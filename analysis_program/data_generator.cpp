#include <numeric>
#include "data_generator.h"
#include <unordered_set>
#include <random>
#include <iomanip>

void generateSortedData(int dataSize) {

    std::ofstream outputFile(DATA_FILE, std::ios::app);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int currentNumber = 1 + std::rand() % 10000;

    for (int i = 0; i < dataSize; ++i) {
        outputFile << currentNumber << " ";
        int stepSize = 1 + std::rand() % 100;
        currentNumber += stepSize;
    }

    outputFile << "\n";
    outputFile.close();
}
void generateUniqueData(int dataSize) {
    // Open the file in truncation mode
    std::ofstream outputFile(DATA_FILE);

    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open file for writing.\n";
        return;
    }

    std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));

    std::unordered_set<int> generatedValues;

    while (generatedValues.size() < dataSize) {
        int randomValue = rng();
        if (generatedValues.insert(randomValue).second) {
            outputFile << randomValue << " ";
        }
    }

    // Close the file
    outputFile.close();
}
void generateReverseData(int dataSize) {
    std::ofstream outputFile(DATA_FILE, std::ios::app);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open data file for writing." << std::endl;
        return;
    }

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int currentNumber = 10000 - (std::rand() % 10000); // Start from a random number in the range

    for (int i = 0; i < dataSize; ++i) {
        outputFile << currentNumber << " ";
        int stepSize = 1 + std::rand() % 100;
        currentNumber -= stepSize;
    }

    outputFile << "\n";
    outputFile.close();
}
void generateNonUniqueData(int dataSize) {
    std::ofstream outputFile(DATA_FILE, std::ios::app);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open data file for writing." << std::endl;
        return;
    }

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::vector<int> numbers;

    // Generate random numbers
    for (int i = 0; i < dataSize; ++i) {
        int num = std::rand() % 10000;
        numbers.push_back(num);
    }

    for (int i = 0; i < dataSize / 10; ++i) {
        int index = std::rand() % dataSize;
        numbers.push_back(numbers[index]);
    }

    std::shuffle(numbers.begin(), numbers.end(), std::default_random_engine(std::time(nullptr)));
    for (int num : numbers) {
        outputFile << num << " ";
    }

    outputFile << "\n";
    outputFile.close();
}
void generateAlmostSortedData(int dataSize) {
    std::ofstream outputFile(DATA_FILE, std::ios::app);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open data file for writing." << std::endl;
        return;
    }

    std::vector<int> numbers(dataSize);
    int stepSize = 2; // Start with a step size of 2
    int currentNumber = 1;
    for (int i = 0; i < dataSize; ++i) {
        numbers[i] = currentNumber;
        currentNumber += stepSize;
        stepSize = (std::rand() % 10) + 1; // Randomly change the step size between 1 and 10
    }

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for (int i = 0; i < dataSize / 10; ++i) { // Introduce disorder in approximately 10% of the data
        int index1 = std::rand() % dataSize;
        int index2 = std::rand() % dataSize;
        std::swap(numbers[index1], numbers[index2]);
    }

    // Write numbers to the file
    for (int num : numbers) {
        outputFile << num << " ";
    }

    outputFile << "\n";
    outputFile.close();
}

void generateNegativeData(int dataSize) {
    std::ofstream outputFile(DATA_FILE, std::ios::app);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open data file for writing." << std::endl;
        return;
    }
    std::srand(static_cast<unsigned int>(std::time(nullptr)));


    for (int i = 0; i < dataSize; ++i) {
        int randomInt = -1 * (std::rand() % 1000000 + 1); // Generates integers between -1 and -100
        outputFile << randomInt << " ";
    }

    outputFile << "\n";
    outputFile.close();
}
void generateSparseData(int dataSize) {
    std::ofstream outputFile(DATA_FILE, std::ios::app);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open data file for writing." << std::endl;
        return;
    }
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int i = 0; i < dataSize; ++i) {

        int randomNumber = std::rand() % 10;

        if (randomNumber < 7) {
            outputFile << 0 << " ";
        } else {

            int randomNonZero = std::rand() % 10000000 + 1;
            outputFile << randomNonZero << " ";
        }
    }

    outputFile << "\n";
    outputFile.close();
}
void generateData(const std::string& dataType, int dataSize)
{
    std::ofstream outputFile(DATA_FILE);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open file for writing.\n";
        return;
    }
    outputFile.close();
    if (dataType == "Sorted") {
        generateSortedData(dataSize);
    } else if (dataType == "Unique") {
        generateUniqueData(dataSize);
    } else if (dataType == "Reverse") {
        generateReverseData(dataSize);
    } else if (dataType == "Non-unique") {
        generateNonUniqueData(dataSize);
    } else if (dataType == "Almost") {
        generateAlmostSortedData(dataSize);
    } else if (dataType == "Negative") {
        generateNegativeData(dataSize);
    } else if (dataType == "Sparse") {
        generateSparseData(dataSize);
    }
}

