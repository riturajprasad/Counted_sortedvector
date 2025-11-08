#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template <class T>
class counted_sortedvector {
private:
    vector<pair<T, int>> data;
public:
    counted_sortedvector(){}
    ~counted_sortedvector(){}
    counted_sortedvector(const counted_sortedvector &csv) : data(csv.data) {}
    counted_sortedvector& operator=(const counted_sortedvector& csv)
    {
        if (this != &csv)
        {
            data = csv.data;
        }
        return *this;
    }
public:
    void insert(T value);
    bool find(T value) const;
    int count(T value) const;
    void printall() const;
    int size(T value) const;
    int findIndex(const T& value) const;
    void erase(T value);
    void clear(T value);
};