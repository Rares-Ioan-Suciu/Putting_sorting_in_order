#include <iostream>
#include <vector>
#include "menu.h"

int main(int argc, char* argv[]) {
    setNonCanonicalMode();

    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <analysis_program_path> <csv_directory_path> <python_script_path>\n";
        return 1;
    }

    // Extract command-line arguments
    const std::string analysisProgramPath = argv[1];
    const std::string csvDirectoryPath = argv[2];
    const std::string python_path = argv[3];


    // Call the main menu function with the provided paths
    showMainMenu(analysisProgramPath, csvDirectoryPath, python_path);

    restoreCanonicalMode();

    return 0;
}

