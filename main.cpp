#include <iostream> 
#include <string>   
#include <vector>

struct MatchResult {
    std::string playerX;
    std::string playerO;
    std::string winner; // "X", "O", or "Draw"
};

//class Player to represent each player in the game
class Player {
private: 
    std::string name;
    char symbol; 

public: 
    Player(std::string playerName, char playerSymbol) : name(playerName), symbol(playerSymbol) {}  //constructor 
    std::string getName() const { return name; }   
    char getSymbol() const { return symbol; } 
};

//class Board to represent the game board
class Board {
private:
    char cells[3][3]; // 3x3 array of chars to represent the cells
    int moves;        // move counter

public: 
    Board() {
        reset(); 
    }

    //initialize the board to empty and reset the move counter
    void reset() {
        for (int i = 0; i < 3; i++) {      
            for (int j = 0; j < 3; j++) {   
                cells[i][j] = ' ';          
            }
        }
        moves = 0; 
    }

    // place a symbol in a cell (row, column).
    bool checkMove(int row, int column, char symbol) {

        // if row/column are out of range it stops immediately
        if (row >= 1 && row <= 3 && column >= 1 && column <= 3 && cells[row - 1][column - 1] == ' ') {
            cells[row - 1][column - 1] = symbol;
            moves++;
            return true; // valid move
        }
        return false; // invalid move
    }

    int getMoves() const { 
        return moves; 
    }
    
    // isFull: the board is full when 9 moves have been made.
    bool isFull() const {
        return moves == 9; 
    }

    // checkWinner returns true if the given symbol has a winning combination on the board.
    bool checkWinner(char symbol) const {
        for (int i = 0; i < 3; i++) {
            
            if ((cells[i][0] == symbol && cells[i][1] == symbol && cells[i][2] == symbol) ||
                (cells[0][i] == symbol && cells[1][i] == symbol && cells[2][i] == symbol)) {
                return true;
            }
        }
        
        if ((cells[0][0] == symbol && cells[1][1] == symbol && cells[2][2] == symbol) ||
            (cells[0][2] == symbol && cells[1][1] == symbol && cells[2][0] == symbol)) {
            return true;
        }
        return false; 
    }

    // print the board 
    void print() const {
        std::cout << "\n";
        for (int i = 0; i < 3; i++) {
            std::cout << " " << cells[i][0] << " | " << cells[i][1] << " | " << cells[i][2] << " \n";
            if (i < 2) { 
                std::cout << "---|---|---\n";
            }
        }
        std::cout << "\n";
    }
};

//return row and column by reference. If the user enters invalid input, it will ask again until valid numbers are entered.
void readMove(int& row, int& column) {
    while (!(std::cin >> row >> column)) { // if the input is not numbers, it will enter this loop
        std::cin.clear();             // clear the error state of cin
        std::cin.ignore(10000, '\n'); // ignore the rest of the line to avoid infinite loop
        std::cout << "Invalid input. Enter two numbers (from 1 to 3): ";
    }
    std::cin.ignore(10000, '\n'); // ignore the rest of the line to avoid issues with leftover input
}

// class Game to manage the game flow 
class Game {
private:
    Board board;     // creates a Board object to manage the game board
    Player playerX;  // creates a Player object for player X (symbol 'X')
    Player playerO;  // creates a Player object for player O (symbol 'O')
    Player* current; // pointer that refers to the current player (either &playerX or &playerO)

    /* switchTurn changes the current player to the other player.
    uses a pointer to avoid copying the Player object.*/
    void switchTurn() {
        current = (current == &playerX) ? &playerO : &playerX; 
    }

public:
    Game(std::string nameX, std::string nameO) : playerX(nameX, 'X'), playerO(nameO, 'O'), current(&playerX) {} // constructor initializes the players and sets the current player to playerX

    void play() {
        while (true) { // repeats the game until draw or win
            board.print(); 

            // calling getName() and getSymbol() through the pointer current to print the current player's name and symbol
            std::cout << (*current).getName() << " (" << (*current).getSymbol() << "), enter row and column (from 1 to 3): ";
            int row, column;       
            readMove(row, column); // readMove will check if the input is a int and will ask again if not
            while (!board.checkMove(row, column, (*current).getSymbol())) {
                std::cout << "Invalid move. Enter row and column again (from 1 to 3): ";
                readMove(row, column);
            }

            if (board.checkWinner((*current).getSymbol())) { 
                board.print();
                std::cout << (*current).getName() << " has won!\n";
                break; 
            } else if (board.isFull()) {  
                board.print();
                std::cout << "Draw!\n";
                break; 
            }
            switchTurn();
        }
    }
};

int main() {
    std::string name_X, name_O; 

    std::cout << "Name of player X: ";
    std::cin >> name_X; //input the name of player X
    std::cout << "Name of player O: ";
    std::cin >> name_O; //input the name of player O

    Game game(name_X, name_O); 
    game.play();             

    return 0; 
}
