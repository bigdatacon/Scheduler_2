import my_module

def test_data_container():
    container = my_module.DataContainer()
    container.add(10)
    container.add(20)

    op1 = my_module.MSOperation()
    op1.nJobIndex = 0
    op1.nOperationIndex = 1
    op1.nStartTime = 10
    op1.nFinishTime = 20

    op2 = my_module.MSOperation()
    op2.nJobIndex = 1
    op2.nOperationIndex = 2
    op2.nStartTime = 30
    op2.nFinishTime = 40

    container.add_2(op1)
    container.add_2(op2)

    print("container.getData()")
    print(container.getData())

    print("Проверка что может указатели получить из container.getData_2()")
    data_2 = container.getData_2()
    for op in data_2:
        print(f"JobIndex: {op['nJobIndex']}, OperationIndex: {op['nOperationIndex']}, StartTime: {op['nStartTime']}, FinishTime: {op['nFinishTime']}")

    # Использование функции add_arrays
    result = my_module.add_arrays([1, 2, 3], [4, 5, 6])
    print("my_module.add_arrays")
    print(result)  # Выведет [5, 7, 9]


    # Использование класса
    print("Использование класса  CMachine: ")
    machine = my_module.CMachine()
    machine.SetDischarge(15)
    print(machine.GetDischarge())

if __name__ == "__main__":
    test_data_container()
