#include <cmath>
#include <algorithm>
#include <vector>
#include "introsort.h"

void swapValue(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

void insertionSortintro(std::vector<int>& arr, int left, int right)
{
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int partitionintro(std::vector<int>& arr, int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

int medianOfThree(std::vector<int>& arr, int a, int b, int c)
{
    if (arr[a] < arr[b] && arr[b] < arr[c])
        return b;

    if (arr[a] < arr[c] && arr[c] <= arr[b])
        return c;

    if (arr[b] <= arr[a] && arr[a] < arr[c])
        return a;

    if (arr[b] < arr[c] && arr[c] <= arr[a])
        return c;

    if (arr[c] <= arr[a] && arr[a] < arr[b])
        return a;

    if (arr[c] <= arr[b] && arr[b] <= arr[a])
        return b;

    return -1;
}

void introsortUtil(std::vector<int>& arr, int begin, int end, int depthLimit)
{
    int size = end - begin;

    if (size < 16) {
        insertionSortintro(arr, begin, end);
        return;
    }

    if (depthLimit == 0) {
        std::make_heap(arr.begin() + begin, arr.begin() + end + 1);
        std::sort_heap(arr.begin() + begin, arr.begin() + end + 1);
        return;
    }

    int pivotIndex = medianOfThree(arr, begin, begin + size / 2, end);
    swapValue(arr[pivotIndex], arr[end]);

    int partitionIndex = partitionintro(arr, begin, end);
    introsortUtil(arr, begin, partitionIndex - 1, depthLimit - 1);
    introsortUtil(arr, partitionIndex + 1, end, depthLimit - 1);
}

void introsort(std::vector<int>& data)
{
    int depthLimit = 2 * log(data.size());
    introsortUtil(data, 0, data.size() - 1, depthLimit);
}
