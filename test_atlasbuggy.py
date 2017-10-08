from atlasbuggy import Robot
from atlasbuggy.subscriptions import *
from atlasbuggy.camera import CameraViewer, VideoPlayer
from atlasbuggy.plotters import LivePlotter

from pyratslam import Ratslam

width = 800
height = 500


def main():
    robot = Robot(write=False)

    viewer = CameraViewer()
    video = VideoPlayer(file_name="07_39_40.mp4", width=width, height=height)
    rat = Ratslam("config.txt", log_level=20)
    plotter = LivePlotter(1)

    viewer.subscribe(Update(viewer.capture_tag, video))
    rat.subscribe(Update(rat.capture_tag, video))
    rat.subscribe(Subscription(rat.plotter_tag, plotter))

    robot.run(viewer, video, rat, plotter)


main()
