from atlasbuggy import Robot
from atlasbuggy.camera import CameraViewer, VideoPlayer
from atlasbuggy.subscriptions import *

from ratslam_stream import RatslamStream

robot = Robot(write=False)

viewer = CameraViewer()
video = VideoPlayer(file_name="/Users/Woz4tetra/Google Drive/Atlas Docs/Media/Videos/rolls/2017_Oct_01/06_35_25.mp4", width=800, height=500)
ratslam = RatslamStream("test_config.txt")

ratslam.subscribe(Update(ratslam.capture_tag, video))
viewer.subscribe(Update(viewer.capture_tag, video))

robot.run(ratslam, viewer, video)