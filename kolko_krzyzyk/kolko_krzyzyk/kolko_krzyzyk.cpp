#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
import Menu;
import walidacjaPliku;

int main() {
    std::string filename = "results.txt";
    if (walidacjaDanych_z_Pliku(filename)) {
        std::cout << "All lines in the file have valid format." << std::endl;
    }
    else {
        std::cout << "Some lines in the file have invalid format." << std::endl;
    }
    Menu menu;
    menu.run();
    return 0;
}
