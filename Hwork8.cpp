#include <iostream>
#include <vector>
using namespace std;

struct Point
{
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}

    void printXY() const
    {
        cout << "(" << x << ", " << y << ")" << endl;
    }
};

class Rectangle
{
    private:
    double width, height;
    Point bottomLeft;

    public:
    explicit Rectangle(double w, double h, double x = 0, double y = 0)
    : width(w), height(h), bottomLeft(x, y) {}

    Rectangle(const Rectangle& other)
    {
        width = other.width;
        height = other.height;
        bottomLeft = other.bottomLeft;
    }

    Rectangle& operator=(const Rectangle& other)
    {
        if (this != &other)
        {
            width = other.width;
            height = other.height;
            bottomLeft = other.bottomLeft;
        }
        return *this;
    }

    vector<Point> getAllCorners() const
    {
        vector<Point> corners;
        corners.reserve(4);

        corners.push_back (bottomLeft);
        corners.push_back (Point(bottomLeft.x, bottomLeft.y + height));
        corners.push_back (Point(bottomLeft.x + width, bottomLeft.y));
        corners.push_back (Point(bottomLeft.x + width, bottomLeft.y + height));

        return corners;
    }

    bool intersects(const Rectangle& other) const
    {
        if (bottomLeft.x >= other.bottomLeft.x + other.width)
        {
            return false;
        }

        if (other.bottomLeft.x >= bottomLeft.x + width)
        {
            return false;
        }

        if (bottomLeft.y >= other.bottomLeft.y + height)
        {
            return false;
        }

        if (other.bottomLeft.y >= bottomLeft.y + height)
        {
            return false;
        }

        return true;
    }

    bool contains(const Point& p) const
    {
        return p.x >= bottomLeft.x && p.x <= bottomLeft.x + width
        && p.y >= bottomLeft.y && p.y <= bottomLeft.y + height;
    }

    Rectangle& moveTo(double x, double y)
    {
        bottomLeft.x = x;
        bottomLeft.y = y;

        return *this;
    };

    Rectangle& resize(double w, double h)
    {
        width = w;
        height = h;

        return *this;
    }

    void print()
    {
        cout << "Координата левой нижней точки: (" << bottomLeft.x << ", " << bottomLeft.y << ")" << endl;
        cout << "Размер: " << width << " на " << height << endl;
    }
};

int main()
{
    cout << "Проверка пересечения:" << endl;
    cout << endl;

    Rectangle r1(3, 2, 3, 2);
    Rectangle r2(7, 6, 2, 3);

    cout << "Пересекается ли прямоугольник r1 с r2: " << r1.intersects(r2) << endl;

    Rectangle r3(4, 5, 5, 7);
    Rectangle r4(3, 8, 1, 4);

    cout << "Пересекается ли прямоугольник r3 с r4: " << r3.intersects(r4) << endl;

    cout << endl;
    cout << "Проверка цепочек вызовов:" << endl;
    cout << endl;

    Rectangle r5(7, 5, 3, 4);

    cout << "Исходный прямоугольник r5: " << endl;
    r5.print();

    cout << endl;
    
    r5.moveTo(7, 5);
    r5.resize(3, 4);

    cout << "Изменённый прямоугольник r5: " << endl;
    r5.print();

    cout << endl;
    cout << "Проверка работы с константными объектами:" << endl;
    cout << endl;

    Rectangle r6 (1,2,3,4);

    cout << "Исходный прямоугольник r6: " << endl;
    r6.print();

    cout << endl;

    cout << "Все углы прямоугольника r6: " << endl;

    vector<Point>
    corners = r6.getAllCorners();
    for (const auto& corner : corners)
    {
        corner.printXY();
    };

    cout << endl;

    Point p1 = {2, 2};
    Point p2 = {4, 5};

    cout << "Располагается ли точка p1 в прямоугольнике r6: " << r6.contains(p1) << endl;
    cout << "Располагается ли точка p2 в прямоугольнике r6: " << r6.contains(p2) << endl;

    cout << endl;
    cout << "Проверка корректности копирования:" << endl;
    cout << endl;

    Rectangle RectCopy1 = r1;
    Rectangle RectCopy2(0,0);
    RectCopy2 = r1;

    cout << "Исходный прямоугольник r1: " << endl;
    r1.print();

    cout << endl;

    cout << "Конструктор копирования прямоугольника r1: " << endl;
    RectCopy1.print();

    cout << endl;

    cout << "Оператор присваивания прямоугольника r1: " << endl;
    RectCopy2.print();

    return 0;
};