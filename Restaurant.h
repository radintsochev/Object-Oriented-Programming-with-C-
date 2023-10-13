#pragma once
#include "myString.h"
#include "Order.h"

class Restaurant {
private:
	char name[26] = "";
	unsigned numberOfDishes = 0;
	unsigned maxNumberOfItems = 0;
	myString* dish = nullptr;
public:
	Restaurant() = default;
	Restaurant(const Restaurant& other);
	Restaurant& operator=(const Restaurant& other);
	~Restaurant();
	void addItem(const myString& dish);
	bool isInMenu(const myString& dish) const;
	double order(const Order& order) const;
	Restaurant(Restaurant&& other);
	Restaurant& operator=(Restaurant&& other);
private:
	void copyFrom(const Restaurant& other);
	void free();
	void resize();
};