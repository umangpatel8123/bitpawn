
# 🧠 How to Run the Project
# 📁 First-Time Setup (One-Time Only)

cmake -S . -B build       # Generate build files
cmake --build build       # Build the project

# ✅ Running the Project
# 🖥️ On macOS / Linux (Terminal)

chmod +x run.sh    # (Only needed once)
./run.sh           # Shortcut to build & run the project

# chmod +x run.sh    # (Only needed once)
./run.sh           # Shortcut to build & run the project

# 🪟 On Windows (Command Prompt / PowerShell)

run.bat            :: Shortcut to build & run the project

# 1. Generate build files using CMake
cmake -S . -B build

# 2. Build the project
cmake --build build

# 3. Run the executable
# On Linux/macOS:
./build/bitpawn

# On Windows:
./build/bitpawn.exe

int index = (rank-1) * 8 + (file-1);

  a8  b8  c8  d8  e8  f8  g8  h8     ← rank 8 → index 56-63
  a7  b7  c7  d7  e7  f7  g7  h7     ← rank 7 → index 48-55
  a6  b6  c6  d6  e6  f6  g6  h6     ← rank 6 → index 40-47
  a5  b5  c5  d5  e5  f5  g5  h5     ← rank 5 → index 32-39
  a4  b4  c4  d4  e4  f4  g4  h4     ← rank 4 → index 24-31
  a3  b3  c3  d3  e3  f3  g3  h3     ← rank 3 → index 16-23
  a2  b2  c2  d2  e2  f2  g2  h2     ← rank 2 → index  8-15
  a1  b1  c1  d1  e1  f1  g1  h1     ← rank 1 → index  0-7
