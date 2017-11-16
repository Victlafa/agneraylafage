// Generated by dia2code
#ifndef AI__RANDOMAI__H
#define AI__RANDOMAI__H

#include <random>

namespace engine {
  class Engine;
};
namespace ai {
  class AI;
}

#include "AI.h"

namespace ai {

  /// class RandomAI - 
  class RandomAI : public ai::AI {
    // Attributes
  private:
    std::mt19937 randGen;
    // Operations
  public:
    RandomAI (int randomSeed);
    void run (const engine::Engine& moteur);
    // Setters and Getters
  };

};

#endif