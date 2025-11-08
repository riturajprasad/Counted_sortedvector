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
    bool isempty() const;
    int findIndex(const T& value) const;
    void insert(T value);
    bool find(T value) const;
    int count(T value) const;
    void erase(T value);
    void eraseall(T value);
    void clear();
    void printall() const;
    int total_size() const;
    int unique_size() const;
};

template <class T>
bool counted_sortedvector<T>::isempty() const
{
    if (data.empty()) cout << "counted_sortedvector is empty" << endl;
    return data.empty();
}

template <class T>
int counted_sortedvector<T>::findIndex(const T& value) const {
    int low = 0, high = data.size() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (data[mid].first == value) return mid;
        else if (data[mid].first < value) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

template <class T>
void counted_sortedvector<T>::insert(T value) {
    int index = findIndex(value);
    if (index != -1) {
        data[index].second++;
        return;
    }
    int pos = 0;
    while (pos < data.size() && data[pos].first < value) {
        pos++;
    }
    // insert of vector
    data.insert(data.begin() + pos, { value, 1 });
}

template <class T>
bool counted_sortedvector<T>::find(T value) const {
    if (isempty()) return false;
    return findIndex(value) != -1;
}

template <class T>
int counted_sortedvector<T>::count(T value) const {
    if (isempty()) return 0;
    int index = findIndex(value);
    if (index != -1) return data[index].second;
    return 0;
}

template <class T>
void counted_sortedvector<T>::erase(T value) {
    if (isempty()) return;
    int index = findIndex(value);
    if (index != -1) {
        data[index].second--;
        if (data[index].second == 0) {
            data.erase(data.begin() + index);
        }
    }
}

template <class T>
void counted_sortedvector<T>::eraseall(T value) {
    int index = findIndex(value);
    if (index != -1) {
        data.erase(data.begin() + index);
    }
}

template <class T>
void counted_sortedvector<T>::clear() {
    if (isempty()) return;
    data.clear();
}

template <class T>
void counted_sortedvector<T>::printall() const {
    if (isempty()) return;
    for (auto& p : data) {
        for (int i = 0; i < p.second; i++)
            cout << p.first << " ";
    }
    cout << endl;
}

template <class T>
int counted_sortedvector<T>::total_size() const {
    if (isempty()) return 0;
    int sum = 0;
    for (auto& p : data) sum += p.second;
    return sum;
}

template <class T>
int counted_sortedvector<T>::unique_size() const {
    if (isempty()) return 0;
    return data.size();
}