import <SFML/Graphics.hpp>;
import <iostream>;
#include <vector>
import Game;
import zapisGry;

export module Menu;

export class Menu {
private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text startText;
    sf::Text saveText;
    sf::Text closeText;
    bool gameStarted;
    bool gameWon;
    int moves;
    int winningPlayer;

public:
    Menu() {
        window.create(sf::VideoMode(400, 400), "Tic Tac Toe Menu");

        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Failed to load font!" << std::endl;
            exit(1);
        }
        startText.setFont(font);
        startText.setString("Start");
        startText.setCharacterSize(30);
        startText.setPosition(170, 100);

        saveText.setFont(font);
        saveText.setString("Zapisac");
        saveText.setCharacterSize(30);
        saveText.setPosition(150, 200);

        closeText.setFont(font);
        closeText.setString("Zamknac");
        closeText.setCharacterSize(30);
        closeText.setPosition(145, 300);
    }

    void start() {
        std::cout << "Gra rozpoczeta!" << std::endl;
        Game game;
        game.run();
    }

    void zapisac() {
        if (gameStarted && gameWon) {
            zapisGry save;
            save.zapisDoPliku();
        }
    }

    void zamknac() {
        window.close();
    }

    void drawButton(sf::Text& text, sf::Color buttonColor, sf::RenderWindow& window) {
    sf::RectangleShape button(sf::Vector2f(text.getGlobalBounds().width + 35, text.getGlobalBounds().height + 35));
    button.setFillColor(buttonColor);
    button.setOutlineThickness(3);
    button.setOutlineColor(sf::Color::Black);
    button.setPosition(text.getPosition().x - 10, text.getPosition().y - 10);

    window.draw(button);
    window.draw(text);

    // Dodanie ramki do całego okna
    sf::RectangleShape border(sf::Vector2f(window.getSize().x - 10, window.getSize().y - 10));
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineThickness(10);
    border.setOutlineColor(sf::Color::Blue);
    border.setPosition(5, 5);
    window.draw(border);
}



    void run() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                else if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        if (startText.getGlobalBounds().contains(mousePos.x, mousePos.y))
                            start();
                        else if (saveText.getGlobalBounds().contains(mousePos.x, mousePos.y))
                            zapisac();
                        else if (closeText.getGlobalBounds().contains(mousePos.x, mousePos.y))
                            zamknac();
                    }
                }
            }

            window.clear(sf::Color::White);
            drawButton(startText, sf::Color::Green, window);
            drawButton(saveText, sf::Color::Yellow, window);
            drawButton(closeText, sf::Color(255, 192, 203), window); 
            window.display();
        }
    }
};