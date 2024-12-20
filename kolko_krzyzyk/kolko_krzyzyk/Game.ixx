
import <SFML/Graphics.hpp>;
import <iostream>;
#include <vector>
import Gracz;
import Plansza;
import Checker;
import zapisGry;
import Komunikator;
export module Game;


export class Game {
public:
    enum class Player { Human1, Human2 };

private:
    Plansza plansza;
    Player currentPlayer;
    Gracz gracz1;
    Gracz gracz2;
    sf::RenderWindow window;
    bool gameOver;
    zapisGry logger;
    int moveCount;

    RuchKolka komunikatKolka;
    RuchKrzyzyka komunikatKrzyzyka;
    WygralKolko komunikatWygralKolko;
    WygralKrzyzyk komunikatWygralKrzyzyk;
    Remis komunikatRemis;

public:
    Game()
        : plansza(3),
        gracz1(Gracz::Symbol::Cross),
        gracz2(Gracz::Symbol::Circle),
        currentPlayer(Player::Human1),
        window(sf::VideoMode(600, 700), "Tic-Tac-Toe"),
        gameOver(false),
        moveCount(0)
    {
        komunikatKrzyzyka.ustawKomunikat("Krzyzyka");
    }

    void run() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                else if (event.type == sf::Event::MouseButtonPressed && !gameOver) {
                    handleMouseClick(event.mouseButton.x, event.mouseButton.y);
                }
                else if (event.type == sf::Event::MouseButtonPressed && gameOver) {
                    resetGame();
                }
            }
            render();
        }
    }

private:
    void handleMouseClick(int x, int y) {
        if (y >= 600) {
            return;  // Kliknięcia poniżej planszy są ignorowane
        }

        int cellSize = plansza.getCellSize();
        int row = y / cellSize;
        int col = x / cellSize;

        if (plansza.getPole(col, row) == Plansza::Pole::None) {
            Plansza::Pole currentSymbol = (currentPlayer == Player::Human1) ? Plansza::Pole::Cross : Plansza::Pole::Circle;
            plansza.setPole(col, row, currentSymbol);
            moveCount++;

            if (Checker::checkWin(plansza, (currentPlayer == Player::Human1) ? Gracz::Symbol::Cross : Gracz::Symbol::Circle)) {
                gameOver = true;
                if (currentPlayer == Player::Human1) {
                    komunikatWygralKrzyzyk.ustawKomunikat("Krzyzyk!\n1) Kliknij na ekran dla ponownej gry\n2) Dla wyjscia, krzyzyk na gorze");
                    logger.zapisRezultatu(true, moveCount, 1);
                }
                else {
                    komunikatWygralKolko.ustawKomunikat("Kolko!\n1) Kliknij na ekran dla ponownej gry\n2) Dla wyjscia, krzyzyk na gorze");
                    logger.zapisRezultatu(true, moveCount, 2);
                }
                logger.zapisDoPliku();
            }
            else if (plansza.isFull()) {
                gameOver = true;
                komunikatRemis.ustawKomunikat("Remis!\n1) Kliknij na ekran dla ponownej gry\n2) Dla wyjscia, krzyzyk na gorze");
                logger.zapisRezultatu(false, moveCount, 0);
                logger.zapisDoPliku();
            }
            else {
                currentPlayer = (currentPlayer == Player::Human1) ? Player::Human2 : Player::Human1;
                if (currentPlayer == Player::Human1) {
                    komunikatKrzyzyka.ustawKomunikat("Krzyzyka");
                }
                else {
                    komunikatKolka.ustawKomunikat("Kolka");
                }
            }
        }
    }

    void render() {
        window.clear(sf::Color::White);
        plansza.drawBoard(window);

        if (gameOver) {
            if (Checker::checkWin(plansza, Gracz::Symbol::Cross)) {
                komunikatWygralKrzyzyk.rysuj(window);
            }
            else if (Checker::checkWin(plansza, Gracz::Symbol::Circle)) {
                komunikatWygralKolko.rysuj(window);
            }
            else {
                komunikatRemis.rysuj(window);
            }
        }
        else {
            if (currentPlayer == Player::Human1) {
                komunikatKrzyzyka.rysuj(window);
            }
            else {
                komunikatKolka.rysuj(window);
            }
        }

        window.display();
    }


    void resetGame() {
        plansza.clearBoard(); // Wyczyszczenie planszy
        gameOver = false; // Reset flagi gameOver
        moveCount = 0; // Reset licznika ruchów
        currentPlayer = Player::Human1; // Ustawienie gracza jako Human1
        komunikatKrzyzyka.ustawKomunikat("Krzyzyka"); // Ustawienie komunikatu
    }
};

