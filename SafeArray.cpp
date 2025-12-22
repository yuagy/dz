#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cstring>

class SafeArray {
private:
    int* data;
    size_t size;

public:
    // Конструктор
    explicit SafeArray(size_t size) : size(size) {
        if (size <= 0) {
            throw std::invalid_argument("The array size must be external");
        }
        data = new int[size](); 
    }

    // Конструктор копирования 
    SafeArray(const SafeArray& other) : size(other.size) {
        data = new int[size];
        std::copy(other.data, other.data + size, data);
    }

    // Оператор присваивания 
    SafeArray& operator=(SafeArray other) {
        swap(other);
        return *this;
    }

    // Обмен (гарантия отсутствия исключений)
    void swap(SafeArray& other) noexcept {
        std::swap(data, other.data);
        std::swap(size, other.size);
    }

    // Метод изменения размера
    void resize(size_t newSize) {
        if (newSize > 1000) {
            throw std::length_error("The new size exceeds the maximum allowed (1000)");
        }

        int* newData = new int[newSize]();
        size_t copySize = std::min(size, newSize);
        std::copy(data, data + copySize, newData);

        delete[] data;
        data = newData;
        size = newSize;
    }

    // Оператор доступа с проверкой границ
    int& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("The index is out of bounds of the array.");
        }
        return data[index];
    }

    // Константная версия 
    const int& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index is out of array bounds");
        }
        return data[index];
    }

    // Получение размера
    size_t getSize() const noexcept {
        return size;
    }

    // Деструктор 
    ~SafeArray() noexcept {
        delete[] data;
    }
};

// Пример использования и тестирования
int main() {
    try {

        // Тест Нормальное создание
        SafeArray arr(5);
        for (size_t i = 0; i < arr.getSize(); ++i) {
            arr[i] = static_cast<int>(i * 10);
        }

        // Тест Изменение размера
        arr.resize(8);
        std::cout << "New size: " << arr.getSize() << std::endl;


        // Тест Копирование и присваивание
        SafeArray arr2 = arr;
        arr2[0] = 100;

        SafeArray arr3(3);
        arr3 = arr2;

        // Вывод содержимого arr3
        std::cout << "Contents of arr3: ";
        for (size_t i = 0; i < arr3.getSize(); ++i) {
            std::cout << arr3[i] << " ";
        }
        std::cout << std::endl;

    } catch (const std::invalid_argument& e) {
        std::cerr << "Argument error: " << e.what() << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Boundary Error:" << e.what() << std::endl;
    } catch (const std::length_error& e) {
        std::cerr << "Size Error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Standard error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error!" << std::endl;
    }

    return 0;
}