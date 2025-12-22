#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>

using namespace std;


class Vehicle {
protected:
    string make;
    string model;
    int year;
    double fuelEfficiency;  

    Vehicle(const string& m, const string& mod, int y, double eff)
        : make(m), model(mod), year(y), fuelEfficiency(eff) {}

public:
    virtual ~Vehicle() = default;

    // Виртуальные методы 
    virtual void startEngine() = 0;
    virtual void stopEngine() = 0;
    virtual string getDescription() const = 0;
    virtual double calculateRange(double fuelAmount) const = 0;

    // Перегрузка оператора вывода
    friend ostream& operator<<(ostream& os, const Vehicle& v) {
        os << v.getDescription();
        return os;
    }
};


class Car : public Vehicle {
private:
    int numberOfDoors;
    double trunkCapacity;

public:
    Car(const string& m, const string& mod, int y, double eff, int doors, double trunk)
        : Vehicle(m, mod, y, eff), numberOfDoors(doors), trunkCapacity(trunk) {}

    void startEngine() override {
        cout << "Car " << make << " " << model << " engine started." << endl;
    }

    void stopEngine() override {
        cout << "Car " << make << " " << model << " engine stopped." << endl;
    }

    string getDescription() const override {
        return make + " " + model + " (" + to_string(year) + "), " + to_string(numberOfDoors) + " doors, trunk: " + to_string(trunkCapacity) + " L";
    }

    double calculateRange(double fuelAmount) const override {
        return fuelAmount * fuelEfficiency;
    }

    void openTrunk() {
        cout << "Trunk opened. Capacity: " << trunkCapacity << " L" << endl;
    }
};


class Truck : public Vehicle {
private:
    double cargoCapacity;
    bool hasTrailer;

public:
    Truck(const string& m, const string& mod, int y, double eff, double cargo, bool trailer)
        : Vehicle(m, mod, y, eff), cargoCapacity(cargo), hasTrailer(trailer) {}

    void startEngine() override {
        cout << "Truck " << make << " " << model << " engine started (loud rumble)." << endl;
    }

    void stopEngine() override {
        cout << "Truck " << make << " " << model << " engine stopped." << endl;
    }

    string getDescription() const override {
        string trailerInfo = hasTrailer ? " with trailer" : " without trailer";
        return make + " " + model + " (" + to_string(year) + "), cargo: " + to_string(cargoCapacity) + " kg" + trailerInfo;
    }

    double calculateRange(double fuelAmount) const override {
        return fuelAmount * fuelEfficiency * (hasTrailer ? 0.8 : 1.0);
    }

    void loadCargo(double weight) {
        cout << "Cargo loaded: " << weight << " kg (capacity: " << cargoCapacity << " kg)" << endl;
    }
};


class Motorcycle : public Vehicle {
private:
    string engineType;
    bool hasSideCar;

public:
    Motorcycle(const string& m, const string& mod, int y, double eff, const string& eType, bool sideCar)
        : Vehicle(m, mod, y, eff), engineType(eType), hasSideCar(sideCar) {}

    void startEngine() override {
        cout << "Motorcycle " << make << " " << model << " engine started (vroom!)." << endl;
    }

    void stopEngine() override {
        cout << "Motorcycle " << make << " " << model << " engine stopped." << endl;
    }

    string getDescription() const override {
        string sideCarInfo = hasSideCar ? " with sidecar" : " without sidecar";
        return make + " " + model + " (" + to_string(year) + "), engine: " + engineType + sideCarInfo;
    }

    double calculateRange(double fuelAmount) const override {
        return fuelAmount * fuelEfficiency;
    }

    void performWheelie() {
        cout << make << " " << model << " performs a wheelie!" << endl;
    }
};

// Фабричный метод
Vehicle* createVehicle(const string& type) {
    if (type == "Car") {
        return new Car("Toyota", "Camry", 2022, 15.5, 4, 500);
    } else if (type == "Truck") {
        return new Truck("Ford", "F-150", 2021, 8.5, 1500, true);
    } else if (type == "Motorcycle") {
        return new Motorcycle("Harley", "Davidson", 2023, 20, "V-Twin", false);
    } else {
        throw invalid_argument("Unknown vehicle type");
    }
}


int main() {
    // Создание объектов через фабрику
    vector<Vehicle*> vehicles;
    vehicles.push_back(createVehicle("Car"));
    vehicles.push_back(createVehicle("Truck"));
    vehicles.push_back(createVehicle("Motorcycle"));

    // Полиморфизм
    for (auto* v : vehicles) {
        v->startEngine();
        cout << *v << endl;
        cout << "Range with 50L fuel: " << v->calculateRange(50) << " km" << endl;
        v->stopEngine();
        cout << "---" << endl;
    }

    
    for (auto* v : vehicles) {
        delete v;
    }

    return 0;
}