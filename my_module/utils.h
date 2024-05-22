#pragma once
#include <vector>

inline std::vector<int> add_arrays(const std::vector<int>& a, const std::vector<int>& b) {
    std::vector<int> result;
    for (std::size_t i = 0; i < a.size(); i++) {
        result.push_back(a[i] + b[i]);
    }
    return result;
}
