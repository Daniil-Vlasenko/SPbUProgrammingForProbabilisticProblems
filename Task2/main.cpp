#include <iostream>
#include <fstream>
#include <set>
#include "/usr/include/boost/algorithm/string/split.hpp"
#include "/usr/include/boost/algorithm/string/classification.hpp"


int main() {
    std::ifstream textFile("../text.txt");
    std::ifstream dictionaryFile("../dictionary.txt");
    std::ofstream new_textFile("../new_text.txt");
    std::string strTmp1, strTmp2;
    std::vector<std::string> wordsInLine;
    std::set<std::string> dictionary;

    // Читаем словарь.
    while(getline(dictionaryFile, strTmp1, '\n')) {
        dictionary.insert(strTmp1);
    }

    // Работаем с текстом.
    int intTmp;
    char charTmp;
    while(getline(textFile, strTmp1, '\n')) {
        // Разделяем строку по пробелам.
        boost::split(wordsInLine, strTmp1, boost::is_any_of(" "));
        for(std::string word: wordsInLine) {
            // Если встречается символ, запоминаем его и удаляем из слова.
            intTmp = word.find_first_of(".,!?:;");
            if(intTmp != -1) {
                charTmp = word.push_back();
                word.pop_back();
            }
            // Ищем слово в словаре.
        }
    }


    return 0;
}
