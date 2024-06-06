import my_module

def test_data_container():
    container = my_module.DataContainer()

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

    # Добавляем операции в разные индексы
    container.add_2(0, op1)
    container.add_2(1, op2)

    data_2_index_0 = container.getData_2(0)
    for op in data_2_index_0:
        print(f"Index 0 -> JobIndex: {op.nJobIndex}, OperationIndex: {op.nOperationIndex}, StartTime: {op.nStartTime}, FinishTime: {op.nFinishTime}")

    data_2_index_1 = container.getData_2(1)
    for op in data_2_index_1:
        print(f"Index 1 -> JobIndex: {op.nJobIndex}, OperationIndex: {op.nOperationIndex}, StartTime: {op.nStartTime}, FinishTime: {op.nFinishTime}")

    my_class = my_module.MyClass(container)
    data_container = my_class.GetDataContainer()
    data_2_from_class = data_container.getData_2(0)
    for op in data_2_from_class:
        print(f"From MyClass -> Index 0 -> JobIndex: {op.nJobIndex}, OperationIndex: {op.nOperationIndex}, StartTime: {op.nStartTime}, FinishTime: {op.nFinishTime}")



    print("Использование класса  CMachine: ")
    machine = my_module.CMachine()
    machine.SetDischarge(15)
    print(machine.GetDischarge())

if __name__ == "__main__":
    test_data_container()
