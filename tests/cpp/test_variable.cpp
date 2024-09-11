//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <gtest/gtest.h>
#include <cppad/cg.hpp>

TEST(Variable, constructor) {
    Variable var("var");
    EXPECT_EQ(var.to_string(), "var");
}