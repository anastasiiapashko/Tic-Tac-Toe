import <iostream>;
#include <vector>
export module Gracz;

export class Gracz {
public:
    enum class Symbol { Cross, Circle };

private:
    Symbol symbol;

public:
    Gracz(Symbol sym) : symbol(sym) {}

    Symbol getSymbol() const {
        return symbol;
    }
};