#include <iostream>
#include <type_traits>
#include <string>
#include <windows.h>
using namespace std;

class Animal {
public:
    virtual ~Animal() = default;  
    
    virtual void makeSound() const {
        cout << "Animal sound" << endl;
    }
    
    virtual void move() const {
        cout << "Moving" << endl;
    }
};

class Cat : public Animal {
public:
    void makeSound() const override {
        cout << "Meow!" << endl;
    }
    
    void move() const override {
        cout << "Cat is walking" << endl;
    }
};

class Dog : public Animal {
public:
    void makeSound() const override {
        cout << "Woof!" << endl;
    }
    
    void move() const override {
        cout << "Dog is running" << endl;
    }
};

class Bird : public Animal {
public:
    void makeSound() const override {
        cout << "Chirp!" << endl;
    }
    
    void move() const override {
        cout << "Bird is flying" << endl;
    }
};

class Car {
public:
    void drive() const {
        cout << "Car is driving" << endl;
    }
};

template<typename T>
void feedAnimal(const T& animal) {
    if constexpr (is_base_of_v<Animal, T>) {
        cout << "Feeding the animal ";
        animal.makeSound();
        cout << "Animal is fed!" << endl;
    } else {
        static_assert(is_base_of_v<Animal, T>, "Ошибка: feedAnimal работает только с объектами типа Animal");
    }
}

template<typename T>
void checkAnimalType(const  string& typeName) {
    static_assert(is_base_of_v<Animal, T>, "Ошибка компиляции: тип должен быть наследником Animal");
    
    cout << "Тип " << typeName << " является животным" << endl;
}

int main() {
    SetConsoleCP(65001);    
    SetConsoleOutputCP(65001);
    cout << "--- ТЕСТИРОВАНИЕ ---\n\n";
    
    Cat cat;
    Dog dog;
    Bird bird;
    Car car;
    
    cout << "--- Проверка методов ---\n";
    cat.makeSound();   
    cat.move();        
    
    dog.makeSound();   
    dog.move();        
    
    bird.makeSound();  
    bird.move();       
    
    cout << "\n--- Проверка машины ---\n";
    car.drive();       
    
    cout << "\n--- feedAnimal с животными ---\n";
    feedAnimal(cat);   
    feedAnimal(dog);   
    feedAnimal(bird);  
    
    cout << "\n--- checkAnimalType с животными ---\n";
    checkAnimalType<Cat>("Cat");   
    checkAnimalType<Dog>("Dog");   
    checkAnimalType<Bird>("Bird"); 
    
    /*cout << "\n--- Попытка использовать с машиной  ---\n";
    feedAnimal(car);              
    checkAnimalType<Car>("Car");  */
    
    return 0;
}