#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>


bool isNumber(const std::string& s) {
    long double ld;
    return((std::istringstream(s) >> ld).eof());
}

int readFile(std::string fileName) {
    std::vector<std::string> columnsNames;
    std::vector<std::vector<double>> columns;
    std::ifstream fin(fileName);
    int nColumns = 0, nRows = 0;

    if(!fin.is_open())
        throw std::runtime_error("Could not open file");

    // Читаем названия признаков.
    std::string tmp1, tmp2;
    getline(fin, tmp1);
    if(tmp1.empty())
        throw std::logic_error("The file is empty.");
    std::stringstream sin1(tmp1);
    while(getline(sin1, tmp2, '\t')) {
        ++nColumns;
        columnsNames.push_back(tmp2);
    }
    columns.resize(nColumns);

    // Читаем идивидов.
    while(getline(fin, tmp1)) {
        std::stringstream sin2(tmp1);
        for (int i = 0; i < nColumns; ++i) {
            sin2 >> tmp2;
            if(!isNumber(tmp2)) {
                throw std::logic_error("There is not a double value in column " + std::to_string(i) +
                                        " and row " + std::to_string(nRows));
            }
            columns[i].push_back(std::stod(tmp2));
        }
        ++nRows;
    }

    for(int i = 0; i < nColumns; ++i) {
        std::cout << columnsNames[i] << " ";
        for(auto j: columns[i]) {
            std::cout << j << " ";
        }
        std::cout << "\n";
    }

    fin.close();
}

int main() {
    try {
        readFile("../file.txt");
    }
    catch (std::exception &ex) {
        std::cout << "Ouch! That hurts, because: " << ex.what() << "!\n";
    }
    return 0;
}
