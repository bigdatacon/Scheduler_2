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

    return 0;
}
