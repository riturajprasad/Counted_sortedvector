#pragma once
#include <vector>
#include <algorithm>
using namespace std;

template <class T>
class count_sortedvector {
private:
    vector<pair<T, int>> data;
public:
    count_sortedvector() {}
    ~count_sortedvector() {}
    count_sortedvector(const count_sortedvector& csv) : data(csv.data) {}
    count_sortedvector& operator=(const count_sortedvector& csv)
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

private:
    class value_iterator {
    private:
        typename vector<pair<T, int>>::iterator it;
        int offset;
    public:
        value_iterator(typename vector<pair<T, int>>::iterator _it, int _offset = 0)
            : it(_it), offset(_offset) {
        }

        T operator*() const { return it->first; }

        value_iterator& operator++() {
            offset++;
            if (offset >= it->second) {
                ++it;
                offset = 0;
            }
            return *this;
        }

        bool operator!=(const value_iterator& other) const {
            return it != other.it || offset != other.offset;
        }
    };

public:
    value_iterator begin() { return value_iterator(data.begin(), 0); }
    value_iterator end() { return value_iterator(data.end(), 0); }

    using pair_iterator = typename vector<pair<T, int>>::iterator;
    using const_pair_iterator = typename vector<pair<T, int>>::const_iterator;

    pair_iterator begin_pairs() { return data.begin(); }
    pair_iterator end_pairs() { return data.end(); }

    const_pair_iterator begin_pairs() const { return data.begin(); }
    const_pair_iterator end_pairs()   const { return data.end(); }
};

template <class T>
bool count_sortedvector<T>::isempty() const
{
    return data.empty();
}

template <class T>
int count_sortedvector<T>::findIndex(const T& value) const {
    auto it = lower_bound(
        data.begin(), data.end(),
        make_pair(value, 0),
        [](const pair<T, int>& a, const pair<T, int>& b) {
            return a.first < b.first;
        });

    if (it != data.end() && it->first == value)
        return it - data.begin();
    return -1;
}

template <class T>
void count_sortedvector<T>::insert(T value) {
    int index = findIndex(value);
    if (index != -1) {
        data[index].second++;
    }
    else {
        auto it = lower_bound(
            data.begin(), data.end(),
            make_pair(value, 1),
            [](const pair<T, int>& a, const pair<T, int>& b) {
                return a.first < b.first;
            }
        );
        data.insert(it, { value, 1 });
    }
}

template <class T>
bool count_sortedvector<T>::find(T value) const {
    if (isempty()) return false;
    return findIndex(value) != -1;
}

template <class T>
int count_sortedvector<T>::count(T value) const {
    if (isempty()) return 0;
    int index = findIndex(value);
    if (index != -1) return data[index].second;
    return 0;
}

template <class T>
void count_sortedvector<T>::erase(T value) {
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
void count_sortedvector<T>::eraseall(T value) {
    if (isempty()) return;
    int index = findIndex(value);
    if (index != -1) {
        data.erase(data.begin() + index);
    }
}

template <class T>
void count_sortedvector<T>::clear() {
    data.clear();
}

template <class T>
int count_sortedvector<T>::total_size() const {
    int sum = 0;
    for (auto& p : data) sum += p.second;
    return sum;
}

template <class T>
int count_sortedvector<T>::unique_size() const {
    return data.size();
}