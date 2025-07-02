#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

template <typename T>
class Storage {
protected:
    std::vector<T> items;

public:
    Storage() = default;

    void loadFromFile(const std::string& filename);
    void addItem(const T& item);
    bool editItem(const std::string& id, const std::string& newLocation, time_t newTime);
    bool deleteItem(const std::string& id);
    void saveToFile(const std::string& filename) const;
    const std::vector<T>& getItems() const;
    bool exists(const std::string& id) const;
    const T* getById(const std::string& id) const;

    // Optional: generate next ID based on size
    std::string generateNextId(const std::string& prefix) const;
};

#include "Storage.tpp"
