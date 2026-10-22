#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <time.h>
#include <algorithm>
using namespace std;


int drawCard() {
	int num = (rand() % (13 - 1 + 1)) + 1;
	return num;
}
int drawSuit() {
	int num = (rand() % (4 - 1 + 1)) + 1;
	return num;
}

int dealerChoice() {
	int num = (rand() % (3 - 1 + 1)) + 1;
	return num;
}
int dealerRaiseAmt() {
	int num = (rand() % (2000 - 50 + 1)) + 50;
	return num;
}
int dealerFinalHand() {
	int num = (rand() % (20 - 1 + 1)) + 1;
	return num;
}

struct Card {
	int num;
	int suit;
	string numName;
	string suitName;
	void nameOfCard() {
		if (num < 2) {
			numName = "Ace";
		}
		else if (num == 11) {
			numName = "Jack";
		}
		else if (num == 12) {
			numName = "Queen";
		}
		else if (num == 13) {
			numName = "King";
		}
		else {
			numName = to_string(num);
		}
	}
	void nameOfSuit() {
		if (suit == 1) {
			suitName = "Spades";
		}
		else if (suit == 2) {
			suitName = "Diamonds";
		}
		else if (suit == 3) {
			suitName = "Clubs";
		}
		else if (suit == 4) {
			suitName = "Hearts";
		}
	}

	bool isSameCard(Card other) {
		if (num == other.num && suit == other.suit) {
			return true;
		}
		return false;
	}

	Card(int num, int suit) {
		this->num = num;
		this->suit = suit;
		nameOfCard();
		nameOfSuit();
	}
	Card() {
		num = 1;
		suit = 1;
		nameOfCard();
		nameOfSuit();
	}
	~Card() {

	}

	void printCard() {
		cout << numName << " of " << suitName << endl;
	}
};

class initialHand {
private:
	Card first;
	Card second;
public:
	initialHand(Card first, Card second) {
		this->first = first;
		this->second = second;
	}
	
	void printHand() {
		cout << "Your first card is a " << first.numName << " of " <<first.suitName<< endl;
		cout << "Your second card is a " << second.numName << " of " << second.suitName << endl;
	}

	Card getFirst() {
		return first;
	}
	Card getSecond() {
		return second;
	}
};


struct dealerOptions {

	int choice;
	bool didCheck;
	bool didFold;
	bool didRaise;

	dealerOptions(int choice) {
		this->choice = choice;
		//cout << "dealer choice: "<<choice << endl;
		if (choice == 2) {
			didCheck = true;
			didFold = false;
			didRaise = false;
		}
		else if (choice == 1) {
			didFold = true;
			didCheck = false;
			didRaise = false;
		}
		else if (choice == 3) {
			didRaise = true;
			didCheck = false;
			didFold = false;
		}
	}
	void newChoice(int choice) {
		this->choice = choice;
		if (choice == 2) {
			didCheck = true;
			didFold = false;
			didRaise = false;
		}
		else if (choice == 1) {
			didFold = true;
			didCheck = false;
			didRaise = false;
		}
		else if (choice == 3) {
			didRaise = true;
			didCheck = false;
			didFold = false;
		}
	}
};

