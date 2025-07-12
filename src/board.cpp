#include "board.hpp"
#include <iostream>

ChessBoard::ChessBoard() {
    initializeBoard();
}

void ChessBoard::clearBoard() {
    for (int i = 0; i < 64; ++i) {
        board[i] = EMPTY;
    }
}

void ChessBoard::initializeBoard() {
    clearBoard();

    // White pieces
    board[0] = WR; board[1] = WN; board[2] = WB; board[3] = WQ;
    board[4] = WK; board[5] = WB; board[6] = WN; board[7] = WR;
    for (int i = 8; i < 16; ++i) board[i] = WP;

    // Black pieces
    for (int i = 48; i < 56; ++i) board[i] = BP;
    board[56] = BR; board[57] = BN; board[58] = BB; board[59] = BQ;
    board[60] = BK; board[61] = BB; board[62] = BN; board[63] = BR;
}

void ChessBoard::printBoard() const {
    const char* pieceSymbols[13] = {
        ".",  // EMPTY
        "P", "N", "B", "R", "Q", "K",  // White
        "p", "n", "b", "r", "q", "k"   // Black
    };

    for (int rank = 7; rank >= 0; --rank) {
        std::cout << rank + 1 << "  ";  // Print rank number
        for (int file = 0; file < 8; ++file) {
            int idx = coordToIndex(rank, file);
            int piece = board[idx];
            std::cout << pieceSymbols[piece] << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\n   a b c d e f g h\n";
}

bool ChessBoard::makeMove(int from, int to, char promotionChar) {
    int piece = getPiece(from);

    if (piece == EMPTY || !isValidSquare(to)) return false;

    // Handle promotion
    if ((piece == WP && getRank(to) == 7) || (piece == BP && getRank(to) == 0)) {
        switch (promotionChar) {
            case 'q': case 'Q': piece = isWhite(piece) ? WQ : BQ; break;
            case 'r': case 'R': piece = isWhite(piece) ? WR : BR; break;
            case 'n': case 'N': piece = isWhite(piece) ? WN : BN; break;
            case 'b': case 'B': piece = isWhite(piece) ? WB : BB; break;
            default: return false;  // Invalid promotion piece
        }
    }

    setPiece(to, piece);
    setPiece(from, EMPTY);
    return true;
}


int ChessBoard::algebraicToIndex(const std::string& algebraic) const {
    if (algebraic.length() != 2) return -1;
    char fileChar = algebraic[0];
    char rankChar = algebraic[1];

    int file = fileChar - 'a';       // 'a' -> 0, 'b' -> 1, ..., 'h' -> 7
    int rank = rankChar - '1';       // '1' -> 0, ..., '8' -> 7

    if (file < 0 || file > 7 || rank < 0 || rank > 7) return -1;

    return coordToIndex(rank, file);
}

std::string ChessBoard::indexToAlgebraic(int index) const {
    if (index < 0 || index >= 64) return "";

    int rank = getRank(index);   // 0 to 7
    int file = getFile(index);   // 0 to 7

    char fileChar = 'a' + file;
    char rankChar = '1' + rank;

    return std::string{fileChar, rankChar};
}

bool ChessBoard::isLegalMove(int from, int to, char promotion) const {
    std::cout << "Checking legality of move from " << from << " to " << to << "\n";

    if (!isValidSquare(from) || !isValidSquare(to) || from == to)
        return false;

    int piece = getPiece(from);
    int target = getPiece(to);

    if (piece == EMPTY)
        return false;

    Color mover = getPieceColor(piece);
    if (target != EMPTY && getPieceColor(target) == mover)
        return false;

    int fromRank = getRank(from);
    int fromFile = getFile(from);
    int toRank = getRank(to);
    int toFile = getFile(to);
    int dr = toRank - fromRank;
    int df = toFile - fromFile;

    switch (piece) {
        case WP: {
            std::cout << "Trying WP from " << from << " to " << to
                      << " (dr=" << dr << ", df=" << df << ")\n";

            // One step forward
            if (df == 0 && dr == 1 && isEmpty(to))
                return true;

            // Two steps forward from initial rank
            if (df == 0 && dr == 2 && fromRank == 1 && isEmpty(to) && isEmpty(from + 8))
                return true;

            // Capture
            if (dr == 1 && abs(df) == 1 && !isEmpty(to) && isBlack(target))
                return true;

            return false;
        }

        case BP: {
            // One step forward
            if (df == 0 && dr == -1 && isEmpty(to))
                return true;

            // Two steps forward from initial rank
            if (df == 0 && dr == -2 && fromRank == 6 && isEmpty(to) && isEmpty(from - 8))
                return true;

            // Capture
            if (dr == -1 && abs(df) == 1 && !isEmpty(to) && isWhite(target))
                return true;

            return false;
        }

        case WN:
        case BN: {
            if ((abs(dr) == 2 && abs(df) == 1) || (abs(dr) == 1 && abs(df) == 2))
                return true;
            break;
        }

        case WB:
        case BB: {
            if (abs(dr) != abs(df)) return false;
            int rStep = (dr > 0) ? 1 : -1;
            int fStep = (df > 0) ? 1 : -1;
            for (int r = fromRank + rStep, f = fromFile + fStep;
                 r != toRank && f != toFile;
                 r += rStep, f += fStep) {
                if (!isEmpty(coordToIndex(r, f)))
                    return false;
            }
            return true;
        }

        case WR:
        case BR: {
            if (dr != 0 && df != 0) return false;
            int step = (dr == 0) ? ((df > 0) ? 1 : -1) : ((dr > 0) ? 8 : -8);
            for (int pos = from + step; pos != to; pos += step) {
                if (!isEmpty(pos)) return false;
            }
            return true;
        }

        case WQ:
        case BQ: {
            if (abs(dr) == abs(df)) {
                int rStep = (dr > 0) ? 1 : -1;
                int fStep = (df > 0) ? 1 : -1;
                for (int r = fromRank + rStep, f = fromFile + fStep;
                     r != toRank && f != toFile;
                     r += rStep, f += fStep) {
                    if (!isEmpty(coordToIndex(r, f)))
                        return false;
                }
                return true;
            } else if (dr == 0 || df == 0) {
                int step = (dr == 0) ? ((df > 0) ? 1 : -1) : ((dr > 0) ? 8 : -8);
                for (int pos = from + step; pos != to; pos += step) {
                    if (!isEmpty(pos)) return false;
                }
                return true;
            }
            break;
        }

        case WK:
        case BK: {
            if (abs(dr) <= 1 && abs(df) <= 1)
                return true;
            break;
        }
    }

    return false;
}
