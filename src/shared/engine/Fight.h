// Generated by dia2code
#ifndef ENGINE__FIGHT__H
#define ENGINE__FIGHT__H

#include <vector>

namespace state {
  class State;
}

namespace engine {

  /// class Fight - 
  class Fight {
    // Attributes
  protected:
    std::vector<int> fighterPos;
    std::vector<int> defenderPos;
    int fighter;
    // Operations
  public:
    Fight (int i_fighter, int j_fighter, int i_defender, int j_defender, int fighter);
    bool fightProcess (state::State& state);
    void gainConquest (state::State& state);
    void execute (state::State& state);
    // Setters and Getters
    const std::vector<int>& getFighterPos() const;
    void setFighterPos(const std::vector<int>& fighterPos);
    const std::vector<int>& getDefenderPos() const;
    void setDefenderPos(const std::vector<int>& defenderPos);
    int getFighter() const;
    void setFighter(int fighter);
  };

};

#endif
