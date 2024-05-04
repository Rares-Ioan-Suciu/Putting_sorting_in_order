#ifndef DATA_GENERATOR_H
#define DATA_GENERATOR_H
#define DATA_FILE "generated_data1.txt"
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cmath>


void generateSortedData(int dataSize);
void generateUniqueData(int dataSize);
void generateReverseData(int dataSize);
void generateNonUniqueData(int dataSize);
void generateAlmostSortedData(int dataSize);
void generateNegativeData(int dataSize);
void generateSparseData(int dataSize);
void generateData(const std::string& dataType,int dataSize);

#endif // DATA_GENERATOR_H

