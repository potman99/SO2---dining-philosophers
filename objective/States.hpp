#pragma once
#include <string>

enum class States { Eat, Wait, Think, LeftForkAquired, RightForkAquired };

std::string stateToString(States state);