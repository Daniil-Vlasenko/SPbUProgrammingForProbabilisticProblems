#include <iostream>
#include <fstream>
#include "/usr/include/boost/algorithm/string/split.hpp"
#include "/usr/include/boost/algorithm/string/classification.hpp"

int main() {
    std::ifstream fin("../text.txt");
    std::ofstream fout("../new_text.txt");
    std::string tmp1, tmp2;
    std::vector<std::string> wordsInLine;

    while(getline(fin, tmp1, '\t')) {
        boost::split(wordsInLine, tmp1, boost::is_any_of(" ,.;:?!\"\n"), boost::token_compress_on );

    }


    return 0;
}
