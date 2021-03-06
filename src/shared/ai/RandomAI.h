// Generated by dia2code
#ifndef AI__RANDOMAI__H
#define AI__RANDOMAI__H

#include <random>
#include <vector>

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
    RandomAI (engine::Engine* moteur, int randomSeed);
    void run (int player);
    std::vector<int> moveCellResearch (int player);
    std::vector<int> adjacentEnnemyResearch (int player, int init_i, int init_j);
    // Setters and Getters
  };

};

#endif
