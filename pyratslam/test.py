from atlasbuggy import Robot
from atlasbuggy.camera import CameraViewer, VideoPlayer
from atlasbuggy.subscriptions import *
from atlasbuggy.logparser import LogParser

from lms200 import LmsSimulator, Slam
from ratslam_stream import RatslamStream

# class Simulator(LogParser):
#     def __init__(self, file_name):
#         super(Simulator, self).__init__(file_name)
#
#         self.odom_tag = "odometry"
#         self.add_service(self.odom_tag)
#
#         self.sicklms = None
#
#     def take_from_log(self, subscriptions):
#         self.sicklms = subscriptions[self.lms_tag]
#
#     async def update(self):
#         if self.line_info["name"] == self.sicklms.name:
#
#             self.post((0.0, 0.0), self.odom_tag)
#
#             await asyncio.sleep(self.update_rate)


map_size_pixels = 1600
map_size_meters = 50

robot = Robot(write=False)

viewer = CameraViewer()
video = VideoPlayer(file_name="/Users/Woz4tetra/Google Drive/Atlas Docs/Media/Videos/rolls/2017_Oct_01/09_32_39.mp4",
                    width=800, height=500)
sicklms = LmsSimulator()
simulator = LogParser("")
slam = Slam(map_size_pixels, map_size_meters, write_image=True, enabled=True)

ratslam = RatslamStream("test_config.txt")

ratslam.subscribe(Update(ratslam.capture_tag, video))
ratslam.subscribe(Update(ratslam.odom_tag, simulator))
viewer.subscribe(Update(viewer.capture_tag, video))
simulator.subscribe(Subscription("LMS200", sicklms))
slam.subscribe(Feed(slam.lms_tag, sicklms))

robot.run(ratslam, viewer, video)
