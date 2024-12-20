#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <regex>

export module Komunikator;

export class Komunikator {
protected:
    sf::Text text;
    sf::Font font;

public:
    Komunikator() {
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Failed to load font!" << std::endl;
            exit(1);
        }
        text.setFont(font);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Black);
        text.setPosition(100, 610); 
    }

    virtual void ustawKomunikat(const std::string& msg)  = 0; // Czysto wirtualna metoda
    virtual void rysuj(sf::RenderWindow& window) const = 0; // Czysto wirtualna metoda

    virtual ~Komunikator() = default; // Wirtualny destruktor
};

export class RuchKolka : public Komunikator {
public:
    void ustawKomunikat(const std::string& msg) override {
        text.setString("Ruch " + msg);
    }

    void rysuj(sf::RenderWindow& window) const override {
        window.draw(text);
    }
};

export class RuchKrzyzyka : public Komunikator {
public:
    void ustawKomunikat(const std::string& msg) override {
        text.setString("Ruch " + msg);
    }

    void rysuj(sf::RenderWindow& window) const override {
        window.draw(text);
    }
};

export class WygralKolko : public Komunikator {
public:
    void ustawKomunikat(const std::string& msg) override {
        text.setString("Wygralo: " + msg);
    }

    void rysuj(sf::RenderWindow& window) const override {
        window.draw(text);
    }
};

export class WygralKrzyzyk : public Komunikator {
public:
    void ustawKomunikat(const std::string& msg) override {
        text.setString("Wygral: " + msg);
    }

    void rysuj(sf::RenderWindow& window) const override {
        window.draw(text);
    }
};

export class Remis : public Komunikator {
public:
    void ustawKomunikat(const std::string& msg) override {
        text.setString("Remis: " + msg);
    }

    void rysuj(sf::RenderWindow& window) const override {
        window.draw(text);
    }
};
