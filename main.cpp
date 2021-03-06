#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// function prototypes
void choose_difficulty(int &difficulty);
void get_guess (string &guess);
bool is_guess_valid (string guess);
string check_guess (string guess, string answer, string user_answer, string updated_answer, int &num_lives);
void check_game_won (string user_answer, string answer, bool &is_game_won);

int main() {
    cout << "........................................." << endl;
    cout << "Hangman - the classic word guessing game!" << endl;
    cout << "........................................." << endl;
    cout << "\nNote: guess '*' to quit" << endl;
    
    vector<vector<string> > word_list {
                                                                {"bat", "cow", "bag"},                              // three letters
                                                                {"tree", "lamp", "girl"},                           // four
                                                                {"mouse", "sport", "grass"},                // five
                                                                {"jigsaw", "mobile", "laptop"},         // six
                                                                {"arrived", "quicker", "equinox"}   // seven
                                                            };    
    int num_lives {4};
    int difficulty = {};
    choose_difficulty(difficulty);
    if (difficulty > 3) {
        --num_lives;
        } 
        else if (difficulty <= 2) {
        ++num_lives;    
        }
    
    srand(static_cast<unsigned int>(time(0)));  // seed the random number generator using the current time
    int random_number = rand();
    const int max_words = word_list.at(difficulty - 1).size();      // difficulty selects the row of the 2D vector
    int word_index = (random_number % max_words);      // makes sure the random number is in the range (0 - max number of words)
    
    string answer = word_list.at(difficulty - 1).at(word_index);  // choose a random word from the list
    const int length = answer.size();
    string user_answer (length, '_');   // creates a starting dummy answer
    string updated_answer {};   // if the user enters a correct guess it is stored here
    
    cout << "\nHidden Word: "; 
    for (auto i : answer) {
        cout << "_ ";
        }
    cout << "(" << length << " letters)"; 

    bool guess_again {1};
    do {                   // main game loop
        bool is_game_won {0};
        check_game_won (user_answer, answer, is_game_won);
        if (is_game_won == 1) {
            cout << "\nCongratulations! You did it!" << endl;
            guess_again = 0;
        } else {
            if (num_lives != 0) {
                cout << "\n" << num_lives << " lives remaining." << endl;
                do {
                    string guess {};        // will be used to store the user's guess
                    get_guess(guess);
                    if (is_guess_valid(guess)) {
                        if (guess[0] != '*') {
                            user_answer = check_guess(guess, answer, user_answer, updated_answer, num_lives);
                        } else {
                        guess_again = 0;
                        }
                    }
                } while (is_guess_valid == 0);
                } else {
                cout << "\nBad luck! You have no lives left :(" << endl;
                cout << "\nThe word was: " << answer << endl;
                guess_again = 0;
            }
        }
    } while (guess_again != 0); // TODO add an option to play again with a different word
    cout << "\nThank you for playing! Goodbye!" << endl;
    return 0;
}

    void choose_difficulty (int &difficulty) {
            cout << "\nPlease choose a level of difficulty from 1 (easiest) to 5 (hardest): ";
            cin >> difficulty;
    }

    void get_guess (string &guess) {
            cout << "\nWhat's your guess? ";
            cin >> guess;
    }
    
    bool is_guess_valid (string guess) {  
            if (guess.length() > 1) {
                cout << "Please enter only one letter." << endl;
                return 0;
            } else if (( guess[0] >= 65 && guess[0] <= 90 ) || ( guess[0] >= 97 && guess[0] <= 122 ) || guess[0] == 42) {     // makes sure the guess is a character of the alphabet or *
                return 1;
                } else {
                cout << "Please enter a letter (a-z)." << endl;
                return 0;
            }
    }
    
    string check_guess (string guess, string answer, string user_answer, string updated_answer, int &num_lives) {
            if (isupper(guess[0])) {
                guess = tolower(guess[0]);
                }
            int found = answer.find(guess);
            if (found != string::npos) {    // if the guessed letter is in the answer
                for (int i = 0; i < answer.size(); ++i) {
                    if (guess[0] == answer.at(i) ) {
                        user_answer.at(i) = answer.at(i);   // updates the users answer with the correct guess
                    }
                }
                cout << "Well done!" << endl;
                cout << "\nHidden Word: ";
                for (auto i : user_answer) {
                    cout << i << " ";
                }
                updated_answer = user_answer;
                return updated_answer;
        } else {
            cout << "Wrong :(";
            --num_lives;
            return user_answer;
        }
    }
    
    void check_game_won (string user_answer, string answer, bool &is_game_won) {
        if (user_answer == answer) {
        is_game_won = 1;
        }
    }
