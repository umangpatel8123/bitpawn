#include <iostream>
#include "board.hpp"

int main() {
    ChessBoard board;

    std::cout << "Welcome to Chess AI in C++!\n";

    while (true) {
        board.printBoard();

        std::string move;
        std::cout << "Enter your move (e.g., e2e4 or e7e8q): ";
        std::cin >> move;

        if (move == "exit") break;

        if (move.length() != 4 && move.length() != 5) {
            std::cout << "Invalid move format. Use format like e2e4 or e7e8q.\n";
            continue;
        }

        int from = board.algebraicToIndex(move.substr(0, 2));
        int to = board.algebraicToIndex(move.substr(2, 2));
        char promotion = (move.length() == 5) ? move[4] : '\0';

        if (!board.isLegalMove(from, to, promotion)) {
            std::cout << "Illegal move!\n";
            continue;
        }

        if (!board.makeMove(from, to, promotion)) {
            std::cout << "Invalid move!\n";
        }
    }

    return 0;
}
