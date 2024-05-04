#ifndef ANALYSIS_PROGRAM_TIMSORT_H
#define ANALYSIS_PROGRAM_TIMSORT_H

#include <vector>

void insertionSorttim(std::vector<int>& data, int left, int right);


void mergetim(std::vector<int>& data, int l, int m, int r);


void timsort(std::vector<int>& data);

#endif //ANALYSIS_PROGRAM_TIMSORT_H
