/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "Command.h"

namespace engine
{
    Command::~Command() {}
    int Command::getPlayer() const {return player;};
    void Command::setPlayer(int player) {this->player = player;}
    CommandTypeID Command::getType() const { return type; }
    void Command::setType(CommandTypeID type) {this->type = type; }
    Command* Command::deserialize (const Json::Value& in) { return nullptr; }
    CommandTypeID Command::translateType (std::string typeString)
    {
        if (typeString == "CommandTypeID::MOVE")
            return CommandTypeID::MOVE;
        else if (typeString == "CommandTypeID::NEWGAME")
            return CommandTypeID::NEWGAME;
        else if (typeString == "CommandTypeID::PLACE")
            return CommandTypeID::PLACE;
        else if (typeString == "CommandTypeID::POISON")
            return CommandTypeID::POISON;
        else if (typeString == "CommandTypeID::PROTECTED")
            return CommandTypeID::PROTECTED;
        else if (typeString == "CommandTypeID::SPECIAL")
            return CommandTypeID::SPECIAL;
        else
            throw std::runtime_error("Command::translateType - utilisation d'un argument non valable");
    }
}