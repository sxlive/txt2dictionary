#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <limits>

// 检查是否为标准的有效字符：字母、连字符和撇号
bool isValidWordChar(char c) {
    return std::isalpha(static_cast<unsigned char>(c)) || c == '-' || c == '\'';
}

// 过滤掉无效字符并返回有效单词，如果单词无效则返回空字符串
std::string filterWord(const std::string& word) {
    std::string result;
    for (char c : word) {
        if (isValidWordChar(c)) {
            result += c;
        }
        else {
            return "";  // 只要有一个无效字符，整个单词丢弃
        }
    }
    return result;
}

// 检查单词中是否包含撇号 (')
bool containsApostrophe(const std::string& word) {
    return word.find('\'') != std::string::npos;
}

// 处理文件的主函数
void processFile(const std::string& inputPath, const std::string& outputPath, int wTimes, int wLongs, bool includeCount) {
    std::ifstream inputFile(inputPath);
    if (!inputFile) {
        std::cerr << "Error opening input file: " << inputPath << std::endl;
        return;
    }
    else {
        std::cout << "Input file opened successfully!" << std::endl;
    }

    std::map<std::string, std::pair<std::string, int>> wordCount;  // 保存原始单词和计数
    std::string word;

    // 读取文件中的单词
    while (inputFile >> word) {
        std::string originalWord = word;  // 保留原始形式
        std::string cleanWord = filterWord(word);

        if (!cleanWord.empty() && cleanWord.length() > 1) {  // 丢弃单字母单词
            std::string lowerWord = cleanWord;
            for (char& c : lowerWord) {
                if (std::isalpha(static_cast<unsigned char>(c))) {
                    c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
                }
            }

            // 如果该单词尚未在map中出现，保存原始形式
            if (wordCount.find(lowerWord) == wordCount.end()) {
                wordCount[lowerWord] = { originalWord, 1 };  // 存储原始单词和计数
            }
            else {
                wordCount[lowerWord].second++;  // 增加计数
            }
        }
    }

    inputFile.close();

    if (wordCount.empty()) {
        std::cout << "No valid words found in the file." << std::endl;
        return;
    }

    // 筛选符合条件的单词
    std::vector<std::pair<std::string, std::pair<std::string, int>>> validWords;
    for (const auto& wc : wordCount) {
        if (!containsApostrophe(wc.first) && wc.second.second >= wTimes && wc.first.length() >= wLongs) {
            validWords.push_back(wc);
        }
    }

    if (validWords.empty()) {
        std::cout << "No words passed the filtering criteria." << std::endl;
        return;
    }

    // 按词频排序，词频相同时按字母顺序排序
    std::sort(validWords.begin(), validWords.end(), [](const auto& a, const auto& b) {
        return a.second.second == b.second.second ? a.first < b.first : a.second.second > b.second.second;
        });

    // 确定输出文件路径
    std::string outputFullPath = std::filesystem::path(inputPath).parent_path().string() + "\\" + outputPath;

    // 如果输出文件已存在，提示用户
    if (std::filesystem::exists(outputFullPath)) {
        std::cerr << "Output file already exists: " << outputFullPath << std::endl;
        return;
    }

    std::ofstream outputFile(outputFullPath);
    if (!outputFile) {
        std::cerr << "Error creating output file: " << outputFullPath << std::endl;
        return;
    }

    // 将结果写入输出文件
    for (const auto& wordPair : validWords) {
        if (includeCount) {
            outputFile << wordPair.second.first << " " << wordPair.second.second << std::endl;  // 保留原始单词和统计
        }
        else {
            outputFile << wordPair.second.first << std::endl;  // 只保留原始单词
        }
    }

    outputFile.close();
    std::cout << "Finished writing to output file." << std::endl;
}

// 获取合法的输入文件路径
std::string getValidInputFilePath() {
    std::string inputPath;
    while (true) {
        std::cout << "Enter input file path (or type 'exit' to quit): ";
        std::cin >> inputPath;

        if (inputPath == "exit") {
            return inputPath;
        }

        if (std::filesystem::exists(inputPath) && std::filesystem::is_regular_file(inputPath)) {
            return inputPath;
        }
        else {
            std::cerr << "Invalid file path. Please try again." << std::endl;
        }
    }
}

// 获取输出文件名
std::string getValidOutputFileName(const std::string& inputDir) {
    std::string outputFileName;
    while (true) {
        std::cout << "Enter output file name (in the same directory as input): ";
        std::cin >> outputFileName;

        if (!outputFileName.empty()) {
            return outputFileName;
        }
        else {
            std::cerr << "Output file name cannot be empty. Please try again." << std::endl;
        }
    }
}

// 获取正整数的输入
int getValidIntegerInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail() || value <= 0) {
            std::cin.clear();  // 清除错误标志
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 丢弃错误输入
            std::cerr << "Invalid input. Please enter a positive integer." << std::endl;
        }
        else {
            return value;
        }
    }
}

// 获取是否保留统计数据的输入
bool getIncludeCountOption() {
    char option;
    while (true) {
        std::cout << "Do you want to include word counts in the output? (y/n): ";
        std::cin >> option;
        if (option == 'y' || option == 'Y') {
            return true;
        }
        else if (option == 'n' || option == 'N') {
            return false;
        }
        else {
            std::cerr << "Invalid input. Please enter 'y' or 'n'." << std::endl;
        }
    }
}

// 主函数，循环处理用户输入
int main() {
    while (true) {
        std::string inputPath = getValidInputFilePath();
        if (inputPath == "exit") {
            break;
        }

        std::string outputFileName = getValidOutputFileName(std::filesystem::path(inputPath).parent_path().string());

        int wTimes = getValidIntegerInput("Enter minimum word occurrence threshold (wTimes): ");
        int wLongs = getValidIntegerInput("Enter minimum word length threshold (wLongs): ");

        bool includeCount = getIncludeCountOption();

        processFile(inputPath, outputFileName, wTimes, wLongs, includeCount);
    }

    std::cout << "Exiting program." << std::endl;
    return 0;
}
