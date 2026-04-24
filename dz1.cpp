#include <iostream>
#include <string>

using namespace std;

template<typename T>
class Printer {
    T value;
public:
    Printer(T v) : value(v) {}

    void print() const {
        cout << "Обычный вывод " << value << endl;
    }
};

template<>
class Printer<bool> {
    bool value;
public:
    Printer(bool v) : value(v) {}

    void print() const {
        cout << (value ? "true" : "false") << endl;
    }
};

template<typename T>
class Printer<T*> {
    T* ptr;
public:
    Printer(T* p) : ptr(p) {}

    void print() const {
        if (ptr == nullptr) {
            cout << "Address: nullptr, Value: null" << endl;
        } else {
            cout << "Address: " << ptr << " Value: " << *ptr << endl;
        }
    }
};

int main() {
    Printer<int> p1(42);
    p1.print(); 

    Printer<bool> p2(true);
    p2.print();  
    Printer<bool> p3(false);
    p3.print();  

    int x = 100;
    Printer<int*> p4(&x);
    p4.print(); 

    return 0;
}