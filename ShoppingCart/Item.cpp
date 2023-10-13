#include "Item.h"
#include <cstring>
#include <iostream>
#pragma warning(disable : 4996)

Item::Item() {
	name = nullptr;
	inStock = false;
	price = 0;
}

Item::Item(const char* name, const bool inStock, const double price) {
	setName(name);
	setInStock(inStock);
	setPrice(price);
}

Item::Item(const Item& other) {
	copyFrom(other);
}

Item& Item::operator=(const Item& other) {
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

std::ostream& operator<<(std::ostream& out, const Item& item) {
	out << item.getName() << " " << item.getInStock() << " " << item.getPrice();
	return out;
}

Item::~Item() {
	free();
}

void Item::setName(const char* name) {
	if (name == nullptr)
	{
		return;
	}
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void Item::setInStock(const bool inStock) {
	this->inStock = inStock;
}

void Item::setPrice(double price) {
	if (price > 0)
	{
		price = 0;
	}
	this->price = price;
}

const char* Item::getName() const {
	return name;
}

bool Item::getInStock() const {
	return inStock;
}

double Item::getPrice() const {
	return price;
}

void Item::copyFrom(const Item& other) {
	setName(other.name);
	setInStock(other.inStock);
	setPrice(other.price);
}

void Item::free() {
	delete[] name;
	name = nullptr;
	inStock = false;
	price = 0;
}