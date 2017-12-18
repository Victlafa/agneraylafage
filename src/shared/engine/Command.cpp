/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "Command.h"
#include "MoveCommand.h"
#include "NewGameCommand.h"
#include "PlaceCommand.h"
#include "PoisonCommand.h"
#include "ProtectedCommand.h"
#include "SpecialCellCommand.h"
#include <iostream>

using namespace std;

namespace engine
{
    Command::~Command() {}
    int Command::getPlayer() const {return player;};
    void Command::setPlayer(int player) {this->player = player;}
    CommandTypeID Command::getType() const { return type; }
    void Command::setType(CommandTypeID type) {this->type = type; }
    
    Command* Command::deserialize (const Json::Value& in) 
    { 
        std::string typeCommand = in.get("type","").asString();
        cout << "Command::deserialize - type de commande recupere : " << typeCommand << endl;
                
        if (typeCommand == "CommandTypeID::MOVE")
            return MoveCommand::deserialize(in);
        else if (typeCommand == "CommandTypeID::NEWGAME")
            return NewGameCommand::deserialize(in);
        else if (typeCommand == "CommandTypeID::PLACE")
            return PlaceCommand::deserialize(in);
        else if (typeCommand == "CommandTypeID::POISON")
            return PoisonCommand::deserialize(in);
        else if (typeCommand == "CommandTypeID::PROTECTED")
            return ProtectedCommand::deserialize(in);
        else if (typeCommand == "CommandTypeID::SPECIAL")
            return SpecialCellCommand::deserialize(in);
        else
            throw std::runtime_error("Command::deserialize - le type de commande recupere en memoire n'est pas valable");
    }
    
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