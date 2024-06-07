#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "DataContainer.h"
#include "InputData.h"
#include "utils.h"

namespace py = pybind11;

PYBIND11_MODULE(my_module, m) {
    // Регистрация класса CMachine
    py::class_<CMachine>(m, "CMachine")
            .def(py::init<>())
            .def("SetDischarge", &CMachine::SetDischarge)
            .def("GetDischarge", &CMachine::GetDischarge);

    // Регистрация структуры MSOperation
    py::class_<MSOperation>(m, "MSOperation")
            .def(py::init<>())
            .def_readwrite("nJobIndex", &MSOperation::nJobIndex)
            .def_readwrite("nOperationIndex", &MSOperation::nOperationIndex)
            .def_readwrite("nStartTime", &MSOperation::nStartTime)
            .def_readwrite("nFinishTime", &MSOperation::nFinishTime);

    // Регистрация класса DataContainer
    py::class_<DataContainer>(m, "DataContainer")
            .def(py::init<>())
            .def("add_2", &DataContainer::add_2)
            .def("getData_2", &DataContainer::getData_2, py::return_value_policy::reference_internal);

    // Регистрация класса MyClass
    py::class_<MyClass>(m, "MyClass")
            .def(py::init<DataContainer*>())
            .def("Solve", &MyClass::Solve)
            .def("GetDataContainer", &MyClass::GetDataContainer, py::return_value_policy::reference);
}
