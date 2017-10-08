from atlasbuggy import ThreadedStream
from atlasbuggy.subscriptions import Update

from .pyratslam import Ptree, LocalViewMatch, VisualOdometry, PosecellNetwork, ExperienceMap, PosecellAction


class Ratslam(ThreadedStream):
    def __init__(self, config_path, enabled=True, log_level=None):
        super(Ratslam, self).__init__(enabled, log_level)

        self.ptree = Ptree(config_path)
        self.ratslam_settings = self.ptree.get_child("ratslam")
        self.odom_settings = self.ptree.get_child("visual_odometry")

        self.lv = LocalViewMatch(self.ratslam_settings)
        self.odometry = VisualOdometry(self.odom_settings)
        self.posecells = PosecellNetwork(self.ratslam_settings)
        self.experience_map = ExperienceMap(self.ratslam_settings)

        self.prev_time = 0.0

        self.source_id = None
        self.destination_id = None
        self.relative_rad = None

        self.capture = None
        self.capture_feed = None
        self.capture_tag = "capture"
        self.require_subscription(self.capture_tag, Update, required_attributes=("fps",))

    def take(self, subscriptions):
        self.capture = self.get_stream(self.capture_tag)
        self.capture_feed = self.get_feed(self.capture_tag)

    def run(self):
        while self.is_running():
            if not self.capture_feed.empty():
                frame = self.capture_feed.get()
                if len(frame.shape) == 2:
                    is_color = True
                    height, width = frame.shape
                else:
                    is_color = False
                    height, width = frame.shape[0:2]

                self.lv.on_image(frame, is_color, width, height)
                vtrans, vrot = self.odometry.on_image(frame, is_color, width, height)
                self.logger.info("odometry: %0.4f, %0.4f" % (vtrans, vrot))

                delta_t = self.dt() - self.prev_time
                self.logger.info("delta t: %0.5f" % delta_t)
                self.posecells.on_odo(vtrans, vrot, delta_t)

                self.posecells.on_view_template(self.lv.get_current_vt(), self.lv.get_relative_rad())

                # self.logger.info(self.posecells.x(), self.posecells.y(), self.posecells.th())
                action = self.posecells.get_action()
                self.logger.info("posecell action: '%s'" % action)
                self.source_id = self.posecells.get_current_exp_id()
                if action != PosecellAction.NO_ACTION:
                    self.destination_id = self.posecells.get_current_exp_id()
                    self.relative_rad = self.posecells.get_relative_rad()

                self.experience_map.on_odo(vtrans, vrot, delta_t)

                self.logger.info("updating experience map...")
                self.update_exp_map(action)
                self.logger.info("done")
                
                index = self.experience_map.get_current_id()
                self.logger.info("%s\t%s" % (
                    self.experience_map.get_experience_x_m(index),
                    self.experience_map.get_experience_y_m(index)
                ))
                self.prev_time = self.dt()

    def update_exp_map(self, action):
        if action == PosecellAction.CREATE_NODE:
            self.logger.info("create experience node")
            self.experience_map.on_create_experience(self.destination_id)
            self.logger.info("set experience node")
            self.experience_map.on_set_experience(self.destination_id, 0)

        elif action == PosecellAction.CREATE_EDGE:
            self.logger.info("create experience link, %s, %s, %s" % (
                self.source_id, self.destination_id, self.relative_rad
            ))
            self.experience_map.on_create_link(self.source_id, self.destination_id, self.relative_rad)
            self.logger.info("set experience node")
            self.experience_map.on_set_experience(self.destination_id, self.relative_rad)

        elif action == PosecellAction.SET_NODE:
            self.logger.info("set experience node")
            self.experience_map.on_set_experience(self.destination_id, self.relative_rad)

        self.experience_map.iterate()
