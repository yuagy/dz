#include <iostream>
using namespace std;

class Rectangle {
private:
    double width;
    double height;

public:
    // Конструктор по умолчанию (1x1)
    Rectangle() : width(1.0), height(1.0) {
        cout << "Sozdan rectangle po umolchaniu  " << width << "x" << height << endl;
    }
    
    // Конструктор для квадрата (одно число)
    Rectangle(double size) : width(size), height(size) {
        cout << "Sozdan square " << width << "x" << height << endl;
    }
    
    // Конструктор для прямоугольника (два числа)
    Rectangle(double w, double h) : width(w), height(h) {
        cout << "Sozdan rectangle " << width << "x" << height << endl;
    }
    
    // Деструктор
    ~Rectangle() {
        cout << "Delered " << width << "x" << height << endl;
    }
    
    // Метод для вычисления площади
    double area() {
        return width * height;
    }
    
    // Метод для вычисления периметра
    double perimeter() {
        return 2 * (width + height);
    }
    
    // Проверка на квадрат
    bool is_square() {
        return width == height;
    }
    
    // Геттеры
    double get_width() {
        return width;
    }
    
    double get_height() {
        return height;
    }
    
    // Сеттеры с проверкой
    void set_width(double w) {
        if (w > 0) {
            width = w;
        } else {
            cout << "Error: shirina > 0" << endl;
        }
    }
    
    void set_height(double h) {
        if (h > 0) {
            height = h;
        } else {
            cout << "Error: visota > 0" << endl;
        }
    }
    
    // Метод масштабирования
    void scale(double factor) {
        if (factor > 0) {
            width *= factor;
            height *= factor;
            cout << "Mashtabirovana " << factor << " raz" << endl;
        } else {
            cout << "Error: coefficient mashtabirovania > 0" << endl;
        }
    }
    
    // Метод красивого вывода
    void print() {
        if (is_square()) {
            cout << "Square " << width << "x" << height;
        } else {
            cout << "Rectangle " << width << "x" << height;
        }
        cout << " (ploshad: " << area() << ", perimetr: " << perimeter() << ")" << endl;
    }
    
    // Метод сравнения прямоугольников
    int compare(const Rectangle& other) const {
        double this_area = width * height;
        double other_area = other.width * other.height;
        
        if (this_area > other_area) {
            return 1; // текущий больше
        } else if (this_area < other_area) {
            return -1; // текущий меньше
        } else {
            return 0; // равны
        }
    }
};

int main() {

    cout << "Test constructorov" << endl;
    Rectangle rect1; // по умолчанию
    Rectangle square(4.0); // квадрат
    Rectangle rect2(5.0, 3.0); // обычный
    
    cout << endl << "Test metodov" << endl;
    
    // Методы вычислений
    cout << "Ploshad rect1: " << rect1.area() << endl;
    cout << "Perimetr square: " << square.perimeter() << endl;
    cout << "Square? rect2: " << (rect2.is_square() ? "Yes" : "No") << endl;
    
    // Геттеры и сеттеры
    cout << endl << "Getteri i setteri" << endl;
    cout << "Shrina rect2: " << rect2.get_width() << endl;
    cout << "Visota rect2: " << rect2.get_height() << endl;
    
    rect2.set_width(10.0);
    rect2.set_height(-5.0); // Ошибка!
    cout << "New shirina rect2: " << rect2.get_width() << endl;
    
    // Масштабирование
    cout << endl << "Mashtabirovanie" << endl;
    square.print();
    square.scale(0.5); // Уменьшение
    square.print();
    square.scale(-2.0); // Ошибка!
    
    // Красивый вывод
    cout << endl << "Krasiviy vivod" << endl;
    rect1.print();
    square.print();
    rect2.print();
    
    // Сравнение прямоугольников
    cout << endl << "Sravnenie rectanglov" << endl;
    Rectangle rect3(6.0, 10.0); // Площадь 60
    Rectangle rect4(8.0, 6.0);  // Площадь 48
    Rectangle rect5(10.0, 6.0); // Площадь 60
    
    int result1 = rect3.compare(rect4); // 1 (rect3 > rect4)
    int result2 = rect4.compare(rect3); // -1 (rect4 < rect3)
    int result3 = rect3.compare(rect5); // 0 (rect3 == rect5)
    
    cout << "rect3.compare(rect4): " << result1 << endl;
    cout << "rect4.compare(rect3): " << result2 << endl;
    cout << "rect3.compare(rect5): " << result3 << endl;
    
    if (result1 > 0) {
        cout << "1>2" << endl;
    } else if (result1 < 0) {
        cout << "1<2" << endl;
    } else {
        cout << "==" << endl;
    }
    
    return 0;
}