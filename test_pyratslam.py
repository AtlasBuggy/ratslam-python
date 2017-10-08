import numpy as np

from pyratslam import Ptree, LocalViewMatch

ptree = Ptree("config_irataus.txt.in")
ratslam_settings = ptree.get_child("ratslam")

lv = LocalViewMatch(ratslam_settings)
a = np.zeros((300, 300))
lv.on_image(a, True, 300, 300)
