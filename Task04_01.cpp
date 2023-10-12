#include <iostream>
#include <cstring>
using std::cout, std::cin, std::endl;
const int MAX_NAME_SIZE = 30;

struct Student
{
    char name[MAX_NAME_SIZE + 1];
    unsigned facultyNumber;
};

void initStudent(Student& student, const char* name, unsigned int fn)
{
    strcpy_s(student.name, MAX_NAME_SIZE, name);
    student.facultyNumber = fn;
}

void printStudent(const Student& student)
{
    cout << "Student: " << student.name << endl;
    cout << "Fn: " << student.facultyNumber << endl;
}

int main()
{
    Student me = {"Radin", 10};
    initStudent(me, "Radin Tsochev", 147);
    printStudent(me);
}