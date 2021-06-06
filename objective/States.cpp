#include "States.hpp"

std::string stateToString(States state) {
  switch (state) {
    case States::Eat:
      return "is eating...    ";
    case States::Wait:
      return "is waiting...  ";
    case States::Think:
      return "is thinking... ";
    case States::LeftForkAquired:
      return "has left fork... ";
    case States::RightForkAquired:
      return "has right fork... ";
    default:
      return "unknown";
  }
}