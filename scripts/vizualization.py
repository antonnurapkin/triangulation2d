import re
import csv
import plotly.graph_objects as go

import numpy as np
import math

triangles = []

with open("triangles.csv", mode='r', encoding='utf-8') as file:
    reader = csv.DictReader(file)

    for row in reader:
        point1 = [float(row["x1"]), float(row["y1"])]
        point2 = [float(row["x2"]), float(row["y2"])]
        point3 = [float(row["x3"]), float(row["y3"])]

        triangles.append([point1, point2, point3])

fig = go.Figure()


triangles = np.array(triangles)
for tri_points in triangles:
    fig.add_trace(go.Scatter(x=tri_points[:,0], y=tri_points[:,1], mode='lines'))

fig.show()