int userWin(initialHand userHand, vector<Card> cVect) {
	bool highCard = false;
	bool pair = false;
	bool pair2 = false;
	bool trips = false;
	bool straight = false;
	bool flush = false;
	bool fullHouse = false;

	bool suited = false;
	bool pocket = false;
	bool firstPair = false;

	float pairCount = 0;
	float flushCount = 1;
	float straightCount = 1;
	int sameCount = 0;
	int insideCount = 0;

	//check flush
	if (userHand.getFirst().suit == userHand.getSecond().suit) {
		suited = true;
		flushCount += 1;
	}
	else {
		flushCount = 1;
	}
	for (int i = 0; i < cVect.size(); i++) {
		if (userHand.getFirst().suit == cVect[i].suit) {
			flushCount++;
		}
	}
	if (flushCount >= 5) {
		//cout << "flush on first card" << endl;
		flush = true;
		flushCount = 1;
	}
	else {
		if (suited) {
			flushCount = 2;
		}
		else {
			flushCount = 1;
		}
	}
	for (int i = 0; i < cVect.size(); i++) {
		if (userHand.getSecond().suit == cVect[i].suit) {
			flushCount++;
		}
	}
	if (flushCount >= 5) {
		//cout << "flush on second card" << endl;
		flush = true;
		//flushCount == 0;
	}
	//cout << flushCount << " " << flush << endl;


	//check straight
	vector<int> numVect;
	for (int i = 0; i < cVect.size(); i++) {
		numVect.push_back(cVect[i].num);
	}

	sort(numVect.begin(), numVect.end());
	for (int i = 0; i < numVect.size() - 1; i++) {
		if (numVect[i] == numVect[i + 1]) {
			insideCount++;
			//cout << "inside count ++" << endl;
		}
	}


	numVect.push_back(userHand.getFirst().num);
	numVect.push_back(userHand.getSecond().num);

	//cout << endl;
	sort(numVect.begin(),numVect.end());

	for (int i = 1; i < numVect.size(); i++)
	{
		if (numVect[i] == numVect[i - 1] + 1)
		{
			straightCount++;
		}
	}
	if (straightCount >= 5) {
		straight = true;
	}

	for (int i = 0; i < numVect.size(); i++) {
		//cout << numVect[i] << " ";
	}
	//cout << endl<< straightCount<<" " << straight << endl;


	//check pairs
	for (int i = 0; i < numVect.size()-1; i++) {
		if (numVect[i] == numVect[i + 1]) {
			sameCount++;
		}
	}
	//cout << "same count " << sameCount << endl;

	if (sameCount >= 3 && insideCount <=2) {
		fullHouse = true;
	}
	else if (sameCount == 2) {
		trips = true;
		pair2 = true;
	}
	else if (sameCount == 1) {
		pair = true;
	}
	else {
		if (userHand.getFirst().num >= 11 || userHand.getSecond().num >= 11) {
			highCard = true;
		}
	}
	//cout << pair << " " << pair2 << " " << trips << " " << fullHouse << " " << endl;


	cout << "Checking dealer's hand..." << endl;
	int dealerHandAmt = dealerFinalHand();
	int dealerFinal = 0;

	if (flushCount >= 3) {
		if (dealerHandAmt >= 15) {
			dealerFinal = 6;
			cout << "Dealer has a flush." << endl;
		}
	}
	if (straightCount >= 3) {
		if (dealerHandAmt >= 15 && flushCount<3) {
			dealerFinal = 5;
			cout << "Dealer has a straight." << endl;
		}
	}
	if (insideCount>=1 && flushCount < 3 && straightCount < 3) {
		if (dealerHandAmt >= 15) {
			dealerFinal = 7;
			cout << "Dealer has a full house." << endl;
		}
		else if (dealerHandAmt >= 10 && dealerHandAmt <= 14) {
			dealerFinal = 4;
			cout << "Dealer has 3 of a kind." << endl;
		}
		else if (dealerHandAmt >= 5 && dealerHandAmt <= 9) {
			dealerFinal = 4;
			cout << "Dealer has a 2 pair." << endl;
		}
	}
	else if (dealerHandAmt >= 6 && dealerHandAmt <= 9) {
		dealerFinal = 2;
		cout << "Dealer has a pair." << endl;
	}
	else if (dealerHandAmt >= 1 && dealerHandAmt <= 5) {
		dealerFinal = 1;
		cout << "Dealer has a high card." << endl;
	}
	else if(flushCount < 3 && straightCount < 3) {
		dealerFinal = 0;
		cout << "Dealer doesn't have anything." << endl;
	}
	else {
		dealerFinal = 0;
		cout << "Dealer doesn't have anything." << endl;
	}


	/*else if (dealerHandAmt >= 18 && dealerHandAmt <= 19) {
		dealerFinal = 6;
		cout << "Dealer has a flush." << endl;
	}
	else if (dealerHandAmt >= 16 && dealerHandAmt <= 17) {
		dealerFinal = 5;
		cout << "Dealer has a straight." << endl;
	}
	else if (dealerHandAmt >= 13 && dealerHandAmt <= 15) {
		dealerFinal = 4;
		cout << "Dealer has 3 of a kind." << endl;
	}
	else if (dealerHandAmt >= 10 && dealerHandAmt <= 12) {
		dealerFinal = 3;
		cout << "Dealer has a 2 pair." << endl;
	}
	else if (dealerHandAmt >= 6 && dealerHandAmt <= 9) {
		dealerFinal = 2;
		cout << "Dealer has a pair." << endl;
	}
	else if (dealerHandAmt >= 1 && dealerHandAmt <= 5) {
		dealerFinal = 1;
		cout << "Dealer has a high card." << endl;
	}*/


	int userFinal = 0;
	if (fullHouse) {
		userFinal = 7;
		cout << "You have a full house!" << endl;
	}
	else if (flush) {
		userFinal = 6;
		cout << "You have a flush!" << endl;
	}
	else if (straight) {
		userFinal = 5;
		cout << "You have a straight!" << endl;
	}
	else if (trips) {
		userFinal = 4;
		cout << "You have a 2 pair or 3 of a kind!" << endl;
	}
	else if (pair2) {
		userFinal = 3;
		cout << "You have a 2 pair or 3 of a kind!" << endl;
	}
	else if (pair) {
		userFinal = 2;
		cout << "You have a pair!" << endl;
	}
	else if (highCard) {
		userFinal = 1;
		cout << "You have a high card!" << endl;
	}
	else {
		userFinal = 0;
		cout << "You didn't have anything." << endl;
	}


	//cout << "Dealer final " << dealerFinal << " User final " << userFinal << endl;

	if (dealerFinal > userFinal) {
		return 0;
	}
	else if (userFinal > dealerFinal) {
		return 2;
	}
	else if (userFinal == dealerFinal) {
		return 1;
	}
}

