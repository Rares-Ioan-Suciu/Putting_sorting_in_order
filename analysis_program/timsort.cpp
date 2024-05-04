#include <vector>
#include <algorithm>
#include "timsort.h"

const int RUN = 32;

void insertionSorttim(std::vector<int>& data, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int temp = data[i];
        int j = i - 1;
        while (j >= left && data[j] > temp) {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = temp;
    }
}

void mergetim(std::vector<int>& data, int l, int m, int r) {
    int len1 = m - l + 1, len2 = r - m;
    std::vector<int> left(len1), right(len2);
    for (int i = 0; i < len1; i++)
        left[i] = data[l + i];
    for (int i = 0; i < len2; i++)
        right[i] = data[m + 1 + i];

    int i = 0, j = 0, k = l;

    while (i < len1 && j < len2) {
        if (left[i] <= right[j]) {
            data[k] = left[i];
            i++;
        } else {
            data[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < len1) {
        data[k] = left[i];
        k++;
        i++;
    }

    while (j < len2) {
        data[k] = right[j];
        k++;
        j++;
    }
}

void timsort(std::vector<int>& data) {
    int n = data.size();

    for (int i = 0; i < n; i += RUN)
        insertionSorttim(data, i, std::min((i + RUN - 1), (n - 1)));

    for (int size = RUN; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = std::min((left + 2 * size - 1), (n - 1));
            if (mid < right)
                mergetim(data, left, mid, right);
        }
    }
}