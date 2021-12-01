#include <iostream>
#include <string>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include "auction.h"
#include "antique.h"
#include "customer.h"
using namespace std;

Auction::Auction(int n1, int n2, int n3, int n4)
{
	num1 = n1;
	num2 = n2;
	num3 = n3;
	num4 = n4;
}
Auction::Auction()
{
	num1=0;
	num2=0;
	num3=0;
	num4=0;
}
Auction::~Auction() {}

//display item's introduction before customer start to bid  
void Auction::intro(int ID)
{
	int id;
	ifstream Myfile;
	string intro;
	Myfile.open("intro.txt");
	while (Myfile >> id, getline(Myfile, intro, '|'))
	{
		if (id == ID)
		{
			break;
		}
	}
	Myfile.close();
	cout << "************************************************************************************************************************\n";
	for (int i = 1; i < intro.length(); i++)
	{
		cout << intro[i];
		Sleep(5);
		if (intro[i] == ' ')
		{
			Sleep(100);
		}
		if (intro[i] == '.')
		{
			Sleep(1000);
		}
	}
	cout << "\n************************************************************************************************************************\n";
	Sleep(5000);
}
//there was 4 bot and 1 user in the auction
void Auction::auction(string user, bool admin)
{
	antique item;
	antique::Antique* ptr;
	Customer cus;
	Customer::customer* bot_name = cus.head;
	ofstream Myfile;
	Auction bot1(10, 15, 30, 35), bot2(50, 55, 70, 75), bot3(170, 175, 195, 200), bot4(215, 220, 235, 240), bot5(100, 105, 150, 155);
	Myfile.open("profit.txt");
	int add, addPrice, choice;
	int i = 10, count = 0;
	bool hit = false;
	bool b01 = true, b02 = true, b03 = true, b04 = true, b05 = true, count_user = false, count_bot = false, check = true;
	string name, bot_name1, bot_name2, bot_name3, bot_name4, bot_name5;

	if (item.head == NULL) //open the customer list and item list
	{
		item.openfile();
	}
	if (cus.head == NULL)
	{
		cus.readFile();
	}

	for (bot_name = cus.head; bot_name != NULL; bot_name = bot_name->next)  //set the bot name as the customer name in the customer list
	{																		//4 bot will enable when the auction is start with identity of custtomer
		if (bot_name->name != user)											//The fifth bot will only enable when auction start with identity of staff 
		{
			count++;
		}
		if (bot_name->name != user && count == 1)
		{
			bot_name1 = bot_name->name;
		}
		else if (bot_name->name != user && count == 2)
		{
			bot_name2 = bot_name->name;
		}
		else if (bot_name->name != user && count == 3)
		{
			bot_name3 = bot_name->name;
		}
		else if (bot_name->name != user && count == 4)
		{
			bot_name4 = bot_name->name;
		}
		else if (bot_name->name != user && count == 5 && admin == true)
		{
			bot_name5 = bot_name->name;
		}
	}
	ptr = item.head;

	cout << setw(88) << "****************************************************************************\n";
	cout << setw(70) << "Welcome to our Antique Auction System\n";
	cout << setw(90) << "****************************************************************************\n\n\n";
	cout << setw(86) << "Tonight has tons of wonderful antique provided. Hope you enjoyed the night!";
	Sleep(3000);
	system("cls");

	do
	{
		cout << setw(60) << ptr->name << endl;
		Sleep(1000);
		intro(ptr->id);
		cout << setw(68) << "The price is start from " << ptr->price << endl << endl;		//some rules of the auction
		Sleep(1000);
		cout << setw(83) << "You can place 10% of the reserve price once\n\n";
		Sleep(1000);
		cout << setw(95) << "Auction will end once the highest bid has been called after 10 seconds\n\n";
		Sleep(1000);
		cout << setw(70) << "Auction will start in 5 seconds";
		Sleep(1000);
		for (int i = 0; i < 5; i++)
		{
			cout << ".";
			Sleep(1000);
		}
		system("cls");
		addPrice = ptr->price;
		add = 0.1 * ptr->price;
	jump:
		do
		{							//customer can choose to place a bid or wait for next item
			srand(time(0));
			for (i = 10; i > 0; i--)
			{
				if (admin != true)
				{
					if (_kbhit() && count_user != true)	//user can place a bid when he is customer
					{									//when user want to place a bid, just hit the keyboard and key in the choice
						system("cls");					//if not, there was our turn of bot to place a bid 
						cout << setw(70) << "Now the price was " << addPrice << endl << endl;
						cout << setw(80) << "Do you want to place a bid?\n\n";
						cout << setw(60) << "1. Add " << add << endl << endl;
						cout << setw(60) << "2. No\n\n";
						cout << setw(67) << "Your choice : ";
						cin >> choice;
						switch (choice)
						{
						case 1:
							count_user = true;			//diable the function of user to place a bid to prevent the situation where user placed a bid twice even he has the highest bid
							count_bot = false;			//enable the bot to place a bid
							addPrice += add;			//add price into the item's price
							name = user;
							check = true;
							goto jump;
							break;
						case 2:
							break;
						}

					}
				}
				system("cls");

				if (count_bot == true)				//display when bot place the highest bid
				{									//display the name who has the highest bid
					cout << setw(55) << name << " has the highest bid!\n\n";
				}
				if (count_user == true)		//display when user place the highest bid
				{
					cout << setw(90) << "You have the highest bid! Please wait for 10 seconds\n";
				}
				else			//ask user to place a bid continuously
				{
					cout << setw(70) << "Now the price was " << addPrice << endl << endl;
					if (admin != true)
					{
						cout << setw(80) << "Do you want to place a bid?\n\n";
						cout << setw(60) << "1. Add " << add << endl << endl;
						cout << setw(60) << "2. No\n\n";
						cout << setw(67) << "Your choice : ";
					}
				}
				cout << endl << endl << setw(54) << i << " second remaining";
				Sleep(1000);
				hit = bot1.bot(bot_name1, name, addPrice, add, count_bot, count_user, b01, b02, b03, b04, b05); //bot1 try to place a bid
				if (hit == true)		//if the bot place a bid successfully, the bot name will be recorded 
				{
					name = bot_name1;
					break;
				}
				hit = bot2.bot(bot_name2, name, addPrice, add, count_bot, count_user, b02, b01, b03, b04, b05);
				if (hit == true)
				{
					name = bot_name2;
					break;
				}
				hit = bot3.bot(bot_name3, name, addPrice, add, count_bot, count_user, b03, b02, b01, b04, b05);
				if (hit == true)
				{
					name = bot_name3;
					break;
				}
				hit = bot4.bot(bot_name4, name, addPrice, add, count_bot, count_user, b04, b02, b03, b01, b05);
				if (hit == true)
				{
					name = bot_name4;
					break;
				}
				if (admin == true)
				{
					hit = bot5.bot(bot_name5, name, addPrice, add, count_bot, count_user, b05, b02, b03, b04, b01);
					if (hit == true)
					{
						name = bot_name5;
						break;
					}
				}
			}
		} while (i != 0);
		cout << "\n\n" << setw(105) << "***********************************************************************\n";			//display the name who win the bid and the price
		cout << setw(55) << "Congratulation " << name << "! He bids the " << ptr->name << " with price " << addPrice << endl;
		cout << setw(105) << "***********************************************************************\n";
		Sleep(3000);

		Myfile << "|" << ptr->name << "|" << name << "|" << ptr->price << " " << addPrice << " " << addPrice - ptr->price << endl; //write the details of the price into file

		ptr = ptr->next;

		if (ptr != NULL)
		{
			cout << endl << setw(80) << "Auction will continue in 5 second"; //ready to continue the auction
			for (int i = 0; i < 5; i++)
			{
				cout << ".";
				Sleep(1000);
			}
			count_bot = false;
			count_user = false;
			b01 = true;
			b02 = true;
			b03 = true;
			b04 = true;
			system("cls");
		}
		else
		{
			cout << setw(90) << "This is the last items in our auction! Auction will end in 5 second";
			for (int i = 0; i < 5; i++)
			{
				cout << ".";
				Sleep(1000);
			}
			system("cls");		//program end
			cout << setw(88) << "****************************************************************************\n";
			cout << setw(72) << "Thank you for using our Antique Auction System\n";
			cout << setw(90) << "****************************************************************************\n\n\n";
			Sleep(3000);
		}
	} while (ptr != NULL);
	Myfile.close();
}

bool Auction::bot(string bot_name, string& name, int& addPrice, int add, bool& count_bot, bool& count_user, bool& b0, bool& b01, bool& b02, bool& b03, bool& b04)
{
	bool check = false;
	int bot;

	if (b0 == true)
	{
		bot = rand() % 250 + 1;												//get a random number
		if ((bot >= num1 && bot <= num2) || (bot >= num3 && bot <= num4))	//if the random number is inside the range, the bot can place a bid 
		{
			cout << "\n\n" << setw(78) << "*****************************\n";
			cout << setw(55) << bot_name << " has placed a new bid!\n";
			cout << setw(78) << "*****************************\n";
			addPrice += add;
			Sleep(1000);
			name = bot_name;
			count_bot = true;		//enable user to place a bid
			count_user = false;		
			b0 = false;				//disable the bot who placed a bid
			b01 = true;				//enable other bot to place a bid
			b02 = true;
			b03 = true;
			b04 = true;
			check = true;
		}
	}
	return check;
}

