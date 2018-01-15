// Generated by dia2code
#ifndef SERVER__GAMESERVICE__H
#define SERVER__GAMESERVICE__H

#include <json/json.h>

namespace server {
  class AbstractService;
}

#include "HttpStatus.h"
#include "AbstractService.h"

namespace server {

  /// class GameService - 
  class GameService : public server::AbstractService {
    // Attributes
  public:
    int beginner     = 0;
    // Operations
  public:
    GameService ();
    HttpStatus get (Json::Value& out, int id) const;
    // Setters and Getters
  };

};

#endif