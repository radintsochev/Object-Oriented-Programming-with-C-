#pragma once

class MonsterCard {
private:
	char* name;
	unsigned pointsATK;
	unsigned pointsDEF;
public:
	MonsterCard();
	MonsterCard(const char* name, const unsigned pointsATK, const unsigned pointsDEF);
	MonsterCard(const MonsterCard& other);
	MonsterCard& operator=(const MonsterCard& other);
	char* getName() const;
	unsigned getPointsATK() const;
	unsigned getPointsDEF() const;

};