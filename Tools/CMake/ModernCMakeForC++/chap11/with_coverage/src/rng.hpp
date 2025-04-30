#pragma once

class IRandomNumberGenerator
{
public:
    virtual int Get() = 0;
    virtual ~IRandomNumberGenerator() = default;
};
