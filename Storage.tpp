#pragma once

#include <algorithm>

template <typename T>
void Storage<T>::loadFromFile(const std::string& filename) {
    // Open the file and read data format specific to T
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string id, location;
    time_t time;
    while (file >> id >> location >> time) {
        items.emplace_back(id, location, time);
    }
}

template <typename T>
void Storage<T>::addItem(const T& item) {
    items.push_back(item);
}

template <typename T>
bool Storage<T>::editItem(const std::string& id, const std::string& newLocation, time_t newTime) {
    for (auto& item : items) {
        if (item.getId() == id) {
            item.setLocation(newLocation);
            item.setTime(newTime);
            return true;
        }
    }
    return false;
}

template <typename T>
bool Storage<T>::deleteItem(const std::string& id) {
    auto it = std::remove_if(items.begin(), items.end(),
                             [&](const T& item) { return item.getId() == id; });
    if (it != items.end()) {
        items.erase(it, items.end());
        return true;
    }
    return false;
}

template <typename T>
void Storage<T>::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    for (const auto& item : items) {
        file << item.getId() << " " << item.getLocation() << " " << item.getTime() << "\n";
    }
}

template <typename T>
const std::vector<T>& Storage<T>::getItems() const {
    return items;
}

template <typename T>
bool Storage<T>::exists(const std::string& id) const {
    for (const auto& item : items) {
        if (item.getId() == id) return true;
    }
    return false;
}

template <typename T>
const T* Storage<T>::getById(const std::string& id) const {
    for (const auto& item : items) {
        if (item.getId() == id) return &item;
    }
    return nullptr;
}

template <typename T>
std::string Storage<T>::generateNextId(const std::string& prefix) const {
    return prefix + std::to_string(items.size() + 1);
}
