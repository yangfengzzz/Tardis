//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <nanobind/nanobind.h>

namespace nb = nanobind;
using namespace nb::literals;

extern void bindAD(nb::module_& m);

NB_MODULE(py_tardis_ext, m) {
    m.doc() = "python binding for Tardis";

    bindAD(m);
}
