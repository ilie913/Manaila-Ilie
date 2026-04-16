#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(){
    srand(time(0));
    int randomNum = rand() % 100+1;
    int guess, attempts=10;

    cout<<"Welcome to the number guessing game!"<<endl;
    cout<<"Guess a number  between 1 and 100"<<" "<<"You have"<<" "<<attempts<<" attempts."<<endl;

    while(attempts >0) {

        cout<<"Attempts left"<<" "<<attempts<<endl;
        cout<<"Enter your guess"<<endl;
        cin>>guess;

       if(guess == randomNum) {

        cout<<"Correct, the number was"<<" "<<randomNum<<endl;
        return 0;
        }

        else if(guess<randomNum) {
        cout<<"Too low! Try higher!"<<endl;
        } 
        
        else {
          cout<<"Too high! Try lower!"<<endl;
        }
    attempts--;
    }
    cout<<"Out of attempts! The number was "<< randomNum<<endl;
    return 0;
}