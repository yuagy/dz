#include <iostream>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <string>
#include <utility>
#include <windows.h>

using namespace std;

template<typename T>
class MiniSmartList {
private:
    vector<T> data_;

public:
    void push_back(const T& value) {
        data_.push_back(value);
    }

    void pop_back() {
        if (!data_.empty()) {
            data_.pop_back();
        }
    }

    size_t size() const {
        return data_.size();
    }

    void clear() {
        data_.clear();
    }

    template<typename U = T>
    enable_if_t<is_arithmetic_v<U>, U> 
    sum() const {
        U result = 0;
        for (const auto& val : data_) {
            result += val;
        }
        return result;
    }

    template<typename U = T>
    auto sort() -> decltype(declval<U>() < declval<U>(), void()) {
        std::sort(data_.begin(), data_.end());
    }

    
    template<typename U = T>
    auto print() const -> decltype(cout << declval<const U&>(), void()) {
        for (const auto& val : data_) {
            cout << val << " ";
        }
        cout << endl;
    }

    void debug_print() const {
        if constexpr (is_pointer_v<T>) {
            cout << "[ptr] ";
            for (const auto& val : data_) {
                cout << static_cast<const void*>(val) << " ";
            }
        } else {
            cout << "[val] ";
            for (const auto& val : data_) {
                cout << val << " ";
            }
        }
        cout << endl;
    }

    template<typename U>
    bool contains(U&& value) const {
        
        // снимаем ссылки и cv-квалификаторы с переданного аргумента
        // сначала remove_reference_t, потом remove_cv_t
        using CleanU = remove_cv_t<remove_reference_t<U>>;
        
        for (const auto& item : data_) {
            if (item == value) {
                return true;
            }
        }
        return false;
    }
};

struct NoPrint {}; // структура без operator<<
struct NoCompare {}; // структура без operator<

int main() {
    SetConsoleCP(65001);   
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, "Russian");
    cout << "=== Arithmetic Sum ===" << endl;
    MiniSmartList<int> intList;
    intList.push_back(10);
    intList.push_back(20);
    intList.push_back(30);
    cout << "Sum: " << intList.sum() << endl; 

    // MiniSmartList<string> strListBad;
    // strListBad.push_back("hi");
    // strListBad.sum(); // ошибка компиляции

    cout << "\n=== Sort ===" << endl;
    MiniSmartList<string> strList;
    strList.push_back("banana");
    strList.push_back("apple");
    strList.sort(); 
    strList.print(); 

    // MiniSmartList<NoCompare> ncList;
    // ncList.sort(); // ошибка компиляции

    cout << "\n=== Print ===" << endl;
    intList.print(); 

    // MiniSmartList<NoPrint> npList;
    // npList.push_back(NoPrint{});
    // npList.print(); // ошибка компиляции

    cout << "\n=== Debug Print ===" << endl;
    intList.debug_print(); 

    int x = 100;
    int y = 200;
    MiniSmartList<int*> ptrList;
    ptrList.push_back(&x);
    ptrList.push_back(&y);
    ptrList.debug_print(); 

    cout << "\n=== Contains ===" << endl;
    MiniSmartList<int> searchList;
    searchList.push_back(5);
    searchList.push_back(10);

    int a = 5;
    const int b = 10;
    
    cout << "Contains 5 (lvalue): " << searchList.contains(a) << endl;       
    cout << "Contains 10 (const lvalue): " << searchList.contains(b) << endl; 
    cout << "Contains 7 (rvalue): " << searchList.contains(7) << endl;        
    cout << "Contains 5 (moved): " << searchList.contains(move(a)) << endl; 

    return 0;
}