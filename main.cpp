#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// function prototypes
int choose_difficulty();
char get_guess ();
bool is_guess_valid (char guess);
string check_guess (char guess, string answer, string user_answer, string updated_answer);
bool check_game_won (string user_answer, string answer);

char guess {};
int difficulty {};
int num_lives {4};
bool is_game_won {0};

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
    
    srand(static_cast<unsigned int>(time(0)));  // seed the random number generator using the current time
    int random_number = rand();
    const int max_words = word_list.at(difficulty).size();
    int word_index = (random_number % max_words);      // makes sure the random number is in the range (0 - max number of words)
    
    choose_difficulty();
    if (difficulty > 3) {
        --num_lives;
        } 
        else if (difficulty <= 2) {
        ++num_lives;    
        }
    
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
    do {    // main game loop
        check_game_won (user_answer, answer);
        if (is_game_won == 1) {
            cout << "\nCongratulations! You did it!" << endl;
            guess_again = 0;
        } else {
            if (num_lives != 0) {
                cout << "\n" << num_lives << " lives remaining." << endl;
                do {
                    get_guess();
                    if (is_guess_valid(guess)) {
                        if (guess != '*') {
                            user_answer = check_guess(guess, answer, user_answer, updated_answer);
                        } else {
                        guess_again = 0;
                        }
                    }
                } while (is_guess_valid == 0);
                } else {
                cout << "\nBad luck! You have no lives left :(" << endl;
                guess_again = 0;
            }
        }
    } while (guess_again != 0); // TODO add an option to play again with a different word
    cout << "\nThank you for playing! Goodbye!" << endl;
    return 0;
}

    int choose_difficulty() {
            cout << "\nPlease choose a level of difficulty from 1 (easiest) to 5 (hardest): ";
            cin >> difficulty;
            return difficulty;
    }

    char get_guess () {
            cout << "\nWhat's your guess? ";
            cin >> guess;
            return guess;
    }
    
    bool is_guess_valid (char guess) {  // TODO recognise capitals as correct guesses
            if ( ( guess >= 65 && guess <= 90 ) || ( guess >= 97 && guess <= 122 ) || guess == 42 ) {
                return 1;
            } else {
                cout << "Please enter a letter (a-z)." << endl;
                return 0;
            }
    }
    
    string check_guess (char guess, string answer, string user_answer, string updated_answer) {
            int found = answer.find(guess);
            if (found != string::npos) {    // if the guessed letter is in the answer
                for (int i = 0; i < answer.size(); ++i) {
                    if (guess == answer.at(i) ) {
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
    
    bool check_game_won (string user_answer, string answer) {
        if (user_answer == answer) {
        is_game_won = 1;
        }
        return is_game_won;
    }
