#include <iostream>
using namespace std;

void fillArray(int* array, int length)
{
    for (size_t i = 0; i < length; i++)
    {
        cout << "array["<< i <<"]: ";
        cin >> array[i];
    }
    
}

bool isBiggerThan (int num1, int num2)
{
    return num1 > num2;
}

int biggerThanSymbol(int* array, int length, char symbol)
{
    int count = 0;
    for (size_t i = 0; i < length; i++)
    {
        if(isBiggerThan(array[i], (int)symbol))
        {
            ++count;
        }
    }
    return count;
}

int main()
{
    int wholeNumber;
    cout << "Write a whole number: ";
    cin >> wholeNumber;
    int* listOfNums = new int[wholeNumber];
    fillArray(listOfNums, wholeNumber);
    char symbol;
    cout << "Write a symbol: ";
    cin >> symbol;
    cout << biggerThanSymbol(listOfNums, wholeNumber, symbol) << endl;
    delete[] listOfNums;
}
