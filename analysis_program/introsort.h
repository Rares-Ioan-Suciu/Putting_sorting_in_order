#ifndef ANALYSIS_PROGRAM_INTROSORT_H
#define ANALYSIS_PROGRAM_INTROSORT_H

#include <vector>


void swapValue(int& a, int& b);


 void insertionSortintro(std::vector<int>& arr, int left, int right);


int partitionintro(std::vector<int>& arr, int low, int high);


int medianOfThree(std::vector<int>& arr, int a, int b, int c);


void introsortUtil(std::vector<int>& arr, int begin, int end, int depthLimit);


void introsort(std::vector<int>& data);

#endif //ANALYSIS_PROGRAM_INTROSORT_H
