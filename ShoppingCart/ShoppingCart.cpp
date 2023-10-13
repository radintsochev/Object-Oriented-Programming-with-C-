#include "ShoppingCart.h"
#include <cstring>
#include <iostream>
#include <fstream>

ShoppingCart::ShoppingCart() {
	item = nullptr;
	itemCount = 0;
	maxItemCount = 0;
}

ShoppingCart::ShoppingCart(const ShoppingCart& other) {
	copyFrom(other);
}

ShoppingCart& ShoppingCart::operator=(const ShoppingCart& other) {
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

ShoppingCart::~ShoppingCart() {
	free();
}

void ShoppingCart::setItemCount(const unsigned itemCount) {
	this->itemCount = itemCount;
}

void ShoppingCart::setMaxItemCount(const unsigned maxItemCount) {
	this->maxItemCount = maxItemCount;
}

void ShoppingCart::copyFrom(const ShoppingCart& other) {
	item = new Item[other.maxItemCount];
	setItemCount(other.itemCount);
	setMaxItemCount(other.maxItemCount);
	for (size_t i = 0; i < itemCount; i++)
	{
		item[i] = other.item[i];
	}
}

void ShoppingCart::resize() {
	Item* temp = new Item[maxItemCount * 2];
	setMaxItemCount(maxItemCount * 2);
	for (size_t i = 0; i < itemCount; i++)
	{
		temp[i] = item[i];
	}
	delete[] item;
	item = temp;
}

int ShoppingCart::find(const char* name) const {
	for (size_t i = 0; i < itemCount; i++)
	{
		if (!strcmp(item[i].getName(), name))
		{
			return i;
		}
	}
	return -1;
}

void ShoppingCart::free() {
	delete[] item;
	itemCount = 0;
	maxItemCount = 0;
}

bool ShoppingCart::addItem(const Item& item) {
	for (size_t i = 0; i < itemCount; i++)
	{
		if (!strcmp(this->item[i].getName(), item.getName()))
		{
			return false;
		}
	}
	if (itemCount == maxItemCount)
	{
		resize();
	}
	this->item[itemCount] = item;
	++itemCount;
	return true;
}

bool ShoppingCart::removeItem(const char* name) {
	if (find(name) == -1)
	{
		return false;
	}
	size_t removeIndex = find(name);
	for (size_t i = removeIndex; i < itemCount; i++)
	{
		item[i] = item[i + 1];
	}
	--itemCount;
	return true;
}

unsigned ShoppingCart::itemsCount() const {
	return itemCount;
}

bool ShoppingCart::exists(const char* name) const {
	return find(name) != -1;
}

bool ShoppingCart::isEmpty() const {
	return itemCount == 0;
}

double ShoppingCart::getPriceOf(const char* name) const {
	return item[find(name)].getPrice();
}

double ShoppingCart::totalPrice() const {
	double totalPrice = 0;
	for (size_t i = 0; i < itemCount; i++)
	{
		totalPrice += item[i].getPrice();
	}
	return totalPrice;
}

void ShoppingCart::sortByName() {
	for (size_t i = 0; i < itemCount - 1; i++)
	{
		for (size_t j = i + 1; j < itemCount; j++)
		{
			if (strcmp(item[i].getName(), item[j].getName()) > 0)
			{
				Item temp = item[i];
				item[i] = item[j];
				item[j] = temp;
			}
		}
	}
}

bool ShoppingCart::save(const char* fileName) const {
	std::ofstream file(fileName);
	if (!file.is_open())
	{
		return false;
	}
	for (size_t i = 0; i < itemCount; i++)
	{
		file << item[i] << std::endl;
	}

	file.close();
	return true;
}