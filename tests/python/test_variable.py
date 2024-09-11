#  Copyright (c) 2024 Feng Yang
#
#  I am making my contributions/submissions to this project solely in my
#  personal capacity and am not conveying any rights to any intellectual
#  property of any third parties.

import pySymbolic as sym
import pytest

def test_variable():
    var = sym.Variable("var name")
    print(var)
    sym.MakeMatrixVariable(1, 1, "aa")