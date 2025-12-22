#include <list>
#include <unordered_map>

class LRUCache {
private:
    int capacity;
    std::list<std::pair<int, int>> cacheList; // (key, value) в порядке использования
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> cacheMap; // key -> итератор в list

public:
    LRUCache(int capacity) : capacity(capacity) {}

    int get(int key) {
        // Ищем ключ в unordered_map за O(1) в среднем
        auto it = cacheMap.find(key);
        if (it == cacheMap.end()) {
            return -1; // ключа нет
        }
        // Перемещаем элемент в начало списка (самый недавний)
        cacheList.splice(cacheList.begin(), cacheList, it->second);
        return it->second->second; // возвращаем значение
    }

    void put(int key, int value) {
        auto it = cacheMap.find(key);
        if (it != cacheMap.end()) {
            // Ключ уже есть — обновляем значение и перемещаем в начало
            it->second->second = value;
            cacheList.splice(cacheList.begin(), cacheList, it->second);
            return;
        }

        // Ключа нет — добавляем новый
        if (cacheList.size() == capacity) {
            // Удаляем самый старый элемент (с конца списка)
            int oldKey = cacheList.back().first;
            cacheMap.erase(oldKey);
            cacheList.pop_back();
        }

        // Добавляем новый элемент в начало списка
        cacheList.emplace_front(key, value);
        cacheMap[key] = cacheList.begin();
    }
};
#include <list>
#include <unordered_map>

class LRUCache {
private:
    int capacity;
    std::list<std::pair<int, int>> cacheList; // (key, value) в порядке использования
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> cacheMap; // key -> итератор в list

public:
    LRUCache(int capacity) : capacity(capacity) {}

    int get(int key) {
        // Ищем ключ в unordered_map за O(1) в среднем
        auto it = cacheMap.find(key);
        if (it == cacheMap.end()) {
            return -1; // ключа нет
        }
        // Перемещаем элемент в начало списка (самый недавний)
        cacheList.splice(cacheList.begin(), cacheList, it->second);
        return it->second->second; // возвращаем значение
    }

    void put(int key, int value) {
        auto it = cacheMap.find(key);
        if (it != cacheMap.end()) {
            // Ключ уже есть — обновляем значение и перемещаем в начало
            it->second->second = value;
            cacheList.splice(cacheList.begin(), cacheList, it->second);
            return;
        }

        // Ключа нет — добавляем новый
        if (cacheList.size() == capacity) {
            // Удаляем самый старый элемент (с конца списка)
            int oldKey = cacheList.back().first;
            cacheMap.erase(oldKey);
            cacheList.pop_back();
        }

        // Добавляем новый элемент в начало списка
        cacheList.emplace_front(key, value);
        cacheMap[key] = cacheList.begin();
    }
};