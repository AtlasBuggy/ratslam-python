import time

from atlasbuggy import ThreadedStream
from atlasbuggy.subscriptions import *
from atlasbuggy.plotters import RobotPlot, RobotPlotCollection

from .pyratslam import Ptree, LocalViewMatch, VisualOdometry, PosecellNetwork, ExperienceMap, PosecellAction


class Ratslam(ThreadedStream):
    def __init__(self, config_path, enabled=True, log_level=None):
        super(Ratslam, self).__init__(enabled, log_level)

        self.ptree = Ptree(config_path)
        self.ratslam_settings = self.ptree.get_child("ratslam")
        self.odom_settings = self.ptree.get_child("visual_odometry")

        self.local_view = LocalViewMatch(self.ratslam_settings)
        self.odometry = VisualOdometry(self.odom_settings)
        self.posecells = PosecellNetwork(self.ratslam_settings)
        self.experience_map = ExperienceMap(self.ratslam_settings)

        self.prev_time = 0.0

        self.lv_current_vt = None
        self.lv_relative_rad = None
        self.vtrans = 0.0
        self.vrot = 0.0
        self.source_id = None
        self.destination_id = None
        self.relative_rad = None
        self.action = PosecellAction.NO_ACTION

        self.from_points = RobotPlot("from points", linestyle='', marker='o')
        self.to_points = RobotPlot("to points", linestyle='', marker='x')
        self.trajectory = RobotPlotCollection("trajectory", self.from_points, self.to_points)

        self.capture = None
        self.capture_feed = None
        self.capture_tag = "capture"
        self.require_subscription(self.capture_tag, Update, required_attributes=("fps",))

        self.plotter = None
        self.plotter_tag = "plotter"
        self.require_subscription(self.plotter_tag, Subscription, is_suggestion=True)

        self.experience_map.on_create_experience(0)
        self.experience_map.on_set_experience(0, 0)

    def take(self, subscriptions):
        self.capture = self.get_stream(self.capture_tag)
        self.capture_feed = self.get_feed(self.capture_tag)
        if self.plotter_tag in subscriptions:
            self.plotter = self.get_stream(self.plotter_tag)
            self.plotter.add_plots(self.trajectory)

    def update_ratslam(self, frame, is_color, width, height, delta_t):
        self.logger.debug("----- update ratslam -----")
        # image view template callback
        self.logger.debug(
            "view template on image. w=%s, h=%s, is color=%s, dt=%0.4f" % (width, height, is_color, delta_t))
        self.local_view.on_image(frame, is_color, width, height)

        self.lv_current_vt = self.local_view.get_current_vt()
        self.lv_relative_rad = self.local_view.get_relative_rad()
        self.logger.debug("lv_current_vt: %s, lv_relative_rad: %s" % (self.lv_current_vt, self.lv_relative_rad))

        # image visual odometry callback
        self.logger.debug("odometry on image")
        self.vtrans, self.vrot = self.odometry.on_image(frame, is_color, width, height)
        self.logger.debug("vtrans: %0.4f, vrot: %0.4f" % (self.vtrans, self.vrot))

        # pose cell view template callback
        self.logger.debug(
            "on view template. current_vt: %s, relative_rad: %s" % (self.lv_current_vt, self.lv_relative_rad))
        self.posecells.on_view_template(self.lv_current_vt, self.lv_relative_rad)

        # odometry pose cell callback
        self.logger.debug("get_current_exp_id, posecells")
        self.source_id = self.posecells.get_current_exp_id()
        self.logger.debug("posecells source id: %s" % self.source_id)

        self.logger.debug("on_odo, posecells")
        self.posecells.on_odo(self.vtrans, self.vrot, delta_t)

        self.action = self.posecells.get_action()
        self.logger.debug("posecell action: %s" % self.action)

        if self.action != PosecellAction.NO_ACTION:
            self.destination_id = self.posecells.get_current_exp_id()
            self.relative_rad = self.posecells.get_relative_rad()
            self.logger.debug("dest id: %s, relative rad: %s" % (self.destination_id, self.relative_rad))
            self.logger.debug("pose x: %0.4f, pose y: %0.4f, pose th: %0.4f" % (
                self.posecells.x(), self.posecells.y(), self.posecells.th()))

            # odometry experience map callback
            self.logger.debug("on_odo, experience map")
            self.experience_map.on_odo(self.vtrans, self.vrot, delta_t)

            self.action_callback()

    def action_callback(self):
        if self.action == PosecellAction.CREATE_NODE:
            self.logger.debug("experience map, create node")

            self.experience_map.on_create_experience(self.destination_id)
            x, y = self.exp_map_coords(self.destination_id)
            self.logger.debug("experience map, created node at id: %s, x: %0.4f, y: %0.4f" % (
                self.destination_id, x, y))

            self.experience_map.on_set_experience(self.destination_id, 0)
            self.logger.debug("experience map, set experience at id: %s, relative rad: 0" % self.destination_id)

        elif self.action == PosecellAction.CREATE_EDGE:
            self.logger.debug("experience map, create edge")

            self.experience_map.on_create_link(self.source_id, self.destination_id, self.relative_rad)

            dest_x, dest_y = self.exp_map_coords(self.destination_id)
            src_x, src_y = self.exp_map_coords(self.source_id)
            self.logger.debug(
                "experience map, created link source: %s (%0.4f, %0.4f) -> dest: %s (%0.4f, %0.4f), relative rad: %s" % (
                    self.source_id, src_x, src_y, self.destination_id, dest_x, dest_y, self.relative_rad)
            )

            self.experience_map.on_set_experience(self.destination_id, self.relative_rad)
            self.logger.debug("experience map, set experience at id: %s, relative rad: %s" % (
                self.destination_id, self.relative_rad))

        elif self.action == PosecellAction.SET_NODE:
            self.logger.debug("experience map, set node")

            self.experience_map.on_set_experience(self.destination_id, self.relative_rad)

            x, y = self.exp_map_coords(self.destination_id)
            self.logger.debug("experience map, set experience at id: %s, x: %0.4f, y: %0.4f, relative rad: %s" % (
                self.destination_id, x, y, self.relative_rad))

        self.experience_map.iterate()
        self.logger.debug("iterated map, num experiences: %s" % self.experience_map.get_num_experiences())

        current_id = self.experience_map.get_current_id()
        x, y = self.exp_map_coords(current_id)

        self.logger.debug("exp map id: %s, x: %0.4f, y: %0.4f" % (current_id, x, y))

    def exp_map_coords(self, exp_id):
        x = self.experience_map.get_experience_x_m(exp_id)
        y = self.experience_map.get_experience_y_m(exp_id)

        return x, y

    def run(self):
        while self.is_running():
            time.sleep(1 / self.capture.fps)
            if not self.capture_feed.empty():
                frame = self.capture_feed.get()
                if len(frame.shape) == 2:
                    is_color = True
                    height, width = frame.shape
                else:
                    is_color = False
                    height, width = frame.shape[0:2]

                delta_t = self.dt() - self.prev_time
                self.update_ratslam(frame, is_color, width, height, delta_t)
                self.prev_time = self.dt()

                if self.is_subscribed(self.plotter_tag):
                    x1s = []
                    y1s = []
                    x2s = []
                    y2s = []
                    for index in range(self.experience_map.get_num_links()):
                        from_id = self.experience_map.get_link_exp_from_id(index)
                        to_id = self.experience_map.get_link_exp_to_id(index)

                        x1, y1 = self.exp_map_coords(from_id)
                        x2, y2 = self.exp_map_coords(to_id)
                        x1s.append(x1)
                        y1s.append(y1)
                        x2s.append(x2)
                        y2s.append(y2)

                    if len(x1s) != len(y1s):
                        print(x1s, y1s)
                    else:
                        self.from_points.update(x1s, y1s)

                    if len(x2s) != len(y2s):
                        print(x2s, y2s)
                    else:
                        self.to_points.update(x2s, y2s)

    def stop(self):
        output = ""
        for index in range(self.experience_map.get_num_links()):
            from_id = self.experience_map.get_link_exp_from_id(index)
            to_id = self.experience_map.get_link_exp_to_id(index)

            x1, y1 = self.exp_map_coords(from_id)
            x2, y2 = self.exp_map_coords(to_id)
            output += "%s, %s -> %s, %s\n" % (x1, y1, x2, y2)

        with open("output.txt", 'w+') as file:
            file.write(output)
