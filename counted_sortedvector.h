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
    int total_size() const;
    int unique_size() const;
    counted_sortedvector& merge(const counted_sortedvector& csv)
    {
        if (this == &csv) {
            for (auto& p : data)
                p.second *= 2;
            return *this;
        }

        for (const auto& p : csv)
            for (int i = 0; i < p.second; ++i)
                insert(p.first);
        return *this;
    }

    auto begin() { return data.begin(); }
    auto end() { return data.end(); }
    auto begin() const { return data.begin(); }
    auto end() const { return data.end(); }

    friend ostream& operator<<(ostream& out, const counted_sortedvector& csv)
    {
        for (const auto& p : csv)
            for (int i = 0; i < p.second; ++i)
                cout << p.first << " ";
        return out;
    }
};

template <class T>
bool counted_sortedvector<T>::isempty() const
{
    return data.empty();
}

template <class T>
int counted_sortedvector<T>::findIndex(const T& value) const {
    const auto it = lower_bound(data.begin(), data.end(), value,
        [](const pair<T, int>& p, const T& val) { return p.first < val; }
    );
    if (it != data.end() && it->first == value)
        return distance(data.begin(), it);
    return -1;
}

template <class T>
void counted_sortedvector<T>::insert(T value) {
    int index = findIndex(value);
    if (index != -1) {
        data[index].second++;
        return;
    }
    auto pos = lower_bound(data.begin(), data.end(), value,
        [](const pair<T, int>& p, const T& val) { return p.first < val; });
    data.insert(pos, { value, 1 });
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
    if (isempty()) return;
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
int counted_sortedvector<T>::total_size() const {
    if (isempty()) return 0;
    int sum = 0;
    for (const auto& p : data) sum += p.second;
    return sum;
}

template <class T>
int counted_sortedvector<T>::unique_size() const {
    if (isempty()) return 0;
    return data.size();
}