#include "MonsterCard.h"
#include <cstring>
#pragma warning(diasble : 4996)
MonsterCard::MonsterCard(const char* name, const unsigned pointsATK, const unsigned pointsDEF) {
	strcpy(this->name, name);
	this->pointsATK = pointsATK;
	this->pointsDEF = pointsDEF;

}