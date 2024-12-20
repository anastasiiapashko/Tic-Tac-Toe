// Importuj potrzebne pliki nagłówkowe
import <SFML/Graphics.hpp>;
import <iostream>;

// Importuj definicję klasy Komunikator
import Komunikator;

// Zdefiniuj moduł Plansza
export module Plansza;

// Zdefiniuj klasę Plansza
export class Plansza {
public:
    enum class Pole { None, Cross, Circle };

private:
    std::vector<std::vector<Pole>> board;
    int gridSize;
    RuchKolka komunikatKolka; // Obiekt RuchKolka
    RuchKrzyzyka komunikatKrzyzyka; // Obiekt RuchKrzyzyka

public:
    // Konstruktor Plansza
    Plansza(int size) : gridSize(size), board(size, std::vector<Pole>(size, Pole::None)) {}

    // Metoda getSize
    int getSize() const {
        return gridSize;
    }

    // Metoda getPole
    Pole getPole(int x, int y) const {
        return board[y][x];
    }

    // Metoda setPole
    void setPole(int x, int y, Pole symbol) {
        board[y][x] = symbol;
    }

    // Metoda isFull
    bool isFull() const {
        for (const auto& row : board) {
            for (const auto& pole : row) {
                if (pole == Pole::None) {
                    return false;
                }
            }
        }
        return true;
    }

    
    // Metoda drawBoard
    void drawBoard(sf::RenderWindow& window) const {
        window.clear(sf::Color::White);

        int cellSize = 600 / gridSize;

        sf::RectangleShape square(sf::Vector2f(cellSize, cellSize));
        square.setFillColor(sf::Color::Transparent);
        square.setOutlineThickness(2.f);
        square.setOutlineColor(sf::Color::Black);

        for (int i = 0; i < gridSize; ++i) {
            for (int j = 0; j < gridSize; ++j) {
                square.setPosition(j * cellSize, i * cellSize);
                window.draw(square);

                Plansza::Pole pole = getPole(j, i);
                if (pole == Plansza::Pole::Cross) {
                    drawCross(window, j * cellSize, i * cellSize, cellSize);
                }
                else if (pole == Plansza::Pole::Circle) {
                    drawCircle(window, j * cellSize, i * cellSize, cellSize);
                }
            }
        }
    }


    // Metoda drawCross
    void drawCross(sf::RenderWindow& window, float x, float y, int size) const {
        sf::VertexArray cross(sf::Lines, 4);
        cross[0].position = sf::Vector2f(x + size * 0.1, y + size * 0.1);
        cross[1].position = sf::Vector2f(x + size * 0.9, y + size * 0.9);
        cross[2].position = sf::Vector2f(x + size * 0.1, y + size * 0.9);
        cross[3].position = sf::Vector2f(x + size * 0.9, y + size * 0.1);
        cross[0].color = sf::Color::Red;
        cross[1].color = sf::Color::Red;
        cross[2].color = sf::Color::Red;
        cross[3].color = sf::Color::Red;
        window.draw(cross);
    }

    // Metoda drawCircle
    void drawCircle(sf::RenderWindow& window, float x, float y, int size) const {
        sf::CircleShape circle(size * 0.4);
        circle.setFillColor(sf::Color::Transparent);
        circle.setOutlineThickness(3);
        circle.setOutlineColor(sf::Color::Blue);
        circle.setPosition(x + size * 0.1, y + size * 0.1);
        window.draw(circle);
    }

    // Metoda getCellSize
    int getCellSize() const {
        return 600 / gridSize;
    }

    void clearBoard() {
        for (auto& row : board) {
            for (auto& pole : row) {
                pole = Pole::None;
            }
        }
    }
};
