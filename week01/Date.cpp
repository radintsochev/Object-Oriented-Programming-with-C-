#include <iostream>

struct Date {
    size_t day = 1;
    size_t month = 1;
    int year = 0;
};
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

Date nextDay(const Date& date) {
    Date next = date;
    switch (date.month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
        if (date.day == 31)
        {
            next.day = 1;
            ++next.month;
        }
        else
        {
            ++next.day;
        }
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        if (date.day == 30)
        {
            next.day = 1;
            ++next.month;
        }
        else
        {
            ++next.day;
        }
        break;
    case 12:
        if (date.day == 31)
        {
            next.day = 1;
            next.month = 1;
            ++next.year;
        }
        else
        {
            ++next.day;
        }
        break;
    case 2:
        if (isLeapYear(date.year))
        {
            if (date.day == 29)
            {
                next.day = 1;
                ++next.month;
            }
            else
            {
                ++next.day;
            }
        }
        else
        {
            if (date.day == 28)
            {
                next.day = 1;
                ++next.month;
            }
            else
            {
                ++next.day;
            }
        }
    }
    return next;
}

int daysUntil(const Date& from, const Date& to) {
    int result = 0;
    Date next = from;
    while (next.day != to.day || next.month != to.month || next.year != to.year)
    {
        next = nextDay(next);
        ++result;
    }
    return result;
}

int main()
{
    Date bd = { 30, 12, 2003 };
    Date today = { 23, 2, 2024 };
    Date nextBd = nextDay(bd);
    std::cout << daysUntil(bd, today);
}