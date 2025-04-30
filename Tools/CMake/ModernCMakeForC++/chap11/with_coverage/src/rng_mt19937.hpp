#include "rng.hpp"

class MT19937RandomNumberGenerator : public IRandomNumberGenerator
{
public:
    int Get() override;
};
