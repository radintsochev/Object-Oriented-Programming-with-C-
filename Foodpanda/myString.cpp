#include "myString.h"
#include <cstring>

#pragma warning(disable : 4996)

myString::myString(const myString& other) {
	copyFrom(other);
}

myString::myString(const char* data) {
	this->data = new char[strlen(data) + 1];
	strcpy(this->data, data);
}

myString& myString::operator=(const myString& other) {
	if (this != &other)
	{
		free();
	}
	copyFrom(other);
	return *this;
}

bool myString::operator==(const myString& other) {
	return !(strcmp(data, other.data));
}

bool myString::operator!=(const myString& other) {
	return !(this == &other);
}

myString::~myString() {
	free();
}

void myString::copyFrom(const myString& other) {
	data = new char[strlen(other.data) + 1];
	strcpy(data, other.data);
}

void myString::free() {
	delete[] data;
}

myString::myString(myString&& other) noexcept{
	data = other.data;
	other.data = nullptr;
}

myString& myString::operator=(myString&& other) noexcept{
	if (this != &other)
	{
		free();
	}
	data = other.data;
	other.data = nullptr;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const myString& string) {
	os << string.data;
	return os;
}

std::istream& operator>>(std::istream& is, const myString& string) {
	is >> string.data;
	return is;
}