void newGame(initialHand& playerHand, dealerOptions& dealer, bool& check, bool& fold, bool& raise,bool &isFlop, bool &isTurn, bool &isRiver,vector<Card> cVect) {
	Card first(drawCard(), drawSuit());
	Card second(drawCard(), drawSuit());
	if (first.isSameCard(second)) {
		cout << "same card" << endl;
		Card newC(drawCard(), drawSuit());
		second.num = newC.num;
		second.suit = newC.suit;
		cout << second.num << second.suitName << endl;

	}
	initialHand newPlayerHand(first, second);
	playerHand = newPlayerHand;
	//playerHand.printHand();


	dealer.newChoice(dealerChoice());
	check = dealer.didCheck;
	fold = dealer.didFold;
	raise = dealer.didRaise;

	isFlop = false;
	isTurn = false;
	isRiver = false;

	cVect.clear();
}


void nextHand(bool& flop, bool& turn, bool& river, vector<Card>& cVect, initialHand user, int& userM, int& pot, bool &gameOver) {
	if (!flop) {
		flop = true;
		cVect.clear();
		//cout << "flop" << endl;
		//print flop


		Card first(drawCard(), drawSuit());
		Card second(drawCard(), drawSuit());
		Card third(drawCard(), drawSuit());


		cVect.push_back(first);
		cVect.push_back(second);
		cVect.push_back(third);

		cVect[0].printCard();
		cVect[1].printCard();
		cVect[2].printCard();
	}
	else {
		if (!turn) {
			turn = true;
			//cout << "turn" << endl;
			//print turn
			Card fourth(drawCard(), drawSuit());
			cVect.push_back(fourth);

			cVect[0].printCard();
			cVect[1].printCard();
			cVect[2].printCard();
			cVect[3].printCard();


		}
		else {
			if (!river) {
				river = true;
				//cout << "river" << endl;
				//print river
				Card fifth(drawCard(), drawSuit());
				cVect.push_back(fifth);

				cVect[0].printCard();
				cVect[1].printCard();
				cVect[2].printCard();
				cVect[3].printCard();
				cVect[4].printCard();

			}
			else {
				cout << "All cards have been revealed:" << endl;
				cout << endl;
				cVect[0].printCard();
				cVect[1].printCard();
				cVect[2].printCard();
				cVect[3].printCard();
				cVect[4].printCard();
				user.printHand();
				cout << endl;


				gameOver = true;
				int userHasWon = userWin(user, cVect);
				if (userHasWon == 2) {
					cout << "You won " << pot << endl;
					userM += pot;
					pot = 0;
				}
				else if (userHasWon == 0) {
					cout << "You lost " << pot << endl;
					pot = 0;
				}
				else if (userHasWon == 1) {
					cout << "You tied! You won " << pot / 2.0f << endl;
					userM += pot / 2.0f;
					pot = 0;
				}
			}
		}
	}
}

