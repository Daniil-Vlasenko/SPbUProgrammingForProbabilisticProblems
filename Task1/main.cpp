#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>


bool isNumber(const std::string& s) {
    int countOfPoints = 0;
    for(char const &ch : s) {
        if(ch == '.')
            ++countOfPoints;
        if(std::isdigit(ch) == 0 and ch != '.' or countOfPoints > 1)
            return false;
    }
    return true;
}

int main() {
    std::vector<std::string> columnsNames;
    std::vector<std::vector<double>> columns;
    std::ifstream fin("../file.txt");
    int count = 0;

    try {
        if (!fin.is_open())
            throw(1);

        // Читаем названия признаков.
        std::string tmp1, tmp2;
        getline(fin, tmp1);
        if(tmp1.size() == 0)
            throw(2);
        std::stringstream sin1(tmp1);
        while (getline(sin1, tmp2, '\t')) {
            ++count;
            columnsNames.push_back(tmp2);
        }
        columns.resize(count);

        // Читаем идивидов.
        double tmp3;
        while (getline(fin, tmp1)) {
            std::stringstream sin2(tmp1);
            for (int i = 0; i < count; ++i) {
                sin2 >> tmp2;
                if(!isNumber(tmp2))
                    throw 3;
                columns[i].push_back(std::stod(tmp2));
            }
        }
    }
    catch(int error) {
        switch(error) {
            case 1:
                std::cout << "The file was not found.";
                break;
            case 2:
                std::cout << "The file is empty.";
                break;
            case 3:
                std::cout << "One of the fields is not a number.";
                break;
            default:
                std::cout << "Something went wrong.";
        }
        return error;
    }
    for(int i = 0; i < count; ++i) {
        std::cout << columnsNames[i] << " ";
        for(auto j: columns[i]) {
            std::cout << j << " ";
        }
        std::cout << "\n";
    }

    fin.close();
    return 0;
}
