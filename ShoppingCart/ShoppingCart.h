#pragma once
#include "Item.h"

class ShoppingCart {
private:
	Item* item;
	unsigned itemCount;
	unsigned maxItemCount;
public:
	ShoppingCart();
	ShoppingCart(const ShoppingCart& other);
	ShoppingCart& operator=(const ShoppingCart& other);
	~ShoppingCart();
	void setItemCount(const unsigned itemCount);
	void setMaxItemCount(const unsigned maxItemCount);
	bool addItem(const Item& item);
	bool removeItem(const char* name);
	unsigned itemsCount() const;
	bool exists(const char* name) const;
	bool isEmpty() const;
	double getPriceOf(const char* name) const;
	double totalPrice() const;
	void sortByName();
	bool save(const char* fileName) const;
private:
	void copyFrom(const ShoppingCart& other);
	void free();
	void resize();
	int find(const char* name) const;
};