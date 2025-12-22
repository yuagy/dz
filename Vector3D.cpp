#include <iostream>
#include <cmath>
#include <cassert>

using namespace std;


class Vector3D {
private:
    double x, y, z;
    mutable double cached_magnitude;
    mutable bool cache_valid;
    static int total_vectors;

public:
    // Конструктор
    Vector3D(double x = 0.0, double y = 0.0, double z = 0.0)
        : x(x), y(y), z(z), cache_valid(false) {
        total_vectors++;
    }

    // Конструктор копирования
    Vector3D(const Vector3D& other)
        : x(other.x), y(other.y), z(other.z), cache_valid(false) {
        total_vectors++;
    }

    // Деструктор
    ~Vector3D() {
        total_vectors--;
    }

    // Получение длины вектора с кешированием
    double getMagnitude() const {
        if (!cache_valid) {
            cached_magnitude = sqrt(x * x + y * y + z * z);
            cache_valid = true;
        }
        return cached_magnitude;
    }

    // Нормализация вектора
    Vector3D normalized() const {
        double mag = getMagnitude();
        if (mag == 0.0) {
            return Vector3D(0, 0, 0); 
        }
        return Vector3D(x / mag, y / mag, z / mag);
    }

    // Статический метод для скалярного произведения
    static double dotProduct(const Vector3D& a, const Vector3D& b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    // Функтор: проверка, равен ли хотя бы один компонент значению
    bool operator()(double component_value) const {
        return (x == component_value) || (y == component_value) || (z == component_value);
    }

    // Перегрузка оператора сложения
    Vector3D operator+(const Vector3D& other) const {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }

    // Перегрузка оператора вычитания
    Vector3D operator-(const Vector3D& other) const {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }

    // Перегрузка оператора умножения на скаляр
    Vector3D operator*(double scalar) const {
        return Vector3D(x * scalar, y * scalar, z * scalar);
    }

    // Перегрузка оператора сравнения (с учетом погрешности)
    bool operator==(const Vector3D& other) const {
        const double epsilon = 1e-9;
        return abs(x - other.x) < epsilon &&
               abs(y - other.y) < epsilon &&
               abs(z - other.z) < epsilon;
    }

    // Перегрузка оператора неравенства через ==
    bool operator!=(const Vector3D& other) const {
        return !(*this == other);
    }

    // Статический метод для получения количества векторов
    static int getTotalVectors() {
        return total_vectors;
    }

    // Дружественные объявления
    friend ostream& operator<<(ostream& os, const Vector3D& vec);
    friend class Vector3DTest;
};

// Инициализация статической переменной
int Vector3D::total_vectors = 0;

// Перегрузка оператора вывода
ostream& operator<<(ostream& os, const Vector3D& vec) {
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}


class Vector3DTest {
private:
    // Приватный метод проверки компонента
    static bool validateComponent(double component) {
        return !isnan(component) && !isinf(component);
    }

public:
    // Тест статического счетчика
    static void testStaticCounter() {
        int initial = Vector3D::getTotalVectors();
        {
            Vector3D v1(1, 2, 3);
            Vector3D v2(4, 5, 6);
            assert(Vector3D::getTotalVectors() == initial + 2);
        }
        assert(Vector3D::getTotalVectors() == initial);
        cout << "testStaticCounter: OK\n";
    }

    // Тест механизма кеширования
    static void testCachingMechanism() {
        Vector3D v(3, 4, 0); 
        double mag1 = v.getMagnitude();
        double mag2 = v.getMagnitude(); 
        assert(mag1 == 5.0);
        assert(mag2 == 5.0);
        cout << "testCachingMechanism: OK\n";
    }

    // Тест сложения векторов
    static void testVectorAddition() {
        Vector3D v1(1, 2, 3);
        Vector3D v2(4, 5, 6);
        Vector3D sum = v1 + v2;
        assert(sum == Vector3D(5, 7, 9));
        cout << "testVectorAddition: OK\n";
    }

    // Тест вычитания векторов
    static void testVectorSubtraction() {
        Vector3D v1(5, 7, 9);
        Vector3D v2(1, 2, 3);
        Vector3D diff = v1 - v2;
        assert(diff == Vector3D(4, 5, 6));
        cout << "testVectorSubtraction: OK\n";
    }

    // Тест умножения на скаляр
    static void testScalarMultiplication() {
        Vector3D v(1, 2, 3);
        Vector3D scaled = v * 2.5;
        assert(scaled == Vector3D(2.5, 5, 7.5));
        cout << "testScalarMultiplication: OK\n";
    }

    // Тест операторов сравнения
    static void testEqualityOperator() {
        Vector3D v1(1.0, 2.0, 3.0);
        Vector3D v2(1.0, 2.0, 3.0);
        Vector3D v3(1.1, 2.0, 3.0);
        assert(v1 == v2);
        assert(v1 != v3);
        cout << "testEqualityOperator: OK\n";
    }

    // Тест скалярного произведения
    static void testDotProduct() {
        Vector3D v1(1, 2, 3);
        Vector3D v2(4, 5, 6);
        double dot = Vector3D::dotProduct(v1, v2);
        assert(dot == 32); 
        cout << "testDotProduct: OK\n";
    }

    // Тест нормализации
    static void testNormalization() {
        Vector3D v(3, 4, 0);
        Vector3D norm = v.normalized();
        double mag = norm.getMagnitude();
        assert(abs(mag - 1.0) < 1e-9);
        cout << "testNormalization: OK\n";
    }

    // Тест функтора
    static void testFunctionalObject() {
        Vector3D v(1, 2, 3);
        assert(v(2) == true);  
        assert(v(5) == false); 
        cout << "testFunctionalObject: OK\n";
    }

    // Запуск всех тестов
    static void runAllTests() {
        testStaticCounter();
        testCachingMechanism();
        testVectorAddition();
        testVectorSubtraction();
        testScalarMultiplication();
        testEqualityOperator();
        testDotProduct();
        testNormalization();
        testFunctionalObject();
        cout << "\nAll tests passed successfully!\n";
    }
};

// ===================== MAIN =====================
int main() {
    // Демонстрация работы класса
    cout << "=== Demonstration Vector3D ===\n";

    Vector3D v1(1, 2, 3);
    Vector3D v2(4, 5, 6);

    cout << "v1 = " << v1 << endl;
    cout << "v2 = " << v2 << endl;

    Vector3D sum = v1 + v2;
    cout << "v1 + v2 = " << sum << endl;

    Vector3D diff = v1 - v2;
    cout << "v1 - v2 = " << diff << endl;

    Vector3D scaled = v1 * 2.5;
    cout << "v1 * 2.5 = " << scaled << endl;

    cout << "Length v1: " << v1.getMagnitude() << endl;
    cout << "Normalized v1: " << v1.normalized() << endl;

    cout << "dot product v1 и v2: "
         << Vector3D::dotProduct(v1, v2) << endl;

    cout << "Functor check v1(2): " << (v1(2) ? "true" : "false") << endl;

    cout << "\nNumber of vectors in memory:"
         << Vector3D::getTotalVectors() << endl;

    cout << "\nTest\n";
    Vector3DTest::runAllTests();

    return 0;
}