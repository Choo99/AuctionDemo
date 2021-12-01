#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
#include "customer.h"
#include "antique.h"
#include "staff.h"
#include "auction.h"
using namespace std;

Customer::Customer()
{
	head = NULL;
	tail = NULL;
}
Customer::~Customer(){}

//initiate a new node and put data into node 
Customer::customer* Customer::iniNode(string username,string password,string name,int age)
{
	customer* NewNode = new customer;
	NewNode->username = username;
	NewNode->password = password;
	NewNode->name = name;
	NewNode->age = age;
	return NewNode;
}
//add a node into the customer list
void Customer::addNode(customer* NewNode)
{
	if (head == NULL)
	{
		head = NewNode;
		tail = NewNode;
		tail->before = NULL;
		return;
	}
	tail->next = NewNode;
	NewNode->before = tail;
	NewNode->next = NULL;
	tail = NewNode;
}
//delete the whole customer list to make sure the data is newest
void Customer::deleteList(customer* ptr)
{
	customer* temp;

	if (head == NULL)
	{
		return;
	}
	if (ptr == head)
	{
		head = NULL;
		tail = NULL;
	}
	else
	{
		temp = head;
		while (temp->next != ptr)
		{
			temp = temp->next;
		}
		tail = temp;
	}

	while (ptr != NULL)
	{
		temp = ptr->next;
		delete ptr;
		ptr = temp;
	}

}
//open a input file and take data from it to add into customer list
void Customer::readFile()
{
	string username, password, name;
	int age;
	fstream Myfile;
	customer* ptr;
	Myfile.open("customer.txt");

	if (Myfile.is_open())
	{
		while (getline(Myfile, username, '|'), getline(Myfile, username, '|'), getline(Myfile, password, '|'), getline(Myfile, name, '|'), Myfile >> age)
		{
			ptr = iniNode(username, password, name, age);
			addNode(ptr);
		}
	}
	Myfile.close();
}

//a new account register by customer and the details of account write into output file
void Customer::writeFile(string username, string password, string name, int age)
{
	fstream Myfile;
	Myfile.open("customer.txt", fstream::app);
	if (Myfile.is_open())
	{
		Myfile  << '|' << username << '|' << password << '|' << name << '|' << age << endl;
		Myfile.close();
	}
}
// log in page of user
void Customer::logIn()
{
	Staff admin;
	string username, password, user;
	int choice;
	bool check = 0;
	if (head == NULL)
	{
		readFile();
	}
	else
	{
		deleteList(head);
		readFile();
	}
	system("cls");

	cout << "1. Log In Your Account."<<endl;	//log in the account
	cout << "2. Register an new account."<<endl;//register a new account
	cout << "3. Return\n";						//return to last page
	cout << "Your choice: "; 
	cin >> choice;
	switch (choice)
	{
	case 1:
		do
		{
			cout << "username: ";
			cin >> username;
			cout << "password: ";
			cin >> password;
			for (customer* i = head; i != NULL; i = i->next) //check the existance of the username in the file and also the password
			{
				if (username == i->username)
				{
					if (username == i->username && password == i->password)
					{
						cout << "Log in successfully! Welcome "<<i->name<<endl;
						check = true;
						user = i->name;
						break;
					}
				}
			}
			if (check == false)	//display error message when username or password was wrong
			{
				cout << "Your username or password was wrong. Please reenter." << endl;
			}
		} while (check == false);
		cout << "Press any key to continue";
		system("pause>nul");
		system("cls");
		Function(user);
		break;
	case 2:
		reg();
		break;
	case 3:
		system("cls");
		admin.inter();
	}
}
// register page of new account for new user
//customer need to create a new username and password and enter details of the user
void Customer::reg()
{
	string username, name, password,password2;
	bool check=0;
	int age;
	cout << "Username: "; 
	cin >> username;
	do
	{
		cout << "Password: ";		//user need to make sure the password is same
		cin >> password;
		cout << "Confirm password: ";
		cin >> password2;
		if (password == password2)
		{
			check = true;
		}
		else
		{
			cout << "Your are key in difference password, please try again.\n";
		}
	} while (check == false);
	cout << "Name: ";
	cin.ignore();
	getline(cin, name);
	cout << "Age:";
	cin >> age;
	writeFile(username, password, name, age);
	cout << "You create an account successfully!\n";
	cout << "Press any key to continue";
	system("pause>nul");
	system("cls");
	logIn();
}

//let user check tthe item list, customer list or ready for the auction
void Customer::Function(string user)
{
	int choice;
	antique function;
	Auction start;

	if (head == NULL)		//make sure the data in the list is lastest
	{
		readFile();
	}
	else
	{
		deleteList(head);
		readFile();
	}
	do
	{
		cout << "What do you want to do?\n";
		cout << "1. Check item list\n";			//check the details of items that will be bid in the auction
		cout << "2. Check customer list\n";		//check the details of other user
		cout << "3. Ready to start aution\n";	//ready for start the auction
		cout << "4. Change account\n";			//return to log in page
		cout << "Your choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			function.antiqueFunction(user);
			break;
		case 2:
			displayCustomer(head);
			cout << "Press any key to continue";
			system("pause>nul");
			system("cls");
			Function(user);
			break;
		case 3:
			system("cls");
			function.deleteList(function.head);
			function.openfile();
			start.auction(user, false);
			break;
		case 4:
			logIn();
			break;
		default:
			cout << "Invalid choice!";
		}
	} while (choice != 3);
}
//display the details of customer 
void Customer::displayCustomer(customer* ptr)
{
	int i = 1;
	cout << "-----------------------------------------------\n"; 
	cout << "|" << setw(5) << "No." << setw(2) << "|" << setw(15) << "Name" << setw(15) << "|" << setw(5) << "Age" << setw(4) << "|"<<endl;
	cout << "-----------------------------------------------\n";
	while (ptr)
	{
		cout << "|" << setw(3) << i << setw(4) << "|" << setw(18) << ptr->name << setw(12) << "|" << setw(5) << ptr->age << setw(4) << "|" << endl;
		i++;
		ptr = ptr->next;
		cout << "-----------------------------------------------\n";
	}
}