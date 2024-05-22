//#include <pybind11/pybind11.h>
//#include <pybind11/stl.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>


#include "DataContainer.h"
#include "InputData.h"
#include "utils.h"  // Убедитесь, что включаете заголовочный файл с определением функции add_arrays

namespace py = pybind11;

PYBIND11_MODULE(my_module, m) {
    // Регистрация класса CMachine
    py::class_<CMachine>(m, "CMachine")
            .def(py::init<>())
            .def("SetDischarge", &CMachine::SetDischarge)
            .def("GetDischarge", &CMachine::GetDischarge);
    // Регистрация класса DataContainer
    py::class_<DataContainer>(m, "DataContainer")
            .def(py::init<>())  // Default constructor
            .def("add", &DataContainer::add, "Add a number to the container")
            .def("get_data", &DataContainer::getData, "Get all data from the container");

    // Регистрация функции add_arrays
    m.def("add_arrays", &add_arrays, "A function that adds two integer arrays");
}
