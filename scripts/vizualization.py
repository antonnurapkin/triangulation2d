import sys
import csv
import plotly.graph_objects as go
import plotly.express as px
from pathlib import Path
import numpy as np


triangles = []


if sys.argv[1] != "--file":
    raise AttributeError(f"Такого аргумента не существует: {sys.argv[1]}")


path_to_triangles = Path(sys.argv[2])


with open(path_to_triangles, mode='r', encoding='utf-8') as file:
    reader = csv.DictReader(file)

    for row in reader:
        point1 = [float(row["x1"]), float(row["y1"])]
        point2 = [float(row["x2"]), float(row["y2"])]
        point3 = [float(row["x3"]), float(row["y3"])]

        triangles.append([point1, point2, point3, point1])  # point1 для замыкания треугольника


fig = go.Figure()

triangles = np.array(triangles)
for tri_points in triangles:
    fig.add_trace(go.Scatter(x=tri_points[:,0], y=tri_points[:,1], mode='lines + markers', marker=dict(color='blue')))

fig.show()

# import re
# import csv
# import plotly.graph_objects as go
# import plotly.express as px
# from pathlib import Path
# import numpy as np
# import math

# triangles = []

# with open(Path(__file__).parent / "triangles.csv", mode='r', encoding='utf-8') as file:
#     reader = csv.DictReader(file)

#     for row in reader:
#         point1 = [float(row["x1"]), float(row["y1"])]
#         point2 = [float(row["x2"]), float(row["y2"])]
#         point3 = [float(row["x3"]), float(row["y3"])]

#         triangles.append([point1, point2, point3, point1])  # point1 для замыкания треугольника

# fig = go.Figure()

# triangles = np.array(triangles)
# for i, tri_points in enumerate(triangles):
#     # Отображение треугольника
#     fig.add_trace(go.Scatter(
#         x=tri_points[:,0], 
#         y=tri_points[:,1], 
#         mode='lines+markers', 
#         marker=dict(color='blue', size=8),
#         line=dict(color='blue', width=2),
#         name=f'Треугольник {i+1}'
#     ))
    
#     # Вычисление центра и радиуса описанной окружности
#     A = tri_points[0]
#     B = tri_points[1]
#     C = tri_points[2]
    
#     # Вычисление центра описанной окружности
#     D = 2 * (A[0]*(B[1]-C[1]) + B[0]*(C[1]-A[1]) + C[0]*(A[1]-B[1]))
    
#     if abs(D) < 1e-10:  # Проверка на вырожденный треугольник
#         continue
    
#     Ux = ((A[0]**2 + A[1]**2)*(B[1]-C[1]) + 
#           (B[0]**2 + B[1]**2)*(C[1]-A[1]) + 
#           (C[0]**2 + C[1]**2)*(A[1]-B[1])) / D
    
#     Uy = ((A[0]**2 + A[1]**2)*(C[0]-B[0]) + 
#           (B[0]**2 + B[1]**2)*(A[0]-C[0]) + 
#           (C[0]**2 + C[1]**2)*(B[0]-A[0])) / D
    
#     # Радиус описанной окружности
#     radius = math.sqrt((A[0]-Ux)**2 + (A[1]-Uy)**2)
    
#     # Создание точек для окружности
#     theta = np.linspace(0, 2*np.pi, 100)
#     circle_x = Ux + radius * np.cos(theta)
#     circle_y = Uy + radius * np.sin(theta)
    
#     # Отображение окружности
#     fig.add_trace(go.Scatter(
#         x=circle_x, 
#         y=circle_y, 
#         mode='lines',
#         line=dict(color='red', width=2, dash='dash'),
#         name=f'Окружность {i+1}'
#     ))
    
#     # Отображение центра окружности
#     fig.add_trace(go.Scatter(
#         x=[Ux], 
#         y=[Uy], 
#         mode='markers',
#         marker=dict(color='red', size=6),
#         name=f'Центр {i+1}',
#         showlegend=False
#     ))

# fig.update_layout(
#     title='Треугольники и их описанные окружности',
#     xaxis_title='X',
#     yaxis_title='Y',
#     showlegend=True,
#     width=800,
#     height=600
# )

# fig.show()