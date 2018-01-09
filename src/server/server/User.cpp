/** 
 * @file User.cpp
 * @author Philippe-Henri Gosselin
 * @date 9 décembre 2015
 * @copyright CNRS
 */

#include "User.hpp"
#include "User.h"
using namespace server;

User::User (std::string name, state::CreaturesID cr) : name(name), creatures(cr) {
    
}
