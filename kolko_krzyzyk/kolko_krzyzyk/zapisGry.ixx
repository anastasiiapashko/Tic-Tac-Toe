import <iostream>;
import <fstream>;
import <filesystem>;
import <vector>;
import <string>;
import <concepts>; // Importujemy bibliotekę konceptów

export module zapisGry;

// Koncepty dla odpowiednich typów
template<typename T>
concept BoolType = std::same_as<T, bool>;

template<typename T>
concept IntType = std::same_as<T, int>;

export class zapisGry {
private:
    std::ofstream file;
    std::vector<std::string> results; // Wektor do przechowywania wyników

public:
    zapisGry() {
        std::filesystem::path filePath = std::filesystem::current_path() / "results.txt";
        file.open(filePath, std::ios_base::app);
        if (!file.is_open()) {
            std::cerr << "Failed to open file!" << std::endl;
            exit(1);
        }
    }

    ~zapisGry() {
        if (file.is_open()) {
            file.close();
        }
    }

    // Funkcja zapisRezultatu z zastosowaniem konceptów
    void zapisRezultatu(BoolType auto win, IntType auto moves, IntType auto winningPlayer) {
        //auto end = std::chrono::high_resolution_clock::now();

        std::string result = "";

        // Komunikat potwierdzający działanie konceptów
        std::cout << "zapisRezultatu called with: win = " << win << ", moves = " << moves << ", winningPlayer = " << winningPlayer << std::endl;


        if (win) {
            if (winningPlayer == 1) {
                result += "Zwyciezca: Krzyzyk";
            }
            else if (winningPlayer == 2) {
                result += "Zwyciezca: Kolko";
            }
        }
        else {
            result += "Zwyciezca: Remis";
        }

        result += ", liczba ruchow: " + std::to_string(moves);
        results.push_back(result); // Dodajemy wynik do wektora
    }

    void zapisDoPliku() {
        for (const auto& result : results) {
            file << result << std::endl;
        }
        results.clear(); // Czyścimy wektor po zapisie do pliku
    }
};
