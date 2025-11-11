#pragma once
#include <vector>
#include <algorithm>
using namespace std;

template <class T>
class count_sortedvector {
private:
    vector<pair<T, int>> data;

public:
    // Rule of 3
    count_sortedvector() {}
    ~count_sortedvector() {}
    count_sortedvector(const count_sortedvector& csv) : data(csv.data) {}
    count_sortedvector& operator=(const count_sortedvector& csv)
    {
        if (this != &csv)
            data = csv.data;
        return *this;
    }

    // Basic utilities
    bool isempty() const {
        return data.empty();
    }

    int findIndex(const T& value) const {
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

    void insert(T value) {
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
                });
            data.insert(it, { value, 1 });
        }
    }

    bool find(T value) const {
        return findIndex(value) != -1;
    }

    int count(T value) const {
        int index = findIndex(value);
        if (index != -1) return data[index].second;
        return 0;
    }

    void erase(T value) {
        int index = findIndex(value);
        if (index != -1) {
            data[index].second--;
            if (data[index].second == 0)
                data.erase(data.begin() + index);
        }
    }

    void eraseall(T value) {
        int index = findIndex(value);
        if (index != -1)
            data.erase(data.begin() + index);
    }

    void clear() {
        data.clear();
    }

    int total_size() const {
        int sum = 0;
        for (auto& p : data) sum += p.second;
        return sum;
    }

    int unique_size() const {
        return data.size();
    }

    // ----------------------------
    // ✅ Value Iterator (iterator over expanded values)
    // ----------------------------
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

    value_iterator begin() { return value_iterator(data.begin(), 0); }
    value_iterator end() { return value_iterator(data.end(), 0); }

    // ----------------------------
    // ✅ Pair Iterator (like map)
    // ----------------------------
    using pair_iterator = typename vector<pair<T, int>>::iterator;
    using const_pair_iterator = typename vector<pair<T, int>>::const_iterator;

    pair_iterator begin_pairs() { return data.begin(); }
    pair_iterator end_pairs() { return data.end(); }

    const_pair_iterator begin_pairs() const { return data.begin(); }
    const_pair_iterator end_pairs()   const { return data.end(); }
};
