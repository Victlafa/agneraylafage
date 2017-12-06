// Generated by dia2code
#ifndef AI__PATHMAP__H
#define AI__PATHMAP__H

#include <vector>
#include <queue>

namespace ai {
  class Point;
};
namespace state {
  class ElementTab;
};
namespace ai {
  class PointCompareWeight;
}

#include "Point.h"
#include "state/ElementTab.h"
#include "PointCompareWeight.h"

namespace ai {

  /// class PathMap - 
  class PathMap {
    // Attributes
  private:
    int width;
    int height;
    std::vector<int> weights;
    std::priority_queue<Point,std::vector<Point>,PointCompareWeight> queue;
    Point destination;
    // Operations
  public:
    PathMap (const state::ElementTab& grid, const Point& destination);
    int getWeight (const Point& p) const;
    void setWeight (const Point& p, int weight);
    const std::vector<int>& getWeights () const;
    const Point& getDestination () const;
    void init (const state::ElementTab& grid);
    bool dijkstra ();
    void update (const state::ElementTab& grid);
    // Setters and Getters
  };

};

#endif
