# 🔐 Enigma Machine Simulator

<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/6/6c/Bundesarchiv_Bild_146-2006-0188%2C_Verschl%C3%BCsselungsger%C3%A4t_%22Enigma%22.jpg/335px-Bundesarchiv_Bild_146-2006-0188%2C_Verschl%C3%BCsselungsger%C3%A4t_%22Enigma%22.jpg" width="400">


Unlike other implementations that just focus on the math, this simulator:

- Perfectly mirrors the physical machine's signal path
- Each array represents actual mechanical parts
- Every step matches real hardware:
  - Keyboard input → Electrical signal
  - Plugboard wires → Array swaps
  - Rotating wheels → Array shifts
  - Electrical path → Position tracking
  - Light bulb output → Character display

## ✨ Features

- 🎮 Interactive CLI menu system
- 🔄 Message encryption and decryption
- 🔌 Configurable plugboard (swap letter pairs)
- ⚙️ Adjustable rotor positions
- 💫 Uses actual historical Enigma rotor wirings
- 🎯 Perfect encryption/decryption with reciprocal property

## 📚 Detailed Documentation

Want to dive deeper? Check out these detailed docs:

- `docs/documentation.md`: Complete technical breakdown of how each component works

## 🏃‍♂️ How to Run

1. Clone the repository
2. Compile with any C++ compiler:

```bash
g++ -std=c++11 main.cpp -o enigma
```

3. Run the executable:

```bash
./enigma
```

## 📖 Usage Examples

### Encrypt a Message:

<img src="demoVideo/encryption.gif" width="350">


```
Choose option (1-5): 1
Enter message to encrypt: HELLO
Encrypted message: LZFBD
```

### Configure Plugboard:

<img src="demoVideo/plugboard.gif" width="350">

```
Choose option (1-5): 3
Enter two letters to swap (e.g., AB): HM
Plugboard configured: H <-> M
```

### Set Rotor Positions:

<img src="demoVideo/rotors.gif" width="350">

```
Choose option (1-5): 4
Enter positions for left, middle, and right rotors (e.g., AAA): XYZ
Rotor positions set to: XYZ
```

## 🎯 Project Structure

- `main.cpp`: Core implementation with encryption/decryption logic
- `enigma_display.cpp`: ASCII UI and visual interface implementation
- 📁 `docs/`
  - `DOCUMENTATION.md`: Technical details, hardware simulation, and implementation choices
  - `CPP_CONCEPTS.md`: C++ concepts used and learning resources
  - `ORIGINAL.md`: Historical Enigma machine specifications and details
- `README.md`: Project overview, setup instructions, and usage guide

## 🌟 Cool Features

- Each letter encrypts differently based on rotor positions
- Plugboard adds extra encryption complexity
- Matches historical Enigma machine behavior
- Simple but powerful encryption system

## 💡 Learning Value

This project helps you understand:

- How physical encryption machines work
- Mapping hardware to software concepts
- Array manipulation and character handling
- Historical cryptography
- Modular programming

🤝 Contributing
Feel free to:

Fork the project
Add new features
Fix bugs
Submit pull requests

Made with 💻 by a student fascinated by cryptography, history, and C++!

---

_"Sometimes it is the people no one imagines anything of who do the things that no one can imagine." - Alan Turing_
