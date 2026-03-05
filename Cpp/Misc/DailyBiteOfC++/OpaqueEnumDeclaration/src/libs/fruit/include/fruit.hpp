#pragma once

#include <cstdint>

enum class Fruit : uint32_t;

Fruit GetApple();

Fruit GetBanana();

void Display(Fruit fruit);
