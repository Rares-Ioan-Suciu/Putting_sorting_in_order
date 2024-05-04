#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "data_generator.h"
#include "sorting.h"

std::string generateOutputFileName(const std::string& algorithm, const std::string& dataType) {
    std::stringstream ss;
    ss << "analysis_" << algorithm << "_" << dataType << ".csv";
    return ss.str();
}

int main(int argc, char* argv[])
{
    if (argc != 6)
    {
        std::cerr << "Usage: ./analysis_program <sorting_algorithm> <data_type> max_size increasing_factor <csv_path>\n";
        return 1;
    }

    const std::string algorithm = argv[1];
    const std::string dataType = argv[2];
    double max_size = std::stod(argv[3]);
    double increasing_factor = std::stod(argv[4]);
    std::string path_csv = argv[5];
    double size = 10.0;
    bool ok = true;
    std::ofstream outputFile(generateOutputFileName(algorithm, dataType));

    while (size <= max_size)
    {
        generateData(dataType, static_cast<int>(size));
        ok = performSorting(algorithm, outputFile);
        if(!ok)
            break;
        if ((int)size == (int)(size * increasing_factor))
            size = size * increasing_factor + size;
        else
            size *= increasing_factor;

        size = (int)size;
        std::cout<<size<<std::endl;
        std::cout.flush();
    }
    std::cout << "\nAnalysis complete!\n";
    std::cout << "Results saved to " << generateOutputFileName(algorithm, dataType) << "\n";
    return 0;
}
