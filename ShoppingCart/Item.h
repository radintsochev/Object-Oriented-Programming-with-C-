#pragma once
#include <iostream>

class Item {
private:
	char* name;
	bool inStock;
	double price;
public:
	Item();
	Item(const char* name, const bool inStock, const double price);
	Item(const Item& other);
	Item& operator=(const Item& other);
	friend std::ostream& operator<<(std::ostream& out, const Item& item);
	~Item();
	const char* getName() const;
	bool getInStock() const;
	double getPrice() const;
	void setName(const char* name);
	void setInStock(const bool inStock);
	void setPrice(double price);
private:
	void copyFrom(const Item& other);
	void free();
};

