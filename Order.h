#pragma once
#include "myString.h"
#include "Restaurant.h"

class Order {
private:
	char restName[26] = "";
	unsigned numberOfItems = 0;
	unsigned maxNumberOfItems = 0;
	myString* item = nullptr;
public:
	friend class Restaurant;
	Order() = default;
	Order(const Order& other);
	Order& operator=(const Order& other);
	~Order();
	unsigned getNumberOfItems() const;
	bool exists(const myString& item) const;
	void addItem(const myString& item);
	Order(Order&& other) noexcept;
	Order& operator=(Order&& other) noexcept;
private:
	void copyFrom(const Order& other);
	void free();
	void resize();
};