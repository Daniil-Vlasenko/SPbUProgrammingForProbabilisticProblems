#include <iostream>
#include <fstream>
#include <set>
#include "/usr/include/boost/algorithm/string/split.hpp"
#include "/usr/include/boost/algorithm/string/classification.hpp"


bool stupidAlignment(std::string dicWord, std::string newWord) {
    if(abs(dicWord.size() - newWord.size()) > 1)
        return false;

    int length = dicWord.size(), count = 0;
    for(int i = 0; i < length; ++i) {
        if(dicWord[i] != newWord[i]) {
            ++count;
            if(count > 1)
                return false;
            if(dicWord.size() == newWord.size())
                newWord[i] = dicWord[i];
            if(dicWord.size() > newWord.size())
                newWord.insert(i, &dicWord[i]);
            if(dicWord.size() < newWord.size())
                newWord.erase(i, 1);
        }
    }
    return true;
}

int main() {
    std::ifstream textFile("../text.txt");
    std::ifstream dictionaryFile("../dictionary.txt");
    std::ofstream new_textFile("../new_text.txt");
    std::string oldStr, newStr;
    std::vector<std::string> wordsInLine;
    std::set<std::string> dictionary;

    // Читаем словарь.
    while(getline(dictionaryFile, oldStr, '\n')) {
        dictionary.insert(oldStr);
    }

    // Работаем с текстом.
    int intTmp;
    while(getline(textFile, oldStr, '\n')) {
        newStr = "";
        // Разделяем строку по пробелам.
        boost::split(wordsInLine, oldStr, boost::is_any_of(" "));
        for(std::string word: wordsInLine) {
            // Если встречается синтаксический символ, запоминаем его и удаляем из слова.
            std::string charTmp = "";
            intTmp = word.find_first_of(".,!?:;");
            if(intTmp != -1) {
                charTmp = word.back();
                word.pop_back();
            }
            // Ищем слово в словаре.
            if(dictionary.find(word) != dictionary.end()) {
                newStr += word + charTmp + ' ';
                continue;
            }
            // Если слово не найдено, ищем, на что оно похоже.
            for(auto wordInD: dictionary) {
                std::string isAddNewWord = "";
                if(!stupidAlignment(wordInD, word)) {
                    std::cout << "Do you want to add the new word to the dictionary? (y/n):";
                    std::cin >> isAddNewWord;
                    if(isAddNewWord == "y") {
                        dictionary.insert(word);
                        newStr += word + charTmp + ' ';
                    }
                    else {
                        newStr += word + charTmp + ' ';
                    }
                    continue;
                }
                std::string isReplaceNewWord = "";
                std::cout << "Perhaps instead of \"" + word + "\" you meant \"" + wordInD + "\"? (y/n):";
                std::cin >> isReplaceNewWord;
                if(isReplaceNewWord == "y") {
                    newStr += word + charTmp + ' ';
                    continue;
                }
                std::cout << "Do you want to add the new word to the dictionary? (y/n):";
                std::cin >> isAddNewWord;
                if(isAddNewWord == "y") {
                    dictionary.insert(word);
                    newStr += word + charTmp + ' ';
                }
                else {
                    newStr += word + charTmp + ' ';
                }
            }
        }
        
    }


    return 0;
}
