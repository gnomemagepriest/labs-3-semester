#pragma once
#include <vector>
#include <algorithm>
#include <unordered_map>

template <typename T>
class Inventory {
    //static_assert(is_base_of<T, Item>::value, "!");
private:
    std::vector<T> items;
public:
    Inventory();
    void addItem(const T& item);
    void removeItem(size_t index);
    T& getItem(size_t index);
    size_t size() const;
    std::string getDescription() const;
    std::vector<T> getItems();
    void sortItems();
    T popItem(const std::string& name);
};

template <typename T>
Inventory<T>::Inventory() {
    items.clear();
}

template <typename T>
void Inventory<T>::addItem(const T& item) {
    items.push_back(item);
}

template <typename T>
void Inventory<T>::removeItem(size_t index) {
    if (index < items.size()) {
        items.erase(items.begin() + index);
    }
}

template <typename T>
T& Inventory<T>::getItem(size_t index) {
    return items.at(index);
}

template <typename T>
size_t Inventory<T>::size() const {
    return items.size();
}

template <typename T>
std::string Inventory<T>::getDescription() const {
    std::string result = "Inventory:\n";
    for (const auto item : items) {
        result += "- " + item->getName() + "\n";
    }
    return result;
}

template<typename T>
std::vector<T> Inventory<T>::getItems() {
    return items;
}

template <typename T>
void Inventory<T>::sortItems() {
    std::sort(items.begin(), items.end(), [](const T a, const T b) {
        return a->getName() < b->getName();
        });
}

template <typename T>
T Inventory<T>::popItem(const std::string& name) {
    for (int i = 0; i < items.size(); i++) {
        if (items[i]->getName() == name) {
            T itemToDrop = items[i];
            removeItem(i);
            return itemToDrop;
        }
    }
    return nullptr;
}