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
.def("add", &DataContainer::add)
.def("add_2", &DataContainer::add_2)
.def("getData", &DataContainer::getData)
.def("getData_2", [](const DataContainer &self) {
std::vector<py::dict> result;
for (auto* op : self.getData_2()) {
py::dict d;
d["nJobIndex"] = op->nJobIndex;
d["nOperationIndex"] = op->nOperationIndex;
d["nStartTime"] = op->nStartTime;
d["nFinishTime"] = op->nFinishTime;
result.push_back(d);
}
return result;
});

// Регистрация функции add_arrays
m.def("add_arrays", &add_arrays, "A function that adds two integer arrays");
}
