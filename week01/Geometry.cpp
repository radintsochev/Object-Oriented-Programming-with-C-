#include <iostream>

struct Point {
    double x;
    double y;
};

enum edgeCase {
    center,
    Ox,
    Oy
};

struct Quadrant {
    int numberOfQuadrant;
    edgeCase edgeCase;
};

struct Circle {
    Point center;
    double radius;
};

Quadrant findQuadrant(const Point& point) {
    if (point.x > 0 && point.y > 0)
    {
        return { 1, };
    }
    else if (point.x < 0 && point.y > 0)
    {
        return { 2, };
    }
    else if (point.x < 0 && point.y < 0)
    {
        return { 3, };
    }
    else if (point.x > 0 && point.y < 0)
    {
        return { 4, };
    }
    else if (point.x == 0 && point.y == 0)
    {
        return { 0, edgeCase::center };
    }
    else if (point.y == 0)
    {
        return { 0, edgeCase::Ox };
    }
    else
    {
        return { 0, edgeCase::Oy };
    }
}

double findDistance(const Point& point1, const Point& point2) {
    int distX = point1.x - point2.x;
    int distY = point2.y - point2.x;
    return sqrt(distX * distX + distY * distY);
}

bool isOnTheContour(const Point& point, const Circle& circle) {
    return findDistance(point, circle.center) == circle.radius;
}

bool doCirclesIntersect(const Circle& circle1, const Circle& circle2) {
    double sumOfRadiuses = circle1.radius + circle2.radius;
    return sumOfRadiuses > findDistance(circle1.center, circle2.center);
}

bool doesContain(const Circle& circle1, const Circle& circle2) {
    return !(doCirclesIntersect(circle1, circle2)) && circle1.radius < circle2.radius && findDistance(circle1.center, circle2.center) < circle2.radius;
}

struct Vector {
    int data[100];
    int size;
};

int scalarProduct(const Vector& vector1, const Vector& vector2) {
    int smallerSize;
    int scalarProduct = 0;
    if (vector1.size > vector2.size)
    {
        smallerSize = vector2.size;
    }
    else
    {
        smallerSize = vector1.size;
    }
    for (size_t i = 0; i < smallerSize; i++)
    {
        scalarProduct += vector1.data[i] * vector2.data[i];
    }
    return scalarProduct;
}

Vector vectorProduct(const Vector& vector1, const Vector& vector2) {
    int firstCoordinate = vector1.data[1] * vector2.data[2] - vector1.data[2] * vector2.data[1];
    int secondCoordinate = vector1.data[2] * vector2.data[0] - vector1.data[0] * vector2.data[2];
    int thirdCoordinate = vector1.data[0] * vector2.data[1] - vector1.data[1] * vector2.data[0];
    Vector vectorProduct;
    vectorProduct.data[0] = firstCoordinate;
    vectorProduct.data[1] = secondCoordinate;
    vectorProduct.data[2] = thirdCoordinate;
    vectorProduct.size = 3;
    return vectorProduct;
}

struct Line {
    Point point1;
    Point point2;
};

void sortByDistance(int numberOfLines, Line* lines) {
    int* distances = new int[numberOfLines];
    for (size_t i = 0; i < numberOfLines; i++)
    {
        distances[i] = findDistance(lines[i].point1, lines[i].point2);
    }
    for (size_t k = 0; k < numberOfLines - 1; k++)
    {
        int minDistanceIndex = 0;
        for (size_t i = k; i < numberOfLines; i++)
        {
            if (distances[i] < distances[i + 1])
            {
                minDistanceIndex = i;
            }
        }
        if (k != minDistanceIndex)
        {
            int temp = distances[k];
            distances[k] = distances[minDistanceIndex];
            distances[minDistanceIndex] = temp;
            Line tempLine = lines[k];
            lines[k] = lines[minDistanceIndex];
            lines[minDistanceIndex] = tempLine;
        }
    }
    delete[] distances;
    
}

int main()
{
    int x, y;
    std::cin >> x >> y;

    Point point = { x, y };
    Quadrant quadrant = findQuadrant(point);

    if (quadrant.numberOfQuadrant == 0)
    {
        std::cout << "Error code: " << quadrant.edgeCase;
    }
    else
    {
        std::cout << quadrant.numberOfQuadrant;
    }

    Line line1 = { {1, 0}, {4, 0} };
    Line line2 = { {2, 0}, {2.5, 0} };
    Line line3 = { {0, 0}, {10, 0} };

    Line lines[3] = { line1, line2, line3 };
    sortByDistance(3, lines);

    for (size_t i = 0; i < 3; i++)
    {
        std::cout << "x1: " << lines[i].point1.x << " y1: " << lines[i].point1.y << " x2: " << lines[i].point2.x << " y2: " << lines[i].point2.y << std::endl
            ;
    }
}
