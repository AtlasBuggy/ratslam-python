
import random
import numpy as np
from build.pyratslam import Ratslam

rat = Ratslam("config/config.txt")
for _ in range(5):
    array = np.random.randint(256, size=(20, 20))
    for _ in range(5):
        rat.set_view_rgb(array)
        rat.set_odom(random.random(), random.random())
        rat.set_delta_time(0.1)
        rat.process()

        print(rat.get_num_experiences())
        print(rat.get_experience(0).x_m())
        print(rat.get_experience(0).y_m())
        print(rat.get_experience(0).th_rad())
        print(rat.get_subgoal_m())
