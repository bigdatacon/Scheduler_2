#include <iostream>
#include "my_module/utils.h"
#include "my_module/DataContainer.h"

int main() {
    std::cout << "Пример Использование add_arrays:  " << std::endl;
    std::vector<int> a = {189089, 2, 3};
    std::vector<int> b = {434234, 5, 6};
    std::vector<int> result = add_arrays(a, b);
    for (int num : result) {
        std::cout << num << " ";
    }
    std::cout << std::endl;


///Использование класса DataContainer
    std::cout << "Пример Использование класса DataContainer:  " << std::endl;
    auto container = DataContainer();
    container.add(10);
    container.add(20);
    std::cout << "container.get_data()" << std:: endl;
    for (auto el :container.getData()){
        std::cout << el << std:: endl;  // Выведет [10, 20]
    }


    // проверка добавления операций
    MSOperation op1 = {0, 1, 10, 20};
    MSOperation op2 = {1, 2, 30, 40};

    container.add_2(&op1);
    container.add_2(&op2);


    for (int val : container.getData()) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    std::cout << "использование container.getData_2() : " << std::endl;
    for (MSOperation* op : container.getData_2()) {
        std::cout << op->nJobIndex << " " << op->nOperationIndex << " "
                  << op->nStartTime << " " << op->nFinishTime << std::endl;
    }


    return 0;
}
