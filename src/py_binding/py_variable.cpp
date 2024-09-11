//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include "variable.h"

#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/string.h>
#include <fmt/format.h>

namespace nb = nanobind;
using namespace nb::literals;
using namespace tardis;

void bindVariable(nb::module_& m) {
    nb::class_<Variable> variable(m, "Variable");
    nb::enum_<Variable::Type>(variable, "Type")
            .value("CONTINUOUS", Variable::Type::CONTINUOUS)
            .value("INTEGER", Variable::Type::INTEGER)
            .value("BINARY", Variable::Type::BINARY)
            .value("BOOLEAN", Variable::Type::BOOLEAN)
            .value("RANDOM_UNIFORM", Variable::Type::RANDOM_UNIFORM)
            .value("RANDOM_GAUSSIAN", Variable::Type::RANDOM_GAUSSIAN)
            .value("RANDOM_EXPONENTIAL", Variable::Type::RANDOM_EXPONENTIAL);

    variable.def(nb::init<>())
            .def(nb::init<std::string, Variable::Type>(), "name"_a, "type"_a = Variable::Type::CONTINUOUS)
            .def("is_dummy", &Variable::is_dummy)
            .def("get_id", &Variable::get_id)
            .def("get_type", &Variable::get_type)
            .def("get_name", &Variable::get_name)
            .def("equal_to", &Variable::equal_to)
            .def("less", &Variable::less)
            .def("__str__", &Variable::to_string)
            .def("__repr__", [](const Variable& self) {
                return fmt::format("Variable('{}', {})", self.get_name(), self.get_type());
            });

    m.def(
            "MakeMatrixVariable",
            [](int rows, int cols, const std::string& name, Variable::Type type) {
                return MakeMatrixVariable(rows, cols, name, type);
            },
            "rows"_a, "cols"_a, "name"_a, "type"_a = Variable::Type::CONTINUOUS);
}