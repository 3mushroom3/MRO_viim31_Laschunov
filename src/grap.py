import matplotlib.pyplot as plt
import numpy as np

def read_data(filename):
    """Читает данные из файла и возвращает списки точек для каждого класса."""
    class1 = []
    class2 = []
    with open(filename, 'r', encoding='utf-8') as f: 
        for line in f:
            line = line.strip() 
            if line: 
                if line.startswith("Класс 1"):
                    current_class = class1
                elif line.startswith("Класс 2"):
                    current_class = class2
                elif line.startswith("Центры классов") or line.startswith("Точка на гиперплоскости"):
                    break
                else:
                    x, y = map(float, line.split())
                    current_class.append([x, y])
    return np.array(class1), np.array(class2)

# Чтение данных из файла
filename = "output.txt" # Замените на имя вашего файла
class1, class2 = read_data(filename)

# Чтение центров классов из файла 
with open(filename, 'r', encoding='utf-8') as f:
    lines = f.readlines()
    for i, line in enumerate(lines):
        if line.startswith("Центр класса 1"):
            center1 = np.array(list(map(float, lines[i].split()[3:])))
        elif line.startswith("Центр класса 2"):
            center2 = np.array(list(map(float, lines[i].split()[3:])))

# Чтение точек на гиперплоскости из файла
hyperplane_points = []
with open(filename, 'r', encoding='utf-8') as f:
    for line in f:
        if line.startswith("Точка на гиперплоскости:"):
            x, y = map(float, line.split("(")[1].split(")")[0].split(","))
            hyperplane_points.append([x, y])
hyperplane_points = np.array(hyperplane_points)

# Проверка, достаточно ли точек для построения гиперплоскости
if len(hyperplane_points) >= 2:  
    # Выбираем две точки для построения прямой (в 2D случае)
    point1 = hyperplane_points[0]
    point2 = hyperplane_points[1]

    # Расчет коэффициентов прямой (y = kx + b)
    k = (point2[1] - point1[1]) / (point2[0] - point1[0]) 
    b = point1[1] - k * point1[0] 

    # Создание массива точек для отрисовки гиперплоскости
    hyperplane_x = np.array([-10, 10])  
    hyperplane_y = k * hyperplane_x + b

# Визуализация
plt.scatter(class1[:, 0], class1[:, 1], label='Класс 1', color='blue')
plt.scatter(class2[:, 0], class2[:, 1], label='Класс 2', color='red')
plt.scatter(center1[0], center1[1], marker='*', s=100, color='blue', label='Центр класса 1')
plt.scatter(center2[0], center2[1], marker='*', s=100, color='red', label='Центр класса 2')

# Проверка, построена ли гиперплоскость
if len(hyperplane_points) >= 2:
    plt.plot(hyperplane_x, hyperplane_y, label='Гиперплоскость', linestyle='--', color='green')

plt.xlabel('Ось X')
plt.ylabel('Ось Y')
plt.title('Визуализация кластеров и гиперплоскости')
plt.legend()
plt.show()