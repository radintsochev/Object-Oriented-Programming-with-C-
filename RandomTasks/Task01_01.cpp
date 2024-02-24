#include <iostream>
using namespace std;

int minWithPointers(int* firstNumber, int* secondNumber)
{
    return *firstNumber < *secondNumber ? *firstNumber : *secondNumber;
}

int minWithRefernces(int& firstNumber, int& secondNumber)
{
    return firstNumber < secondNumber ? firstNumber : secondNumber;
}

int main()
{
    int a = 60;
    int b = 15;
    cout << minWithPointers(&a, &b) << endl;
    cout << minWithRefernces(a, b);
    return 0;
}
