export module Checker;
import Plansza;
import Gracz;


export class Checker {
public:
    static bool checkWin(const Plansza& plansza, Gracz::Symbol symbol) {
        Plansza::Pole poleSymbol = (symbol == Gracz::Symbol::Cross) ? Plansza::Pole::Cross : Plansza::Pole::Circle;

        int size = plansza.getSize();
        for (int i = 0; i < size; ++i) {
            bool win = true;
            for (int j = 0; j < size; ++j) {
                if (plansza.getPole(j, i) != poleSymbol) {
                    win = false;
                    break;
                }
            }
            if (win) return true;
        }

        for (int i = 0; i < size; ++i) {
            bool win = true;
            for (int j = 0; j < size; ++j) {
                if (plansza.getPole(i, j) != poleSymbol) {
                    win = false;
                    break;
                }
            }
            if (win) return true;
        }

        bool diagonal1 = true;
        bool diagonal2 = true;
        for (int i = 0; i < size; ++i) {
            if (plansza.getPole(i, i) != poleSymbol) {
                diagonal1 = false;
            }
            if (plansza.getPole(i, size - 1 - i) != poleSymbol) {
                diagonal2 = false;
            }
        }
        if (diagonal1 || diagonal2) return true;

        return false;
    }
};