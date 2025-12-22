#include <iostream>
#include <vector>
#include <cmath>

// Структура Point для хранения координат точки
struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

class Rectangle {
private:
    double width, height;
    Point bottomLeft; // координата нижнего левого угла

public:
    // 1. Параметрический конструктор (с explicit)
    explicit Rectangle(double w = 0, double h = 0, double x = 0, double y = 0)
        : width(w), height(h), bottomLeft(x, y) {}

    // 2. Конструктор копирования (глубокое копирование)
    Rectangle(const Rectangle& other)
        : width(other.width), height(other.height), bottomLeft(other.bottomLeft) {
        std::cout << "Copy constructor called!" << std::endl;
    }

    // 3. Оператор присваивания (с защитой от самоприсваивания)
    Rectangle& operator=(const Rectangle& other) {
        if (this != &other) { // защита от самоприсваивания
            width = other.width;
            height = other.height;
            bottomLeft = other.bottomLeft;
        }
        return *this; // возврат *this для цепочек
    }

    // Деструктор (правило трёх) – здесь не нужен особый, но для полноты оставим
    ~Rectangle() = default;

    // --- Константные методы ---

    // Возвращает вектор из 4 углов прямоугольника
    std::vector<Point> getAllCorners() const {
        std::vector<Point> corners;
        corners.push_back(bottomLeft); // левый нижний
        corners.push_back(Point(bottomLeft.x + width, bottomLeft.y)); // правый нижний
        corners.push_back(Point(bottomLeft.x + width, bottomLeft.y + height)); // правый верхний
        corners.push_back(Point(bottomLeft.x, bottomLeft.y + height)); // левый верхний
        return corners;
    }

    // Проверяет, пересекается ли данный прямоугольник с другим
    bool intersects(const Rectangle& other) const {
        bool noOverlap = bottomLeft.x >= other.bottomLeft.x + other.width ||
                         other.bottomLeft.x >= bottomLeft.x + width ||
                         bottomLeft.y >= other.bottomLeft.y + other.height ||
                         other.bottomLeft.y >= bottomLeft.y + height;
        return !noOverlap;
    }

    // Проверяет, лежит ли точка внутри прямоугольника
    bool contains(const Point& p) const {
        return p.x >= bottomLeft.x && p.x <= bottomLeft.x + width &&
               p.y >= bottomLeft.y && p.y <= bottomLeft.y + height;
    }

    // Возвращает площадь
    double getArea() const {
        return width * height;
    }

    // --- Методы с цепочками (возвращают *this) ---

    // Перемещает прямоугольник в новые координаты
    Rectangle& moveTo(double x, double y) {
        bottomLeft.x = x;
        bottomLeft.y = y;
        return *this;
    }

    // Изменяет размеры прямоугольника
    Rectangle& resize(double w, double h) {
        width = w;
        height = h;
        return *this;
    }

    // Вспомогательный метод для вывода информации (не обязательный)
    void printInfo() const {
        std::cout << "Rectangle: w=" << width << ", h=" << height
                  << ", x=" << bottomLeft.x << ", y=" << bottomLeft.y << std::endl;
    }
};

// --- Тестирование ---
int main() {
    // 1. Проверка конструкторов и оператора присваивания
    Rectangle rect1(10, 20, 1, 2);
    Rectangle rect2 = rect1; // конструктор копирования
    Rectangle rect3;
    rect3 = rect1; // оператор присваивания

    std::cout << "rect1: "; rect1.printInfo();
    std::cout << "rect2: "; rect2.printInfo();
    std::cout << "rect3: "; rect3.printInfo();

    // 2. Проверка константных методов
    const Rectangle constRect(5, 5, 0, 0);
    std::cout << "Area of constRect: " << constRect.getArea() << std::endl;
    std::vector<Point> corners = constRect.getAllCorners();
    std::cout << "Corners of constRect:" << std::endl;
    for (const auto& p : corners) {
        std::cout << "  (" << p.x << ", " << p.y << ")" << std::endl;
    }

    // 3. Проверка intersects и contains
    Rectangle r1(10, 10, 0, 0);
    Rectangle r2(5, 5, 3, 3);
    Rectangle r3(5, 5, 15, 15);
    Point p1(2, 2), p2(20, 20);

    std::cout << "r1 intersects r2: " << (r1.intersects(r2) ? "yes" : "no") << std::endl;
    std::cout << "r1 intersects r3: " << (r1.intersects(r3) ? "yes" : "no") << std::endl;
    std::cout << "r1 contains (2,2): " << (r1.contains(p1) ? "yes" : "no") << std::endl;
    std::cout << "r1 contains (20,20): " << (r1.contains(p2) ? "yes" : "no") << std::endl;

    // 4. Проверка цепочек вызовов
    Rectangle r4;
    r4.resize(30, 40).moveTo(100, 200).printInfo();

    // 5. Проверка с константными объектами
    const Rectangle constR(2, 3, 5, 5);
    // constR.moveTo(0,0); // Ошибка компиляции — метод не константный
    std::cout << "constR area: " << constR.getArea() << std::endl;

    return 0;
}