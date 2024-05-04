#include <algorithm>
#include "Non-comparison.h"
#include <vector>
#include <climits>

void counting_sort(std::vector<int>& data)
{
    if (data.empty()) return;

    int max_element = *std::max_element(data.begin(), data.end());
    int min_element = *std::min_element(data.begin(), data.end());

    int range = max_element - min_element + 1;

    std::vector<int> count(range), output(data.size());

    for (int num : data) {
        ++count[num - min_element];
    }

    int index = 0;
    for (int i = 0; i < range; ++i) {
        while (count[i] > 0) {
            output[index] = i + min_element;
            ++index;
            --count[i];
        }
    }

    data = std::move(output);
}

void bucket_sort(std::vector<int>& data) {
    if (data.empty()) return;

    int max_element = *std::max_element(data.begin(), data.end());
    int min_element = *std::min_element(data.begin(), data.end());

    int bucket_range = 1000;
    int bucket_count = (max_element - min_element) / bucket_range + 1;

    std::vector<std::vector<int>> buckets(bucket_count);

    for (int num : data) {
        int bucket_index = (num - min_element) / (max_element - min_element) * bucket_count;
        buckets[bucket_index].push_back(num);
    }


    data.clear();


    for (auto& bucket : buckets) {
        if (!bucket.empty()) {
            counting_sort(bucket);
            data.insert(data.end(), bucket.begin(), bucket.end());
        }
    }
}

void counting_sort_by_digit(std::vector<int>& data, int exp) {
    int n = data.size();
    std::vector<int> output(n);
    std::vector<int> count(10, 0);


    for (int i = 0; i < n; ++i) {
        ++count[(data[i] / exp) % 10];
    }

    for (int i = 1; i < 10; ++i) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; --i) {
        output[count[(data[i] / exp) % 10] - 1] = data[i];
        --count[(data[i] / exp) % 10];
    }

    for (int i = 0; i < n; ++i) {
        data[i] = output[i];
    }
}

void radix_sort(std::vector<int>& data) {
    if (data.empty()) return;


    std::vector<int> negative, non_negative;
    for (int num : data) {
        if (num < 0) {
            negative.push_back(num);
        } else {
            non_negative.push_back(num);
        }
    }


    if (!negative.empty()) {

        for (int& num : negative) {
            num = std::abs(num);
        }

        for (int exp = 1; exp < INT_MAX; exp *= 10) {
            counting_sort_by_digit(negative, exp);
        }
        for (int& num : negative) {
            num = -num;
        }
    }

    if (!non_negative.empty()) {
        int max_non_neg = *std::max_element(non_negative.begin(), non_negative.end());
        for (int exp = 1; max_non_neg / exp > 0; exp *= 10) {
            counting_sort_by_digit(non_negative, exp);
        }
    }

    data.clear();
    data.reserve(negative.size() + non_negative.size());
    data.insert(data.end(), negative.begin(), negative.end());
    data.insert(data.end(), non_negative.begin(), non_negative.end());
}
