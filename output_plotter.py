import re
import random
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import collections  as mc

with open("output.txt") as output:
    content = output.read()

matches = re.finditer(r"([-.\d]*), ([-.\d]*) -> ([-.\d]*), ([-.\d]*)", content)

lines = []
for match_mum, match in enumerate(matches):
    x1 = float(match.group(1))
    y1 = float(match.group(2))
    x2 = float(match.group(3))
    y2 = float(match.group(4))

    lines.append([(x1, y1), (x2, y2)])

c = np.random.rand(len(lines) * 4).reshape((len(lines), 4))
lc = mc.LineCollection(lines, colors=c, linewidths=2)
fig, ax = plt.subplots(1)

ax.add_collection(lc)
ax.autoscale()
ax.margins(0.1)

plt.show()