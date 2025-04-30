#pragma once
#include "gmock/gmock.h"
#include "rng.hpp"

class MockRandomNumberGenerator : public IRandomNumberGenerator
{
public:
    MOCK_METHOD(int, Get, (), (override));
};
