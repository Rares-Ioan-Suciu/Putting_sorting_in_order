#ifndef ANALYSIS_PROGRAM_SORTING_H
#define ANALYSIS_PROGRAM_SORTING_H
#include <future>
#include <chrono>
#include <iostream>
#include "data_generator.h"
#include "timsort.h"
#include "introsort.h"
#include "O(n^2).h"
#include "O(nlogn).h"
#include "Non-comparison.h"
#include <fstream>


std::vector<int> readDataFromFile();

bool performSorting(const std::string& algorithm, std::ofstream& outputFile);
#endif //ANALYSIS_PROGRAM_SORTING_H
