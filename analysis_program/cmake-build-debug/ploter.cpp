#include <iostream>
#include <fstream>
#include <string>

// Function to generate Gnuplot script
void generateGnuplotScript(const std::string& inputFile) {
    std::ofstream scriptFile("plot_script.gp");
    scriptFile << "set term wxt\n"; // Set terminal to wxt for displaying in a window
    scriptFile << "set title 'Data Plot'\n";
    scriptFile << "set xlabel 'X'\n";
    scriptFile << "set ylabel 'Y'\n";
    scriptFile << "plot '" << inputFile << "' with lines\n";
    scriptFile << "pause -1\n"; // Wait indefinitely until user input
    scriptFile.close();
}
int main() {
    std::string inputFile = "/home/rares655/analysis_program/cmake-build-debug/analysis_Quick_Unique.csv";
    std::string gnuplotPath = "/usr/bin/gnuplot"; // Full path to Gnuplot executable

    // Generate Gnuplot script
    generateGnuplotScript(inputFile);

    // Execute Gnuplot to plot the graph
    std::string command = gnuplotPath + " plot_script.gp";
    int result = system(command.c_str());

    if (result == 0) {
        std::cout << "Plotting completed successfully." << std::endl;
    } else {
        std::cerr << "Error executing plotting program." << std::endl;
    }

    return 0;
}

