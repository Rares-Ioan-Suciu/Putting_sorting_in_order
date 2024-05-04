#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include <map>


enum class SortingCategory {
    O_N_Squared,
    O_N_Log_N,
    Non_Comparison,
    Hybrid
};

enum class AlgorithmCategory { ON2, ONlogN, NonComp, Hybrid };


extern std::map<SortingCategory, std::vector<std::string>> sortingAlgorithms;

void clearScreen();
void setNonCanonicalMode();
void restoreCanonicalMode();
void showMainMenu(const std::string& , const std::string& , const std::string&);
void selectSortingAlgorithms();
void selectDataTypes();
void viewSelectedParameters();
void editSelectedSortingAlgorithms();
void editSelectedDataTypes();
void editSelectedParameters();
void runAnalysis(const std::string& , const std::string& , const std::string&);
void selectAlgorithmsForCategory(const std::vector<std::string>& algorithms);

#endif // MENU_H
