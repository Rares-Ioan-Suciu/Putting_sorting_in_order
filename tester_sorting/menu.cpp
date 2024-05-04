#include "menu.h"
#include <iostream>
#include <termios.h>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include <filesystem>
#include <algorithm>
#include <cstdio>

std::vector<std::string> selectedAlgorithms{};
std::vector<std::string> selectedDataTypes{};

void setNonCanonicalMode() {
    struct termios term{};
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void restoreCanonicalMode() {
    struct termios term{};
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= ICANON | ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
    setNonCanonicalMode();
#endif
}

void selectAlgorithmsForCategory(const std::vector<std::string>& algorithms) {
    std::vector<bool> selected(algorithms.size(), false);

    int currentAlgorithmIndex = 0;
    const int numAlgorithms = algorithms.size() + 2;

    while (true) {
        clearScreen();

        for (int i = 0; i < numAlgorithms; ++i) {
            if (i == currentAlgorithmIndex) {
                std::cout << "-> ";
            } else {
                std::cout << "   ";
            }
            if (i < algorithms.size()) {
                std::cout << algorithms[i] << '\n';
            } else if (i == algorithms.size()) {
                std::cout << "Add All\n";
            } else {
                std::cout << "Back\n";
            }
        }

        char key = getchar();
        if (key == 27) {
            getchar();
            switch (getchar()) {
                case 65:
                    currentAlgorithmIndex = (currentAlgorithmIndex - 1 + numAlgorithms) % numAlgorithms;
                    break;
                case 66:
                    currentAlgorithmIndex = (currentAlgorithmIndex + 1) % numAlgorithms;
                    break;
            }
        } else if (key == '\n') {
            if (currentAlgorithmIndex < algorithms.size()) {
                if (selected[currentAlgorithmIndex]) {
                    std::cout << "Algorithm '" << algorithms[currentAlgorithmIndex] << "' is already selected.\n";
                } else {
                    selected[currentAlgorithmIndex] = true;
                    selectedAlgorithms.push_back(algorithms[currentAlgorithmIndex]);
                    std::cout << "Algorithm '" << algorithms[currentAlgorithmIndex] << "' selected.\n";
                }
                std::cout << "Press Enter to continue selecting or press 'q' to exit this category.\n";
                char choice = getchar();
                if (choice == 'q' || choice == 'Q') {
                    break;
                }
            } else if (currentAlgorithmIndex == algorithms.size()) {
                for (int i = 0; i < algorithms.size(); ++i) {
                    selected[i] = true;
                    selectedAlgorithms.push_back(algorithms[i]);
                }
                std::cout << "All algorithms added.\n";
                std::cout << "Press Enter to continue selecting or press 'q' to exit this category.\n";
                char choice = getchar();
                if (choice == 'q' || choice == 'Q') {
                    break;
                }
            } else {

                return;
            }
        } else if (key == 'q' || key == 'Q') { // Quit key
            break;
        }
    }
}

void selectSortingAlgorithms() {
    int currentCategoryIndex = 0;
    const int numCategories = 6;

    std::vector<std::string> ON2Algorithms = {"Bubble Sort", "Insertion Sort", "Selection Sort", "Shell Sort"};
    std::vector<std::string> ONlogNAlgorithms = {"Heap Sort", "Merge Sort", "Quick Sort"};
    std::vector<std::string> NonCompAlgorithms = {"Counting Sort", "Bucket Sort", "Radix Sort"};
    std::vector<std::string> HybridAlgorithms = {"Timsort", "Introsort"};

    std::vector<std::vector<std::string>> algorithmCategories = {ON2Algorithms, ONlogNAlgorithms, NonCompAlgorithms, HybridAlgorithms};

    while (true) {
        system("clear");
        std::cout << "Select Sorting Algorithms:\n";
        for (int i = 0; i < numCategories; ++i) {
            if (i == currentCategoryIndex) {
                std::cout << "-> ";
            } else {
                std::cout << "   ";
            }
            switch (i) {
                case 0:
                    std::cout << "O(n^2) algorithms\n";
                    break;
                case 1:
                    std::cout << "O(nlogn) algorithms\n";
                    break;
                case 2:
                    std::cout << "Non-comparison sorting algorithms\n";
                    break;
                case 3:
                    std::cout << "Hybrid sorting algorithms\n";
                    break;
                case 4:
                    std::cout << "Select all algorithms\n";
                    break;
                case 5:
                    std::cout<<"Back\n";
                    break;
                default:
                    break;
            }
        }

        char key = getchar();
        if (key == 27) {
            getchar();
            switch (getchar()) {
                case 65:
                    currentCategoryIndex = (currentCategoryIndex - 1 + numCategories) % numCategories;
                    break;
                case 66:
                    currentCategoryIndex = (currentCategoryIndex + 1) % numCategories;
                    break;
            }
        } else if (key == '\n')
        {
                if (currentCategoryIndex == numCategories - 1)
            {
                return;
            }
                else if (currentCategoryIndex == numCategories - 2)
            {
                std::cout << "Adding all algorithms in this category...\n";
                for (const auto& algorithms : algorithmCategories)
                {
                    for (const auto& algorithm : algorithms)
                    {
                        selectedAlgorithms.push_back(algorithm);
                    }
                }
                std::cout << "All algorithms have been added.\n";
                std::cout << "Press Enter to continue...\n";
                getchar();
                return;
            }

            selectAlgorithmsForCategory(algorithmCategories[currentCategoryIndex]);
            break;
        }
    }
}

void selectDataTypes() {
    int currentDataTypeIndex = 0;
    const int numDataTypes = 9;

    while (true) {
        clearScreen();

        for (int i = 0; i < numDataTypes; ++i) {
            if (i == currentDataTypeIndex) {
                std::cout << "-> ";
            } else {
                std::cout << "   ";
            }
            switch (i) {
                case 0:
                    std::cout << "Sorted Data\n";
                    break;
                case 1:
                    std::cout << "Unique Data\n";
                    break;
                case 2:
                    std::cout << "Reverse Data\n";
                    break;
                case 3:
                    std::cout << "Non-unique Data\n";
                    break;
                case 4:
                    std::cout << "Almost Sorted Data\n";
                    break;
                case 5:
                    std::cout << "Negative Data\n";
                    break;
                case 6:
                    std::cout << "Sparse Data\n";
                    break;
                case 7:
                    std::cout <<"Select all\n";
                    break;
                case 8:
                    std::cout << "Back\n";
                    break;
                default:
                    break;
            }
        }

        char key = getchar();
        if (key == 27) {
            getchar();
            switch (getchar()) {
                case 65:
                    currentDataTypeIndex = (currentDataTypeIndex - 1 + numDataTypes) % numDataTypes;
                    break;
                case 66:
                    currentDataTypeIndex = (currentDataTypeIndex + 1) % numDataTypes;
                    break;
            }
        } else if (key == '\n') {
            switch (currentDataTypeIndex) {
                case 0:
                    if (std::find(selectedDataTypes.begin(), selectedDataTypes.end(), "Sorted Data") ==
                        selectedDataTypes.end()) {
                        selectedDataTypes.push_back("Sorted Data");
                        std::cout << "Selected data type: Sorted Data\n";
                    } else {
                        std::cout << "Data type 'Sorted Data' is already selected.\n";
                    }
                    break;
                case 1:
                    if (std::find(selectedDataTypes.begin(), selectedDataTypes.end(), "Unique Data") ==
                        selectedDataTypes.end()) {
                        selectedDataTypes.push_back("Unique Data");
                        std::cout << "Selected data type: Unique Data\n";
                    } else {
                        std::cout << "Data type 'Unique Data' is already selected.\n";
                    }
                    break;
                case 2:
                    if (std::find(selectedDataTypes.begin(), selectedDataTypes.end(), "Reverse Data") ==
                        selectedDataTypes.end()) {
                        selectedDataTypes.push_back("Reverse Data");
                        std::cout << "Selected data type: Reverse Data\n";
                    } else {
                        std::cout << "Data type 'Reverse Data' is already selected.\n";
                    }
                    break;
                case 3:
                    if (std::find(selectedDataTypes.begin(), selectedDataTypes.end(), "Non-unique Data") ==
                        selectedDataTypes.end()) {
                        selectedDataTypes.push_back("Non-unique Data");
                        std::cout << "Selected data type: Non-unique Data\n";
                    } else {
                        std::cout << "Data type 'Non-unique Data' is already selected.\n";
                    }
                    break;
                case 4:
                    if (std::find(selectedDataTypes.begin(), selectedDataTypes.end(), "Almost Sorted Data") ==
                        selectedDataTypes.end()) {
                        selectedDataTypes.push_back("Almost Sorted Data");
                        std::cout << "Selected data type: Almost Sorted Data\n";
                    } else {
                        std::cout << "Data type 'Almost Sorted Data' is already selected.\n";
                    }
                    break;
                case 5:
                    if (std::find(selectedDataTypes.begin(), selectedDataTypes.end(), "Negative Data") ==
                        selectedDataTypes.end()) {
                        selectedDataTypes.push_back("Negative Data");
                        std::cout << "Selected data type: Negative Data\n";
                    } else {
                        std::cout << "Data type 'Negative Data' is already selected.\n";
                    }
                    break;
                case 6:
                    if (std::find(selectedDataTypes.begin(), selectedDataTypes.end(), "Sparse Data") ==
                        selectedDataTypes.end()) {
                        selectedDataTypes.push_back("Sparse Data");
                        std::cout << "Selected data type: Sparse Data\n";
                    } else {
                        std::cout << "Data type 'Sparse Data' is already selected.\n";
                    }
                    break;
                case 7:
                {
                    std::cout << "Adding all data types...\n";
                    const std::vector<std::string> dataTypeNames = {
                            "Sorted Data", "Unique Data", "Reverse Data", "Non-unique Data",
                            "Almost Sorted Data", "Negative Data", "Sparse Data"
                    };

                    for (const std::string &dataType: dataTypeNames) {
                        if (std::find(selectedDataTypes.begin(), selectedDataTypes.end(), dataType) ==
                            selectedDataTypes.end()) {
                            selectedDataTypes.push_back(dataType);
                        } else {
                            std::cout << "Data type '" << dataType << "' is already selected.\n";
                        }
                    }

                    std::cout << "All data types have been added.\n";
                    std::cout << "Press Enter to continue...\n";
                    getchar();
                    return;
                 }
                case 8:
                    return;
            }
            std::cout << "Press Enter to continue...\n";
            getchar();

        }
    }
}

void viewSelectedParameters() {
    clearScreen();
    std::cout << "Selected Parameters:\n\n";


    std::cout << "Sorting Algorithms:\n";
    if (selectedAlgorithms.empty()) {
        std::cout << "None\n";
    } else {
        for (const auto& algorithm : selectedAlgorithms) {
            std::cout << "- " << algorithm << '\n';
        }
    }

    std::cout << '\n';

    std::cout << "Data Types:\n";
    if (selectedDataTypes.empty()) {
        std::cout << "None\n";
    } else {
        for (const auto& dataType : selectedDataTypes) {
            std::cout << "- " << dataType << '\n';
        }
    }

    std::cout << "\nPress Enter to continue...\n";
    getchar();
}

void editSelectedSortingAlgorithms() {
    int currentAlgorithmIndex = 0;
    int numAlgorithms = selectedAlgorithms.size() + 1;

    while (true) {
        clearScreen();

        std::cout << "Selected Sorting Algorithms:\n";
        for (int i = 0; i < numAlgorithms; ++i) {
            if (i == currentAlgorithmIndex) {
                std::cout << "-> ";
            } else {
                std::cout << "   ";
            }
            if (i < numAlgorithms - 1) {
                std::cout << selectedAlgorithms[i] << '\n';
            } else if(i == numAlgorithms-1){
                std::cout << "Back\n";
            }
        }

        char key = getchar();
        if (key == 27) {
            getchar();
            switch (getchar()) {
                case 65:
                    currentAlgorithmIndex = (currentAlgorithmIndex - 1 + numAlgorithms) % numAlgorithms;
                    break;
                case 66:
                    currentAlgorithmIndex = (currentAlgorithmIndex + 1) % numAlgorithms;
                    break;
            }
        } else if (key == '\n') {
            if (currentAlgorithmIndex < selectedAlgorithms.size()) {

                selectedAlgorithms.erase(selectedAlgorithms.begin() + currentAlgorithmIndex);
                --numAlgorithms;
            } else {

                return;
            }
        }
    }
}

void editSelectedDataTypes() {
    int currentDataTypeIndex = 0;
    int numDataTypes = selectedDataTypes.size() + 1;

    while (true) {
        clearScreen();

        std::cout << "Selected Data Types:\n";
        for (int i = 0; i < numDataTypes; ++i) {
            if (i == currentDataTypeIndex) {
                std::cout << "-> ";
            } else {
                std::cout << "   ";
            }
            if (i < numDataTypes - 1) {
                std::cout << selectedDataTypes[i] << '\n';
            } else if (i == numDataTypes - 1) {
                std::cout << "Back\n";
            }
        }

        char key = getchar();
        if (key == 27) {
            getchar();
            switch (getchar()) {
                case 65:
                    currentDataTypeIndex = (currentDataTypeIndex - 1 + numDataTypes) % numDataTypes;
                    break;
                case 66:
                    currentDataTypeIndex = (currentDataTypeIndex + 1) % numDataTypes;
                    break;
            }
        } else if (key == '\n') {
            if (currentDataTypeIndex < selectedDataTypes.size()) {

                selectedDataTypes.erase(selectedDataTypes.begin() + currentDataTypeIndex);
                --numDataTypes;
            } else {
                return;
            }
        }
    }
}

void editSelectedParameters() {
    int currentOptionIndex = 0;
    const int numOptions = 3;

    while (true) {
        clearScreen();

        std::cout << "Edit Selected Parameters:\n";
        for (int i = 0; i < numOptions; ++i) {
            if (i == currentOptionIndex) {
                std::cout << "-> ";
            } else {
                std::cout << "   ";
            }
            switch (i) {
                case 0:
                    std::cout << "Edit selected sorting algorithms\n";
                    break;
                case 1:
                    std::cout << "Edit selected data types\n";
                    break;
                case 2:
                    std::cout << "Back to the main menu\n";
                    break;
                default:
                    break;
            }
        }

        char key = getchar();
        if (key == 27) {
            getchar();
            switch (getchar()) {
                case 65:
                    currentOptionIndex = (currentOptionIndex - 1 + numOptions) % numOptions;
                    break;
                case 66:
                    currentOptionIndex = (currentOptionIndex + 1) % numOptions;
                    break;
            }
        } else if (key == '\n') {
            switch (currentOptionIndex) {
                case 0:

                    editSelectedSortingAlgorithms();
                    break;
                case 1:

                    editSelectedDataTypes();
                    break;
                case 2:

                    return;
                default:
                    break;
            }
        }
    }
}


void runAnalysis(const std::string& analysis_path , const std::string& path_csv, const std::string& path_py) {
    clearScreen();

    if(selectedAlgorithms.empty()) {
        std::cout << "Please select at least one algorithm\n";
        std::cout << "Press Enter to continue...\n";
        getchar();
        return;
    }
    if(selectedDataTypes.empty()) {
        std::cout << "Please select at least one type of data\n";
        std::cout << "Press Enter to continue...\n";
        getchar();
        return;
    }

    long long maxDataSize;
    float increaseFactor;
    restoreCanonicalMode();
    std::cout << "Enter maximum data size (must be a natural integer number smaller than 200 million): " << std::flush;
    while (!(std::cin >> maxDataSize) || maxDataSize <= 0 || maxDataSize >= 200'000'000) {
        std::cout << "Invalid input. Please enter a natual integer number smaller than 200 million: " << std::flush;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "Enter increase factor (should be a float between 1.0 and 10.0, we recommend not going over 2 for getting lots of tests): " << std::flush;
    while (!(std::cin >> increaseFactor) || increaseFactor <= 0 || increaseFactor > 10.0) {
        std::cout << "Invalid input. Please enter a float between 1.0 and 10.0: " << std::flush;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    getchar();
    std::cout << "Running Analysis...\n\n";

    if (access(analysis_path.c_str(), X_OK) == -1) {
        std::cerr << "Error: analysis_program executable not found.\n";
        return;
    }
    for (const auto& entry : std::filesystem::directory_iterator(path_csv))
    {
        if (entry.path().extension() == ".csv") {
            std::filesystem::remove(entry.path());
         }
    }

    int status;

    for (const auto& algorithm : selectedAlgorithms) {
        for (const auto& dataType : selectedDataTypes) {
            std::string algorithmFirstWord = algorithm.substr(0, algorithm.find(' '));
            std::string dataTypeFirstWord = dataType.substr(0, dataType.find(' '));

            // Modify command string to include maxDataSize and increaseFactor
            std::string command = analysis_path + "/analysis_program " + algorithmFirstWord + " " + dataTypeFirstWord + " " + std::to_string(maxDataSize) + " " + std::to_string(increaseFactor) + " " + path_csv;
            std::cout << "Running analysis for " << algorithm << " and " << dataType << "...\n";

            // Execute the command
            int status = std::system(command.c_str());
            if (status != 0) {
                std::cerr << "Error running analysis for " << algorithm << " and " << dataType << std::endl;
            }
        }
    }

    for (const auto& dataType : selectedDataTypes) {
        std::string dataTypeFirstWord = dataType.substr(0, dataType.find(' '));

        std::string pythonCommand = path_py +"/graphmaker.py " + dataTypeFirstWord + " " + path_csv;
        std::cout<< pythonCommand;
        std::cout << "Generating graph for " << dataType << "...\n";

        status = std::system(pythonCommand.c_str());
        if (status != 0) {
            std::cerr << "Error generating graph for " << dataType << std::endl;
        }
    }

    if(!selectedAlgorithms.empty() && !selectedDataTypes.empty())
    {
        std::cout << "\nAnalysis and graph generation complete!\n";
    }
    std::cout << "Press Enter to continue...\n";
    getchar();
}



void showMainMenu(const std::string& path_analysis, const std::string& path_csv, const std::string& path_py)
{
    int currentOption = 0;
    const int numOptions = 6;

    while (true) {
        clearScreen();
        std::cout << "Main Menu:\n";
        for (int i = 0; i < numOptions; ++i) {
            if (i == currentOption) {
                std::cout << "-> ";
            } else {
                std::cout << "   ";
            }
            switch (i) {
                case 0:
                    std::cout << "Select Sorting Algorithms\n";
                    break;
                case 1:
                    std::cout << "Select Data Types\n";
                    break;
                case 2:
                    std::cout << "View Selected Parameters\n";
                    break;
                case 3:
                    std::cout << "Edit Selected Parameters\n";
                    break;
                case 4:
                    std::cout << "Run Analysis\n";
                    break;
                case 5:
                    std::cout << "Quit Program\n";
                    break;
                default:
                    break;
            }
        }

        char key = getchar();
        if (key == 27) {
            getchar();
            switch (getchar()) {
                case 65:
                    currentOption = (currentOption - 1 + numOptions) % numOptions;
                    break;
                case 66:
                    currentOption = (currentOption + 1) % numOptions;
                    break;
            }
        } else if (key == '\n') {
            switch (currentOption) {
                case 0:
                    selectSortingAlgorithms();
                    break;
                case 1:
                    selectDataTypes();
                    break;
                case 2:
                    viewSelectedParameters();
                    break;
                case 3:
                    editSelectedParameters();
                    break;
                case 4:
                    runAnalysis(path_analysis, path_csv, path_py);
                    break;
                case 5:
                    restoreCanonicalMode();
                    return;
                default:
                    return;
            }
        }
    }
}
