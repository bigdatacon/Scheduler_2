import sys
import os

# Добавьте путь к текущему каталогу, где находится my_module.so
sys.path.append(os.path.dirname(os.path.abspath(__file__)))

import my_module

# Использование класса DataContainer
container = my_module.DataContainer()
container.add(10)
container.add(20)
print("container.get_data()")
print(container.get_data())  # Выведет [10, 20]

# Использование функции add_arrays
result = my_module.add_arrays([1, 2, 3], [4, 5, 6])
print("my_module.add_arrays")
print(result)  # Выведет [5, 7, 9]


# Использование класса
print("Использование класса  CMachine: ")
machine = my_module.CMachine()
machine.SetDischarge(15)
print(machine.GetDischarge())