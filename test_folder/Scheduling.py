#!/usr/bin/env python3
import sys
import os

# Добавьте путь к текущему каталогу, где находится my_module.so
sys.path.append(os.path.dirname(os.path.abspath(__file__)))

import my_module

solver = my_module.Solver()

solver.AddMachine('1052', 1, 5, ('126469', '126487', '126474', '126579', '126533', '126540', '126464', '126461', '126578', '126541', '12651'))
solver.AddMachine('2111', 1, 5, ('126541', '126546', '126549', '126515', '126430', '126522', '126435', '126482', '126464'))

solver.AddOperation(1, '126579', 30, 1)
solver.AddOperation(2, '126482', 45, 1)
solver.AddOperation(3, '126464', 45, 1)
solver.AddOperation(4, '126515', 37, 1)
solver.AddOperation(5, '126541', 22, 1)

solver.AddJob('Наряд-заказ_1481755', 5000, (1, 2, 3, 4, 5))

solver.Solve()

# Solver Functions
# AddMachine(string Name, integer Discharge, integer Cost, string_array OperationsNames);
# AddOperation(integer ID, string Name, integer Duration, integer Discharge);
# AddJob(string Name, integer Deadline, integer_array OperationsIDs);