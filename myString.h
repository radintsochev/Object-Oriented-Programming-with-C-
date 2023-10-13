#pragma once
#include <iostream>

class myString {
private:
	char* data = nullptr;
	size_t length = 0;
public:
	myString() = default;
	myString(const char* data);
	myString(const myString& other);
	myString& operator=(const myString& other);
	bool operator==(const myString& other);
	bool operator!=(const myString& other);
	friend std::ostream& operator<<(std::ostream& os, const myString& string);
	friend std::istream& operator>>(std::istream& is, const myString& string);
	~myString();

	myString(myString&& other) noexcept;
	myString& operator=(myString&& other) noexcept;
private:
	void copyFrom(const myString& other);
	void free();
};