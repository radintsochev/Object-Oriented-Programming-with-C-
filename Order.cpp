#include "myString.h"
#include "Order.h"
#include "Restaurant.h"

#pragma warning(disable : 4996)

Order::Order(const Order& other) {
	copyFrom(other);
}

Order& Order::operator=(const Order& other) {
	if (this != &other)
	{
		free();
	}
	copyFrom(other);
	return *this;
}

Order::~Order() {
	free();
}

void Order::copyFrom(const Order& other) {
	strcpy(restName, other.restName);
	numberOfItems = other.numberOfItems;
	maxNumberOfItems = other.maxNumberOfItems;
	item = new myString[numberOfItems + 1];
	for (size_t i = 0; i < numberOfItems; i++)
	{
		item[i] = other.item[i];
	}
}

void Order::free() {
	strcpy(restName,"");
	numberOfItems = 0;
	maxNumberOfItems = 0;
	delete[] item;
}

Order::Order(Order&& other) noexcept {
	strcpy(restName, other.restName);
	numberOfItems = other.numberOfItems;
	maxNumberOfItems = other.maxNumberOfItems;
	item = other.item;
	other.item = nullptr;
}

Order& Order::operator=(Order&& other) noexcept {
	if (this != &other)
	{
		free();
	}
	strcpy(restName, other.restName);
	numberOfItems = other.numberOfItems;
	maxNumberOfItems = other.maxNumberOfItems;
	item = other.item;
	other.item = nullptr;
	return *this;
}

bool Order::exists(const myString& item) const {
	for (size_t i = 0; i < numberOfItems; i++)
	{
		if (this->item[i] == item)
		{
			return true;
		}
	}
	return false;
}

void Order::resize() {
	maxNumberOfItems = 2 * maxNumberOfItems;
	myString* temp = new myString[maxNumberOfItems];
	for (size_t i = 0; i < numberOfItems; i++)
	{
		temp[i] = item[i];
	}
	delete[] item;
	item = temp;
}

unsigned Order::getNumberOfItems() const {
	return numberOfItems;
}

void Order::addItem(const myString& item) {
	if (maxNumberOfItems == numberOfItems)
	{
		resize();
	}
	this->item[numberOfItems] = item;
	++numberOfItems;
}
