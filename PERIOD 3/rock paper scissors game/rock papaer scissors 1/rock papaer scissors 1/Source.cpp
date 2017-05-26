#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string>

using namespace std;

int main()
{
	do {


		std::string userChoice;

		int computer;

		cout << "Rock, paper, or scissors? (All lowecase) i.e rock, paper, scissors" << endl;
		cout << " " << endl;

		cin >> userChoice;

		cout << "You entered: " << userChoice << endl;
		cout << " " << endl;

		srand(time(NULL));

		computer = rand() % 10 + 1;
		//Computer "brain"

		if (computer <= 3)
		{

			cout << "Computer chose: Rock" << endl;
			cout << " " << endl;

		}

		else if (computer <= 6)
		{

			cout << "Computer chose: Paper" << endl;
			cout << " " << endl;

		}
		else if (computer >= 7)
		{

			cout << "Computer chose: Scissors" << endl;
			cout << " " << endl;

		}

		//Determines winner
		//Rock
		if (userChoice == "rock" && computer <= 3)
		{

			cout << "It's a tie!" << endl;
			cout << " " << endl;

		}
		else if (userChoice == "rock" && computer <= 6)
		{

			cout << "You lose!" << endl;
			cout << " " << endl;

		}
		else if (userChoice == "rock" && computer >= 7)
		{

			cout << "You win!" << endl;
			cout << " " << endl;

		}
		//Paper
		if (userChoice == "paper" && computer <= 3)
		{

			cout << "You win!" << endl;
			cout << " " << endl;

		}
		else if (userChoice == "paper" && computer <= 6)
		{

			cout << "It's a tie!" << endl;
			cout << " " << endl;

		}
		else if (userChoice == "paper" && computer >= 7)
		{

			cout << "You lose!" << endl;
			cout << " " << endl;

		}
		//Scissors
		if (userChoice == "scissors" && computer <= 3)
		{

			cout << "You lose!" << endl;
			cout << " " << endl;

		}
		else if (userChoice == "scissors" && computer <= 6)
		{

			cout << "You win!" << endl;
			cout << " " << endl;

		}
		else if (userChoice == "scissors" && computer >= 7)
		{

			cout << "It's a tie!" << endl;
			cout << " " << endl;

		}
	} while (cin.get());






	cin.get();
	return 0;
}
