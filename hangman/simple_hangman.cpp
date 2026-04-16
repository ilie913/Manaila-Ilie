#include <cctype>
#include <ctime>
#include <iostream>
#include <set>
#include <string>
#include <vector>

// Print the hangman picture depending on how many wrong guesses the player has made.
void displayHangman(int wrongGuesses) {
    static const std::vector<std::string> stages = {
        "\n  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========" ,
        "\n  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========" ,
        "\n  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========" ,
        "\n  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========" ,
        "\n  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========" ,
        "\n  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========" ,
        "\n  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n========="
    };

    std::cout << stages[wrongGuesses] << "\n";
}

// Choose one word from the list at random.
std::string chooseWord() {
    static const std::vector<std::string> words = {
        "gemini",
        "atibot",
        "atigra",
        "copilot",
        "river"
    };

    int index = std::rand() % words.size();
    return words[index];
}

// Show the current word state with underscores for letters not guessed yet.
void displayWordState(const std::string& secret, const std::set<char>& guessed) {
    for (char ch : secret) {
        if (guessed.count(std::tolower(ch))) {
            std::cout << ch << ' ';
        } else {
            std::cout << "_ ";
        }
    }
    std::cout << "\n";
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::string secret = chooseWord();
    std::set<char> guessedLetters;
    std::set<char> wrongLetters;
    const int maxWrong = 6;

    std::cout << "Welcome to Hangman!\n";
    std::cout << "Try to guess the letters of the secret word.\n";

    while (true) {
        displayHangman(static_cast<int>(wrongLetters.size()));
        std::cout << "Word: ";
        displayWordState(secret, guessedLetters);

        if (!wrongLetters.empty()) {
            std::cout << "Wrong guesses: ";
            for (char ch : wrongLetters) {
                std::cout << ch << ' ';
            }
            std::cout << "\n";
        }

        if (wrongLetters.size() >= maxWrong) {
            std::cout << "\nYou lost. The word was: " << secret << "\n";
            break;
        }

        bool complete = true;
        for (char ch : secret) {
            if (!guessedLetters.count(std::tolower(ch))) {
                complete = false;
                break;
            }
        }
        if (complete) {
            std::cout << "\nCongratulations! You guessed the word.\n";
            break;
        }

        std::cout << "Enter a letter: ";
        std::string input;
        std::getline(std::cin, input);

        if (input.empty()) {
            std::cout << "Please type one letter.\n";
            continue;
        }

        char guess = std::tolower(input[0]);
        if (!std::isalpha(static_cast<unsigned char>(guess))) {
            std::cout << "Only letters are allowed.\n";
            continue;
        }

        if (guessedLetters.count(guess) || wrongLetters.count(guess)) {
            std::cout << "You already guessed '" << guess << "'. Try another letter.\n";
            continue;
        }

        bool found = false;
        for (char ch : secret) {
            if (std::tolower(ch) == guess) {
                found = true;
                break;
            }
        }

        if (found) {
            guessedLetters.insert(guess);
            std::cout << "Good job! '" << guess << "' is in the word.\n";
        } else {
            wrongLetters.insert(guess);
            std::cout << "Sorry, '" << guess << "' is not in the word.\n";
        }
    }

    return 0;
}
