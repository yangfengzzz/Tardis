//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <gtest/gtest.h>
#include "variable.h"

#include <torch/torch.h>

using namespace tardis;

TEST(Variable, constructor) {
    Variable var("var");
    EXPECT_EQ(var.to_string(), "var");

    torch::Tensor tensor = torch::rand({2, 3});
    std::cout << tensor << std::endl;
    auto metal = tensor.to(torch::Device("mps"));
    auto a = metal.device().is_vulkan();
    std::cout << a << std::endl;
}