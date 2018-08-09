#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;
// function prototypes
char get_guess ();
string check_guess (char guess, string answer, string user_answer, string updated_answer);
bool check_game_won (string user_answer, string answer);

char guess {};
int num_lives {4};
bool is_game_won {0};

int main() {
    bool guess_again {1};
    vector <string> word_list {"arrived", "radiator", "tree", "lamp", "laptop"};
    
    cout << "........................................." << endl;
    cout << "Hangman - the classic word guessing game!" << endl;
    cout << "........................................." << endl;
    cout << "\nNote: guess '*' to quit" << endl;
    
    srand(static_cast<unsigned int>(time(0)));
    int random_number = rand();
    int word_index = (random_number % 5);
    string answer = word_list.at(word_index);
    const int length = answer.size();
    string user_answer (length, '_');
    string updated_answer {};
    
    cout << "\nHidden Word: ";
    for (auto i : answer) {
        cout << "_ ";
        }
    cout << "(" << length << " letters)"; 
    
    do {
        check_game_won (user_answer, answer);
        if (is_game_won == 1) {
            cout << "\nCongratulations! You did it!" << endl;
            guess_again = 0;
        } else {
            if (num_lives != 0) {
                cout << "\n" << num_lives << " lives remaining." << endl;
                get_guess();
            if (guess != '*') {
                user_answer = check_guess(guess, answer, user_answer, updated_answer);
                } else {
                    guess_again = 0;
                }
            } else {
                cout << "\nBad luck! You have no lives left :(" << endl;
                guess_again = 0;
            }
        }
    } while (guess_again != 0);
    cout << "\nThank you for playing! Goodbye!" << endl;
    return 0;
}

    char get_guess () {
            cout << "\nWhat's your guess? ";
            cin >> guess;
            return guess;
    }
    
    string check_guess (char guess, string answer, string user_answer, string updated_answer) {
            int found = answer.find(guess);
            if (found != string::npos) {
                for (int i = 0; i < answer.size(); ++i) {
                    if (guess == answer.at(i) ) {
                        user_answer.at(i) = answer.at(i);
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