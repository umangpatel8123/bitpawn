#pragma once
#include <iostream>
#include <vector>
#include <string>


// Piece definitions
enum Piece { 
    EMPTY = 0, 
    WP = 1, WN = 2, WB = 3, WR = 4, WQ = 5, WK = 6,
    BP = 7, BN = 8, BB = 9, BR = 10, BQ = 11, BK = 12
};

enum Color { WHITE = 0, BLACK = 1 };

class ChessBoard {
private:
    int board[64];
    
public:
    // Constructor
    ChessBoard();
    
    // Board initialization
    void initializeBoard();
    void clearBoard();
    
    // Piece operations
    int getPiece(int square) const;
    void setPiece(int square, int piece);
    bool isEmpty(int square) const;
    
    // Color checks
    bool isWhite(int piece) const;
    bool isBlack(int piece) const;
    Color getPieceColor(int piece) const;
    
    // Coordinate conversion
    int coordToIndex(int rank, int file) const;
    int getRank(int index) const;
    int getFile(int index) const;
    bool isValidSquare(int square) const;
    
    // String to square conversion (e.g., "e4" -> 28)
    int algebraicToIndex(const std::string& algebraic) const;
    std::string indexToAlgebraic(int index) const;
    
    // Move operations
    bool makeMove(int from, int to, char promotion= '\0');
    bool isLegalMove(int from, int to, char promotion = '\0') const;

    bool canMoveTo(int from, int to, Color color) const;
    
    // Board analysis
    int countMaterial(Color color) const;
    int evaluate() const;
    
    // Display
    void printBoard() const;
    std::string toFEN() const;
    void fromFEN(const std::string& fen);
    
    // Move generation
    std::vector<std::pair<int, int>> generateMoves(Color color) const;
    
    // Special moves (to be implemented)
    bool isInCheck(Color color) const;
    bool isCheckmate(Color color) const;
    bool isStalemate(Color color) const;
};

// Inline implementations for frequently used functions
inline int ChessBoard::getPiece(int square) const {
    return (square >= 0 && square < 64) ? board[square] : EMPTY;
}

inline void ChessBoard::setPiece(int square, int piece) {
    if (square >= 0 && square < 64) {
        board[square] = piece;
    }
}

inline bool ChessBoard::isEmpty(int square) const {
    return getPiece(square) == EMPTY;
}

inline bool ChessBoard::isWhite(int piece) const {
    return piece >= WP && piece <= WK;
}

inline bool ChessBoard::isBlack(int piece) const {
    return piece >= BP && piece <= BK;
}

inline Color ChessBoard::getPieceColor(int piece) const {
    return isWhite(piece) ? WHITE : BLACK;
}

inline int ChessBoard::coordToIndex(int rank, int file) const {
    return rank * 8 + file;
}

inline int ChessBoard::getRank(int index) const {
    return index / 8;
}

inline int ChessBoard::getFile(int index) const {
    return index % 8;
}

inline bool ChessBoard::isValidSquare(int square) const {
    return square >= 0 && square < 64;
}
