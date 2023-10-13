#include "myString.h"
#include "Order.h"
#include "Restaurant.h"

#pragma warning(disable : 4996)

Restaurant::Restaurant(const Restaurant& other) {
	copyFrom(other);
}

Restaurant& Restaurant::operator=(const Restaurant& other) {
	if (this != &other)
	{
		free();
	}
	copyFrom(other);
	return *this;
}

Restaurant::~Restaurant() {
	free();
}

void Restaurant::copyFrom(const Restaurant& other) {
	strcpy(name, other.name);
	numberOfDishes = other.numberOfDishes;
	maxNumberOfItems = other.maxNumberOfItems;
	for (size_t i = 0; i < numberOfDishes; i++)
	{
		dish[i] = other.dish[i];
	}
}

void Restaurant::free() {
	strcpy(name, "");
	numberOfDishes = 0;
	maxNumberOfItems = 0;
	delete[] dish;
}

Restaurant::Restaurant(Restaurant&& other) {
	strcpy(name, other.name);
	numberOfDishes = other.numberOfDishes;
	maxNumberOfItems = other.maxNumberOfItems;
	dish = other.dish;
	other.dish = nullptr;
}

Restaurant& Restaurant::operator=(Restaurant&& other) {
	if (this != &other)
	{
		free();
	}
	strcpy(name, other.name);
	numberOfDishes = other.numberOfDishes;
	maxNumberOfItems = other.maxNumberOfItems;
	dish = other.dish;
	other.dish = nullptr;
	return *this;
}

void Restaurant::resize() {
	maxNumberOfItems = 2 * maxNumberOfItems;
	myString* temp = new myString[maxNumberOfItems];
	for (size_t i = 0; i < numberOfDishes; i++)
	{
		temp[i] = dish[i];
	}
	delete[] dish;
	dish = temp;
}

void Restaurant::addItem(const myString& dish) {
	if (maxNumberOfItems == numberOfDishes)
	{
		resize();
	}
	this->dish[numberOfDishes] = dish;
	++numberOfDishes;
}

bool Restaurant::isInMenu(const myString& dish) const {
	for (size_t i = 0; i < numberOfDishes; i++)
	{
		if (this->dish[i] == dish)
		{
			return true;
		}
	}
	return false;
}

double Restaurant::order(const Order& order) const {
	bool found = false;
	for (size_t i = 0; i < order.getNumberOfItems(); i++)
	{
		found = false;
		for (size_t j = 0; j < numberOfDishes; j++)
		{
			if (order.item[i] == dish[j])
			{
				found = true;
			}
		}
		if (!found)
		{
			throw std::runtime_error("Exception: There was an dish in the order that doesn't exist in this restaurant.");
		}
	}
	return 5 * order.getNumberOfItems();
}