//
// Created by kolya on 8/28/2021.
//
#include "gtest/gtest.h"
#include "Message.h"

using namespace stomp;

TEST(MessageTest, GetFromPack)
{
    float a = 1.f;
    ASSERT_TRUE(GetPatternFromParam((float)1) == PATTERN::FLOAT);
    ASSERT_TRUE(GetPatternFromParam("string") == PATTERN::STRING);
}
