import cv2
import time
from pyratslam import Ratslam
from atlasbuggy import ThreadedStream
from atlasbuggy.subscriptions import Update


class RatslamStream(ThreadedStream):
    def __init__(self, config_path):
        super(RatslamStream, self).__init__()

        self.capture_tag = "capture"
        self.timing_tag = "timing"
        self.odom_tag = "odometry"

        self.require_subscription(self.capture_tag, Update)
        self.require_subscription(self.odom_tag, Update, is_suggestion=True,
                                  required_attributes="fps")

        self.capture_feed = None
        self.capture = None

        self.odom_feed = None

        self.rat = Ratslam(config_path)

        self.capture_set = False
        self.odom_set = False
        self.capture_time = 0.0

        self.reset_moving_avg()

    def update_moving_avg(self, vtrans, vrot):
        self.vtrans_sum += vtrans
        self.vrot_sum += vrot
        self.odom_count += 1

    def reset_moving_avg(self):
        self.vtrans_sum = 0.0
        self.vrot_sum = 0.0
        self.odom_count = 0

    def get_moving_avg(self):
        return self.vtrans_sum / self.odom_count, self.vrot_sum / self.odom_count

    def take(self, subscriptions):
        self.capture_feed = subscriptions[self.capture_tag].get_feed()
        self.capture = subscriptions[self.capture_tag].get_stream()
        if self.odom_tag in subscriptions:
            self.odom_feed = subscriptions[self.odom_tag].get_feed()

    def run(self):
        while self.is_running():
            if not self.capture_feed.empty():
                frame = self.capture_feed.get()
                self.capture_time = self.capture.timestamp
                gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
                self.rat.set_view_rgb(cv2.merge((gray, gray, gray)))
                self.capture_set = True

            if self.is_subscribed(self.odom_tag) and not self.odom_feed.empty():
                vtrans, vrot = self.odom_feed.get()
                self.update_moving_avg(vtrans, vrot)
                vtrans_avg, vrot_avg = self.get_moving_avg()

                self.rat.set_odom(vtrans_avg, vrot_avg)
                self.odom_set = True

            if self.capture_set:
                if not self.is_subscribed(self.odom_tag) or self.odom_set:
                    # dt = self.timestamp - self.capture_time
                    dt = 1 / self.capture.fps
                    self.rat.set_delta_time(dt)
                    self.rat.process()

                    self.capture_set = False
                    self.odom_set = False

            # for index in range(self.rat.get_num_experiences()):
            #     exp = self.rat.get_experience(self.rat.get_current_id())
            #     print("%0.4f, %0.4f" % (exp.x_m(), exp.y_m()))

            # current = self.rat.get_experience(self.rat.get_current_id())
            # print("id: %s, num exp: %s, x: %s, y: %s, th: %s" % (
            #     self.rat.get_current_id(), self.rat.get_num_experiences(),
            #     current.x_m(), current.y_m(), current.th_rad()))
            # print("links_from:", tuple(current.links_from()))
            # print("links_to:", tuple(current.links_to()))
            time.sleep(1 / self.capture.fps)