int main() {
	srand(time(0));
	Card first(drawCard(), drawSuit());
	Card second(drawCard(), drawSuit());
	if (first.isSameCard(second)) {
		cout << "same card" << endl;
		Card newC(drawCard(), drawSuit());
		second.num = newC.num;
		second.suit = newC.suit;
	}

	initialHand playerHand(first, second);
	playerHand.printHand();


	int userOption;
	cout << "\n 0. Exit \n 1. Fold \n 2. Check \n 3. Bet\n Enter your option: ";
	cin >> userOption;
	cout << endl;

	bool isFlop = false;
	bool isTurn = false;
	bool isRiver = false;

	vector<Card> cVect;

	int userMoney = 2000;
	int potMoney = 0;

	/*Card firstC(drawCard(), drawSuit());
	Card secondC(drawCard(), drawSuit());
	Card thirdC(drawCard(), drawSuit());
	Card fourthC(drawCard(), drawSuit());
	Card fifthC(drawCard(), drawSuit());


	cVect.push_back(firstC);
	cVect.push_back(secondC);
	cVect.push_back(thirdC);
	cVect.push_back(fourthC);
	cVect.push_back(fifthC);

	for (int i = 0; i < cVect.size(); i++) {
		cVect[i].printCard();
	}
	playerHand.printHand();
	cout << endl;

	userWin(playerHand, cVect);*/

	bool gameOver = false;
	int gamesPlayed = 1;

	while (userOption >=0 && userOption<=3) {
		dealerOptions dealer(dealerChoice());
		bool dealerCheck = dealer.didCheck;
		bool dealerFold = dealer.didFold;
		bool dealerRaise = dealer.didRaise;
		int dealerRaiseAmts = dealerRaiseAmt();


		if (userOption == 0) {
			break;
		}
		else if (userOption == 1) {
			cout << "You folded. Dealer wins!" << endl;

			cout << endl;
			newGame(playerHand,dealer,dealerCheck,dealerFold,dealerRaise,isFlop,isTurn,isRiver, cVect);
			potMoney = 0;
			gameOver = false;
			gamesPlayed++;
			if (gamesPlayed % 3 == 0 && userMoney != 0) {
				cout << "\nIt is your turn to be the small blind. You must put in $50.\nThe dealer puts in $100" << endl;
				potMoney += 150;
				userMoney -= 50;
			}
			else if (gamesPlayed % 4 == 0 && userMoney != 0) {
				cout << "\nIt is your turn to be the big blind. You must put in $100.\nThe dealer puts in $50" << endl;
				potMoney += 150;
				userMoney -= 100;
			}
			
		}
		else if (userOption == 2) {
			if (dealerCheck) {
				cout << "Dealer checked too. Here's the next hand." << endl;
				cout << endl;
				nextHand(isFlop, isTurn, isRiver,cVect,playerHand,userMoney,potMoney,gameOver);
				if (gameOver) {
					if (userMoney <= 0) {
						cout << endl;
						cout << "You have lost all your money after " << gamesPlayed << " games." << endl;
						break;
					}
					newGame(playerHand, dealer, dealerCheck, dealerFold, dealerRaise, isFlop, isTurn, isRiver, cVect);
					gameOver = false;
					gamesPlayed++;
					potMoney = 0;
					if (gamesPlayed % 3 == 0 && userMoney != 0) {
						cout << "\nIt is your turn to be the small blind. You must put in $50.\nThe dealer puts in $100" << endl;
						potMoney += 150;
						userMoney -= 50;
					}
					else if (gamesPlayed % 4 == 0 && userMoney != 0) {
						cout << "\nIt is your turn to be the big blind. You must put in $100.\nThe dealer puts in $50" << endl;
						potMoney += 150;
						userMoney -= 100;
					}
				}
			}
			else {
				if (dealerRaiseAmts > userMoney) {
					dealerRaiseAmts = userMoney;
				}
				else if (dealerRaiseAmts % 5 != 0) {
					dealerRaiseAmts -= dealerRaiseAmts % 5;
				}
				potMoney += dealerRaiseAmts;
				cout << "Dealer raised by " << dealerRaiseAmts;
				cout<<". What do you want to do ? " << endl;
				cout << "\n 1. Fold \n 2. Match \n Enter your option: ";
				cin >> userOption;

				if (userOption == 1) {
					cout << "You folded. Dealer wins!" << endl;
					cout << endl;
					newGame(playerHand, dealer, dealerCheck, dealerFold, dealerRaise, isFlop, isTurn, isRiver,cVect);
					potMoney = 0;
					gameOver = false;
					gamesPlayed++;
					if (gamesPlayed % 3 == 0 && userMoney != 0) {
						cout << "\nIt is your turn to be the small blind. You must put in $50.\nThe dealer puts in $100" << endl;
						potMoney += 150;
						userMoney -= 50;
					}
					else if (gamesPlayed % 4 == 0 && userMoney != 0) {
						cout << "\nIt is your turn to be the big blind. You must put in $100.\nThe dealer puts in $50" << endl;
						potMoney += 150;
						userMoney -= 100;
					}
				}
				else if (userOption == 2 && dealerRaiseAmts<userMoney) {
					userMoney -= dealerRaiseAmts;
					potMoney += dealerRaiseAmts;
					cout << "You matched the dealer. Here's the next hand." << endl;
					cout << endl;
					nextHand(isFlop, isTurn, isRiver,cVect,playerHand,userMoney,potMoney,gameOver);
					if (gameOver) {
						if (userMoney <= 0) {
							cout << endl;
							cout << "You have lost all your money after " << gamesPlayed << " games." << endl;
							break;
						}
						newGame(playerHand, dealer, dealerCheck, dealerFold, dealerRaise, isFlop, isTurn, isRiver, cVect);
						gameOver = false;
						potMoney = 0;
						gamesPlayed++;
						if (gamesPlayed % 3 == 0 && userMoney != 0) {
							cout << "\nIt is your turn to be the small blind. You must put in $50.\nThe dealer puts in $100" << endl;
							potMoney += 150;
							userMoney -= 50;
						}
						else if (gamesPlayed % 4 == 0 && userMoney != 0) {
							cout << "\nIt is your turn to be the big blind. You must put in $100.\nThe dealer puts in $50" << endl;
							potMoney += 150;
							userMoney -= 100;
						}
					}
				}
				else {
					cout << "\nYou are going all in.\n" << endl;
					userMoney -= dealerRaiseAmts;
					potMoney += dealerRaiseAmts;
					nextHand(isFlop, isTurn, isRiver, cVect, playerHand, userMoney, potMoney, gameOver);
					if (gameOver) {
						if (userMoney <= 0) {
							cout << endl;
							cout << "You have lost all your money after "<<gamesPlayed<<" games." << endl;
							break;
						}
						newGame(playerHand, dealer, dealerCheck, dealerFold, dealerRaise, isFlop, isTurn, isRiver, cVect);
						gameOver = false;
						potMoney = 0;
						gamesPlayed++;
						if (gamesPlayed % 3 == 0 && userMoney != 0) {
							cout << "\nIt is your turn to be the small blind. You must put in $50.\nThe dealer puts in $100" << endl;
							potMoney += 150;
							userMoney -= 50;
						}
						else if (gamesPlayed % 4 == 0 && userMoney != 0) {
							cout << "\nIt is your turn to be the big blind. You must put in $100.\nThe dealer puts in $50" << endl;
							potMoney += 150;
							userMoney -= 100;
						}
					}
				}
			}
		}
		else if (userOption == 3) {
			cout << "How much do you want to raise by: ";
			int userRaise;
			cin >> userRaise;
			if (userRaise >= userMoney) {
				cout << "That is more than you can bet. You are going all in." << endl;
				userRaise = userMoney;
			}

			potMoney += userRaise;
			userMoney -= userRaise;
			cout << "Your money: " << userMoney << endl;
			cout << "Money in pot: " << potMoney << endl;

			dealer.newChoice(dealerChoice());

			if (userRaise <= 200) {
				if (dealer.choice != 1) {
					cout << "Dealer matched your bet. Here's the next hand." << endl;
					potMoney += userRaise;
					cout << endl;
					nextHand(isFlop, isTurn, isRiver, cVect, playerHand, userMoney, potMoney, gameOver);
					if (gameOver) {
						if (userMoney <= 0) {
							cout << endl;
							cout << "You have lost all your money after " << gamesPlayed << " games." << endl;
							break;
						}
						newGame(playerHand, dealer, dealerCheck, dealerFold, dealerRaise, isFlop, isTurn, isRiver, cVect);
						gameOver = false;
						potMoney = 0;
						gamesPlayed++;
						if (gamesPlayed % 3 == 0 && userMoney != 0) {
							cout << "\nIt is your turn to be the small blind. You must put in $50.\nThe dealer puts in $100" << endl;
							potMoney += 150;
							userMoney -= 50;
						}
						else if (gamesPlayed % 4 == 0 && userMoney != 0) {
							cout << "\nIt is your turn to be the big blind. You must put in $100.\nThe dealer puts in $50" << endl;
							potMoney += 150;
							userMoney -= 100;
						}
					}
				}
				else {
					cout << "Dealer folds. You win " << potMoney << endl;
					userMoney += potMoney;
					newGame(playerHand, dealer, dealerCheck, dealerFold, dealerRaise, isFlop, isTurn, isRiver, cVect);
					potMoney = 0;
					gameOver = false;
					gamesPlayed++;
					if (gamesPlayed % 3 == 0 && userMoney != 0) {
						cout << "\nIt is your turn to be the small blind. You must put in $50.\nThe dealer puts in $100" << endl;
						potMoney += 150;
						userMoney -= 50;
					}
					else if (gamesPlayed % 4 == 0 && userMoney != 0) {
						cout << "\nIt is your turn to be the big blind. You must put in $100.\nThe dealer puts in $50" << endl;
						potMoney += 150;
						userMoney -= 100;
					}
				}
			}
			else if (dealer.choice == 1) {
				cout << "Dealer matched your bet. Here's the next hand." << endl;
				potMoney += userRaise;
				cout << endl;
				nextHand(isFlop, isTurn, isRiver, cVect, playerHand,userMoney,potMoney,gameOver);
				if (gameOver) {
					if (userMoney <= 0) {
						cout << endl;
						cout << "You have lost all your money after " << gamesPlayed << " games." << endl;
						break;
					}
					newGame(playerHand, dealer, dealerCheck, dealerFold, dealerRaise, isFlop, isTurn, isRiver, cVect);
					gameOver = false;
					potMoney = 0;
					gamesPlayed++;
					if (gamesPlayed % 3 == 0 && userMoney != 0) {
						cout << "\nIt is your turn to be the small blind. You must put in $50.\nThe dealer puts in $100" << endl;
						potMoney += 150;
						userMoney -= 50;
					}
					else if (gamesPlayed % 4 == 0 && userMoney != 0) {
						cout << "\nIt is your turn to be the big blind. You must put in $100.\nThe dealer puts in $50" << endl;
						potMoney += 150;
						userMoney -= 100;
					}
				}
			}
			else {
				cout << "Dealer folds. You win " << potMoney << endl;
				userMoney += potMoney;
				newGame(playerHand, dealer, dealerCheck, dealerFold, dealerRaise, isFlop, isTurn, isRiver, cVect);
				potMoney = 0;
				gameOver = false;
				gamesPlayed++;
				if (gamesPlayed % 3 == 0 && userMoney != 0) {
					cout << "\nIt is your turn to be the small blind. You must put in $50.\nThe dealer puts in $100" << endl;
					potMoney += 150;
					userMoney -= 50;
				}
				else if (gamesPlayed % 4 == 0 && userMoney != 0) {
					cout << "\nIt is your turn to be the big blind. You must put in $100.\nThe dealer puts in $50" << endl;
					potMoney += 150;
					userMoney -= 100;
				}
			}
		}

		
		cout << "\nYour money: " << userMoney << endl;
		cout << "Money in pot: " << potMoney << endl;

		playerHand.printHand();
		cout << "\n 0. Exit \n 1. Fold \n 2. Check \n 3. Bet\n Enter your option: ";
		cin >> userOption;
		cout << endl;

		/*if (!isFlop && userOption != 3) {
			cout << "Initial pot: You both put in $50" << endl;
			potMoney += 100;
			userMoney -= 50;
		}*/
	}
	return 0;
}