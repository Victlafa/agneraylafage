#include "SpecialCell.h"
#include "Cell.h"
#include "SpecialCellID.h"


int SpecialCell::getx(){
	return x;
}

void SpecialCell::setx(int new_x){
	x = new_x;
}

int SpecialCell::gety(){
	return y;
}

void SpecialCell::sety(int new_y){
	y = new_y;
}

std::string SpecialCell::getResType(){
	return neededResType;
}

void SpecialCell::setResType(std::string res){
	neededResType = res;
}

int SpecialCell::getResNbr(){
	return neededResNbr;
}

void SpecialCell::setResNbr(int nbr){
	neededResNbr = nbr;
}

