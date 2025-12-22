#include <iostream>
#include <stdexcept> 

template<typename T, int Capacity>
class Stack {
private:
    T data[Capacity];    // массив для хранения элементов
    int topIndex;        // индекс верхнего элемента

public:
    // Конструктор
    Stack() : topIndex(-1) {}

    // Добавление элемента в стек
    void push(const T& value) {
        if (full()) {
            throw std::overflow_error("Stack is full");
        }
        data[++topIndex] = value;
    }

    // Удаление и возврат верхнего элемента
    T pop() {
        if (empty()) {
            throw std::underflow_error("Stack is empty");
        }
        return data[topIndex--];
    }

    // Просмотр верхнего элемента без удаления
    const T& top() const {
        if (empty()) {
            throw std::underflow_error("Stack is empty");
        }
        return data[topIndex];
    }

    // Проверка, пуст ли стек
    bool empty() const {
        return topIndex == -1;
    }

    // Проверка, заполнен ли стек
    bool full() const {
        return topIndex == Capacity - 1;
    }

    // Текущий размер стека
    int size() const {
        return topIndex + 1;
    }
};

// Пример использования
int main() {
    try {
        // Пример 1: Стек целых чисел
        Stack<int, 5> intStack;
        
        // Добавление элементов
        intStack.push(10);
        intStack.push(20);
        intStack.push(30);
        
        // Проверка состояния
        std::cout << "Size: " << intStack.size() << std::endl;      
        std::cout << "Empty: " << intStack.empty() << std::endl;  
        std::cout << "Full: " << intStack.full() << std::endl;      
        
        // Работа с элементами
        std::cout << "Top: " << intStack.top() << std::endl;        
        std::cout << "Pop: " << intStack.pop() << std::endl;        
        std::cout << "Top: " << intStack.top() << std::endl;        
        
        // Пример 2: Стек строк
        Stack<std::string, 3> strStack;
        strStack.push("Hello");
        strStack.push("World");
        
        std::cout << "String stack top: " << strStack.top() << std::endl;  
        
        // Пример 3: Проверка ошибок
        Stack<int, 2> smallStack;
        smallStack.push(1);
        smallStack.push(2);
        smallStack.push(3);
        
        Stack<int, 2> emptyStack;
        emptyStack.pop();   
        emptyStack.top();  
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}