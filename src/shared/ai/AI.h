// Generated by dia2code
#ifndef AI__AI__H
#define AI__AI__H

#include <vector>
#include <memory>

namespace engine {
  class Engine;
  class Command;
}

namespace ai {

  /// class AI - 
  class AI {
    // Attributes
  protected:
    std::vector<std::shared_ptr<engine::Command> > listCommands;
    // Operations
  public:
    AI ();
    virtual void run (const engine::Engine& moteur) = 0;
    // Setters and Getters
    const std::vector<std::shared_ptr<engine::Command> >& getListCommands() const;
    void setListCommands(const std::vector<std::shared_ptr<engine::Command> >& listCommands);
  };

};

#endif
