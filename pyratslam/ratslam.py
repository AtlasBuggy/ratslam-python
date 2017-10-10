import time
from atlasbuggy import ThreadedStream
from atlasbuggy.subscriptions import *
from atlasbuggy.plotters import RobotPlot

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

        self.trajectory_plot = RobotPlot("trajectory", linestyle='', marker='.', markersize=5)

        self.plotter_tag = "plotter"
        self.plotter = None
        self.require_subscription(self.plotter, Subscription, is_suggestion=True)

        self.capture = None
        self.capture_feed = None
        self.capture_tag = "capture"
        self.require_subscription(self.capture_tag, Update, required_attributes=("fps",))

        self.experience_map.on_create_experience(0)
        self.experience_map.on_set_experience(0, 0)

    def take(self, subscriptions):
        self.capture = self.get_stream(self.capture_tag)
        self.capture_feed = self.get_feed(self.capture_tag)
        if self.plotter_tag in subscriptions:
            self.plotter = subscriptions[self.plotter_tag].get_stream()
            self.plotter.add_plots(self.trajectory_plot)

    def image_callback(self, frame, is_color, width, height, delta_t):
        # view template callback
        self.logger.debug("view template on image. w=%s, h=%s, is color=%s" % (width, height, is_color))
        self.local_view.on_image(frame, is_color, width, height)

        self.lv_current_vt = self.local_view.get_current_vt()
        self.lv_relative_rad = self.local_view.get_relative_rad()
        self.logger.debug("lv_current_vt: %s, lv_relative_rad: %s" % (self.lv_current_vt, self.lv_relative_rad))

        # visual odometry callback
        self.logger.debug("odometry on image")
        self.vtrans, self.vrot = self.odometry.on_image(frame, is_color, width, height)
        self.logger.debug("vtrans: %0.4f, vrot: %0.4f" % (self.vtrans, self.vrot))

        # pose cell callback
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

    def template_callback(self, current_vt, relative_rad):
        self.logger.debug("on view template. current_vt: %s, relative_rad: %s" % (current_vt, relative_rad))
        self.posecells.on_view_template(current_vt, relative_rad)

    def action_callback(self):
        if self.action == PosecellAction.CREATE_NODE:
            self.logger.debug("experience map, create node")

            self.experience_map.on_create_experience(self.destination_id)
            self.logger.debug("experience map, created node at id: %s" % self.destination_id)

            self.experience_map.on_set_experience(self.destination_id, 0)
            self.logger.debug("experience map, set experience at id: %s, relative rad: 0" % self.destination_id)

        elif self.action == PosecellAction.CREATE_EDGE:
            self.logger.debug("experience map, create edge")

            self.experience_map.on_create_link(self.source_id, self.destination_id, self.relative_rad)
            self.logger.debug(
                "experience map, created link source: %s -> dest: %s, relative rad: %s" % (
                    self.source_id, self.destination_id, self.relative_rad)
            )

            self.experience_map.on_set_experience(self.destination_id, self.relative_rad)
            self.logger.debug("experience map, set experience at id: %s, relative rad: %s" % (
                self.destination_id, self.relative_rad))

        elif self.action == PosecellAction.SET_NODE:
            self.logger.debug("experience map, set node")

            self.experience_map.on_set_experience(self.destination_id, self.relative_rad)
            self.logger.debug("experience map, set experience at id: %s, relative rad: %s" % (
                self.destination_id, self.relative_rad))

        self.experience_map.iterate()
        self.logger.debug("iterated map")

    def plot_experience_map(self):
        

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

                self.image_callback(frame, is_color, width, height, delta_t)
                self.template_callback(self.lv_current_vt, self.lv_relative_rad)
                self.action_callback()

                self.prev_time = self.dt()
