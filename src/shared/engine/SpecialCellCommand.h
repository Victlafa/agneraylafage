// Generated by dia2code
#ifndef ENGINE__SPECIALCELLCOMMAND__H
#define ENGINE__SPECIALCELLCOMMAND__H

#include <memory>
#include <vector>
#include <string>

namespace engine {
  class Fight;
};
namespace state {
  class State;
};
namespace engine {
  class Command;
}

#include "Fight.h"
#include "CommandTypeID.h"
#include "Command.h"

namespace engine {

  /// class SpecialCellCommand - 
  class SpecialCellCommand : public engine::Command {
    // Associations
    // Attributes
  protected:
    std::shared_ptr<Fight> fight;
    std::vector<int> initPos;
    std::vector<int> finalPos;
    int player;
    std::string type;
    // Operations
  public:
    SpecialCellCommand (int init_i, int init_j, int final_i, int final_j, int player, std::string type);
    bool isSpecial (state::State& state);
    CommandTypeID getTypeID () const;
    void execute (state::State& state);
    void skyPower (state::State& state);
    void sugarPower (state::State& state);
    void bbqPoolPower (state::State& state);
    // Setters and Getters
    const std::shared_ptr<Fight>& getFight() const;
    void setFight(const std::shared_ptr<Fight>& fight);
    const std::vector<int>& getInitPos() const;
    void setInitPos(const std::vector<int>& initPos);
    const std::vector<int>& getFinalPos() const;
    void setFinalPos(const std::vector<int>& finalPos);
    int getPlayer() const;
    void setPlayer(int player);
    const std::string& getType() const;
    void setType(const std::string& type);
  };

};

#endif
