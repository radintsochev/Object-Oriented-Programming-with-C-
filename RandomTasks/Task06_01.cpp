#include <iostream>
#include <cmath>
using std::cout, std::cin, std::endl;

struct Point
{
    double x;
    double y;
};

void readPoint(Point& point)
{
    int x,y;
    cout << "X coordinate: ";
    cin >> x;
    cout << "Y coordinate: ";
    cin >> y;
    point.x = x;
    point.y = y;
}

void printPoint(const Point& point)
{
    cout << "("<< point.x <<","<< point.y <<")"<<endl;
}

double distanceFromCenter(const Point& point)
{
    return sqrt(pow(point.x, 2) + pow(point.y, 2));
}

double distance(const Point& point1, const Point& point2)
{
    return sqrt(pow((point1.x - point2.x) , 2) + pow((point1.y - point2.y), 2));
}

short quadrant(const Point& point)
{
    if (point.x > 0 && point.y > 0)
    {
        return 1;
    }
    else if (point.x < 0 && point.y > 0)
    {
        return 2;
    }
    else if (point.x < 0 && point.y < 0)
    {
        return 3;
    }
    else if (point.x > 0 && point.y < 0)
    {
        return 4;
    }
    else
    {
        return -1;
    }
    
}

bool isInsideCircle(double radius, const Point& point)
{
    const Point center = {0, 0};
    return distance(point, center) <= radius;
}

int main()
{
    Point p1, p2;
    readPoint(p1);
    printPoint(p1);
    readPoint(p2);
    printPoint(p2);
    cout << distance(p1, p2) << endl;
    cout << quadrant(p2) << endl;
    cout << isInsideCircle(6, p2) << endl;
}
