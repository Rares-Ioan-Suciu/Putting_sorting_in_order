#include <vector>
#include "O(nlogn).h"

void heapify(std::vector<int>& data, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && data[l] > data[largest]) {
        largest = l;
    }

    if (r < n && data[r] > data[largest]) {
        largest = r;
    }

    if (largest != i) {
        std::swap(data[i], data[largest]);
        heapify(data, n, largest);
    }
}

void heap_sort(std::vector<int>& data)
{
    int n = data.size();
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(data, n, i);
    }
    for (int i = n - 1; i > 0; --i) {
        std::swap(data[0], data[i]);
        heapify(data, i, 0);
    }
}

void merge(std::vector<int>& data, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i) {
        L[i] = data[left + i];
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = data[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            data[k] = L[i];
            ++i;
        } else {
            data[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        data[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        data[k] = R[j];
        ++j;
        ++k;
    }
}

void merge_sort_helper(std::vector<int>& data, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort_helper(data, left, mid);
        merge_sort_helper(data, mid + 1, right);
        merge(data, left, mid, right);
    }
}

void merge_sort(std::vector<int>& data) {
    merge_sort_helper(data, 0, data.size() - 1);
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivot = arr[(low + high) / 2];
        int i = low - 1;
        int j = high + 1;
        while (true) {
            do {
                i++;
            } while (arr[i] < pivot);

            do {
                j--;
            } while (arr[j] > pivot);

            if (i >= j)
                break;

            std::swap(arr[i], arr[j]);
        }
        quickSort(arr, low, j);
        quickSort(arr, j + 1, high);
    }
}

void quick_sort(std::vector<int>& arr)
{
    quickSort(arr, 0, arr.size());
}

void shell_sort(std::vector<int>& data) {
    int n = data.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            int temp = data[i];
            int j;
            for (j = i; j >= gap && data[j - gap] > temp; j -= gap) {
                data[j] = data[j - gap];
            }
            data[j] = temp;
        }
    }
}
