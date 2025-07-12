#include <chrono>
#include <iostream>
#include <cctype>

enum Piece { WP = 1, WN = 2, WB = 3, WR = 4, WQ = 5, WK = 6 };

// Method 1: Character-based
bool isWhiteChar(char piece) {
    return std::isupper(piece);
}

// Method 2: Enum-based  
bool isWhiteEnum(int piece) {
    return piece >= WP && piece <= WK;
}

int main() {
    const int ITERATIONS = 100000000;
    
    // Test data
    char charPieces[] = {'P', 'N', 'B', 'R', 'Q', 'K', 'p', 'n', 'b', 'r', 'q', 'k'};
    int enumPieces[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    
    // Benchmark character method
    auto start = std::chrono::high_resolution_clock::now();
    volatile bool result1;
    for (int i = 0; i < ITERATIONS; i++) {
        result1 = isWhiteChar(charPieces[i % 12]);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto charTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Benchmark enum method
    start = std::chrono::high_resolution_clock::now();
    volatile bool result2;
    for (int i = 0; i < ITERATIONS; i++) {
        result2 = isWhiteEnum(enumPieces[i % 12]);
    }
    end = std::chrono::high_resolution_clock::now();
    auto enumTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Character method: " << charTime.count() << " microseconds\n";
    std::cout << "Enum method: " << enumTime.count() << " microseconds\n";
    std::cout << "Speedup: " << (double)charTime.count() / enumTime.count() << "x\n";
    
    return 0;
}