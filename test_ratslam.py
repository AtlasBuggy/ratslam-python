import numpy as np
from build.pyratslam import Ratslam

rat = Ratslam("config/config.txt")
rat.set_view_rgb(np.zeros((10, 10)))
rat.set_odom(0.0, 0.0)
rat.set_delta_time(0.1)
rat.process()

exp = rat.get_experience_map()
print(exp.get_experience(0))
