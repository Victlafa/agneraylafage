// Generated by dia2code
#ifndef RENDER__STATELAYER__H
#define RENDER__STATELAYER__H


namespace render {
  class Layer;
}

#include "Layer.h"

namespace render {

  /// class StateLayer - 
  class StateLayer : public render::Layer {
    // Attributes
  private:
    const state::State& state;
    // Operations
  public:
    StateLayer (const state::State& state);
    void initSurface ();
    // Setters and Getters
  };

};

#endif
