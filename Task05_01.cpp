#include <iostream>
using std::cout, std::cin, std::endl;

struct ComplexNumber
{
    double Re;
    double Im;
};

ComplexNumber sumComplexNums(const ComplexNumber& num1, const ComplexNumber& num2)
{
    ComplexNumber sum;
    sum.Re = num1.Re + num2.Re;
    sum.Im = num1.Im + num2.Im;
    return sum;
}

void printComplexNums(const ComplexNumber& num)
{
    cout << num.Re << " + " << num.Im <<"i"<<endl;
}

int main()
{
    ComplexNumber num1 = {3, 8};
    ComplexNumber num2 = {0.4, 0.9};
    printComplexNums(sumComplexNums(num1, num2));
}