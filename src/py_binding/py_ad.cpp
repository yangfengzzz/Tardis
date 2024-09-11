//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <cppad/cg.hpp>

#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>

namespace nb = nanobind;
using namespace nb::literals;
using namespace CppAD;

template <class Base>
void visitAD(nb::module_& m, const char* name) {
    nb::class_<AD<Base>>(m, name)
            .def(nb::init<>())
            .def(nb::init<const Base&>())
            .def_static("abort_recording", &AD<Base>::abort_recording)
            .def("abs_me", &AD<Base>::abs_me)
            .def("acos_me", &AD<Base>::acos_me)
            .def("asin_me", &AD<Base>::asin_me);
}

void bindAD(nb::module_& m) {
    visitAD<double>(m, "AD");
}