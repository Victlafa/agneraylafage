// Generated by dia2code
#ifndef RENDER__ELEMENTTABLAYER__H
#define RENDER__ELEMENTTABLAYER__H

#include <memory>

namespace state {
  class ElementTab;
};
namespace render {
  class Layer;
}

#include "state/ElementTab.h"
#include "Layer.h"

namespace render {

  /// class ElementTabLayer - 
  class ElementTabLayer : public render::Layer {
    // Attributes
  private:
    const std::unique_ptr<state::ElementTab> tab;
    // Operations
  public:
    ElementTabLayer (const std::unique_ptr<state::ElementTab> tab);
    void initSurface (int type);
    // Setters and Getters
  };

};

#endif
