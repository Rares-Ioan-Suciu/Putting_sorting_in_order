#include <future>
#include <chrono>
#include <fstream>
#include <iostream>
#include <csignal>
#include "sorting.h"
#include "data_generator.h"

bool segmentationFaultOccurred = false;

void segmentationFaultHandler(int signal) {
    segmentationFaultOccurred = true;
    std::cerr << "Segmentation fault occurred. Exiting.\n";
    std::exit(EXIT_FAILURE);
}

std::vector<int> readDataFromFile() {
    std::vector<int> data;
    std::ifstream inputFile(DATA_FILE);
    int num;
    while (inputFile >> num) {
        data.push_back(num);
    }
    inputFile.close();
    return data;
}


bool performSorting(const std::string& algorithm, std::ofstream& outputFile) {

    std::signal(SIGSEGV, segmentationFaultHandler);

    const int numRuns = 3;
    double totalTime = 0.0;

    if (outputFile.tellp() == 0) {

        outputFile << "Data Size,Sorting Time\n";
        outputFile.flush();
    }
    std::vector<int> data = readDataFromFile();
    for (int i = 0; i < numRuns; ++i) {

        auto startTime = std::chrono::steady_clock::now();

        std::future<void> sortingResult = std::async(std::launch::async, [&algorithm, &data]() {
            if (algorithm == "Bubble") {
                bubble_sort(data);
            } else if (algorithm == "Insertion") {
                insertion_sort(data);
            } else if (algorithm == "Selection") {
                selection_sort(data);
            } else if (algorithm == "Heap") {
                heap_sort(data);
            } else if (algorithm == "Merge") {
                merge_sort(data);
            } else if (algorithm == "Quick") {
                quick_sort(data);
            } else if (algorithm == "Shell") {
                shell_sort(data);
            } else if (algorithm == "Counting") {
                counting_sort(data);
            } else if (algorithm == "Bucket") {
                bucket_sort(data);
            } else if (algorithm == "Radix") {
                radix_sort(data);
            } else if (algorithm == "Timsort") {
                timsort(data);
            } else if (algorithm == "Introsort") {
                introsort(data);
            } else {
                std::cerr << "Error: Unsupported sorting algorithm\n";
                return;
            }
        });

        std::future_status status = sortingResult.wait_for(std::chrono::minutes(3));
        if (status == std::future_status::ready) {

            auto endTime = std::chrono::steady_clock::now();
            auto elapsedTime = std::chrono::duration<double>(endTime - startTime);
            totalTime += elapsedTime.count();
        } else if (status == std::future_status::timeout) {

            std::cerr << "Error: Sorting process timed out.\n";
            outputFile.flush();

            return false;
        } else {

            std::cerr << "Error: Unknown future status.\n";
            outputFile << "Unknown error occurred for " << algorithm << " sorting algorithm\n";
            outputFile.flush();
            return false;
        }
    }


    double averageTime = totalTime / numRuns;


    outputFile <<  data.size() << "," << averageTime*1000<<"\n";
    outputFile.flush();

    return !segmentationFaultOccurred;
}
