#include <iostream>
#include <fstream>
#include <filesystem>
#include <regex>
#include <vector>
#include <string>

export module walidacjaPliku;

export bool walidacjaDanych_z_Pliku(const std::string& filename) {
    std::filesystem::path filePath = std::filesystem::current_path() / filename;
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file!" << std::endl;
        return false;
    }
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    std::regex pattern("^Zwyciezca: (Krzyzyk|Kolko|Remis), liczba ruchow: \\d+$");

    for (const auto& line : lines) {
        if (!std::regex_match(line, pattern)) {
            std::cerr << "Invalid format detected: " << line << std::endl;
            return false;
        }
    }
    return true;
}
