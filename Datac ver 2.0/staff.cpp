#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "staff.h"
#include "antique.h"
#include "customer.h"
#include "auction.h"
using namespace std;

Staff::Staff(){}

Staff::~Staff() {}
//let staff add a new item and insert details of the item
void Staff::addItem()
{
	system("cls");
	string name, intro;
	int id, price;
	cout << "Enter the antique's name, id and price.\n";
	cout << "Name : ";
	cin >> name;
	cout << "ID : ";
	cin >> id;
	cout << "Price : ";
	cin >> price;
	cout << "Intro : ";
	cin >> intro;

	ofstream Myfile,file;
	Myfile.open("data.txt", ios::app);
	file.open("intro.txt", ios::app);
	if (file.is_open())
	{
		file << id << " " << intro << endl;
	}
	if (Myfile.is_open())
	{
		Myfile << id << "|" << name << "|" << price << endl;
	}
	Myfile.close();
	file.close();
	cout << "New item added successfully!\n";
	cout << "Press any key to continue";
	system("pause>nul");
	system("cls");
}
//staff can delete a item from the list according to the item's id
void Staff::deleteItem()
{
	int find;
	int id, price;
	string name;
	antique item;
	system("cls");
	if (item.head == NULL)
	{
		item.openfile();
	}
	item.displayList(item.head, 2);
	
	cout << "Enter the item id that you want to delete.\n";
	cout << "Target :";
	cin >> find;
	ofstream temp;
	ifstream Myfile;
	temp.open("temp.txt");
	Myfile.open("data.txt");
	while (Myfile >> id, getline(Myfile, name, '|'), getline(Myfile, name, '|'), Myfile >> price)
	{						//write all of the data into a new file beside the selected item
		if (id != find)
		{
			temp << id <<"|"<< name <<"|"<< price << endl;
		}
	}
	Myfile.close();
	temp.close();
	remove("data.txt");				//old file will be delete and new file that doesn't contain the selected item will be rename as old file
	rename("temp.txt", "data.txt");	
	cout << "The item deleted sucessfully!\n";    
	cout << "Press any key to continue";
	system("pause>nul");
	system("cls");
}
//staff can change the price of the item
void Staff::setPrice()
{
	int find;
	int id, price;
	string name, tem;
	antique item;
	system("cls");
	if (item.head == NULL)
	{
		item.openfile();
	}
	item.displayList(item.head, 2);
	cout << "Enter the item id that you want to change.\n";
	cout << "Target :";
	cin >> find;
	ofstream temp;
	ifstream Myfile;
	temp.open("temp.txt");
	Myfile.open("data.txt");
	while (Myfile >> id, getline(Myfile, name, '|'), getline(Myfile, name, '|'), Myfile >> price)
	{					//copy the data to a new file beside the item that want to change price
		if (id != find)
		{
			temp << id << "|" << name << "|" << price << endl;
		}
		else
		{
			tem = name;	//save the details(beside price) of the selected item in temporary
		}
	}
	cout << "Enter price :";
	cin >> price;					//staff key it the new price of the selected item and put into new file with temporary data
	temp << find << "|" << tem << "|" << price << endl;	
	Myfile.close();
	temp.close();
	remove("data.txt");				//old file will be delete and new file that contain the new price of item will be rename as old file
	rename("temp.txt", "data.txt");

	cout << "The item's price changed sucessfully!\n";
	cout << "Press any key to continue";
	system("pause>nul");
	system("cls");
}
//staff can determine the order of the item when the auction start
void Staff::setOrder()
{
	int price, id,code;;
	string name;
	bool check;
	antique item;
	antique::Antique* ptr;
	ofstream temp;
	system("cls");
	if (item.head == NULL)
	{
		item.openfile();
	}
	item.quickSort(item.head, item.tail, 2);
	while (item.head != NULL)
	{
		temp.open("temp.txt",ios::app);
		item.displayList(item.head, 2);
		cout << "Set the order of the list. Enter the item id to select the item.\n";
		cout << "Code : ";
		cin >> code;
		check = item.sentinelsearch(item.head, code, 2);	//check the existance of the item
		if (check == true)									
		{
			ptr = item.binary(item.head, item.tail, code, 2);			
			temp << ptr->id << "|" << ptr->name << "|" << ptr->price << endl;
			item.deleteNode(ptr);							//the selected item will be delete from the list and details of item will write into a tomporary file
			temp.close();									//this step looped until the item list become empty
			ifstream temp1;
			temp1.open("temp.txt");

			cout << "This is the new list\n";
			cout << "------------------------------------------------------------------\n";
			cout << "|" << setw(10) << "ID" << setw(10) << "|" << setw(15) << "Items" << setw(11) << "|" << setw(12) << "Price" << setw(8) << "|\n";
			cout << "------------------------------------------------------------------\n";
			while (temp1 >> id, getline(temp1, name, '|'), getline(temp1, name, '|'), temp1 >> price)
			{
				cout << "|" << setw(11) << id << setw(9) << "|" << setw(23) << name << setw(3) << "|" << setw(14) << price << setw(6) << "|\n";
				cout << "------------------------------------------------------------------\n";
			}
			temp1.close();
			cout << "Press any key to continue";
			system("pause>nul");
			system("cls");
		}
		else
		{
			temp.close();
			cout << "Target not found! Please enter again!\n";
			system("cls");
		}
	}
	remove("data.txt");
	rename("temp.txt", "data.txt");
}
//let staff add new item, delete a item, change the item's price, set order the item list, check the customer list, check item list and start the auction
void Staff::staffFunction()
{
	system("cls");
	string username = "admin";		//default username and password of the staff
	string password = "abc123";
	string user, pass;
	int choice;
	antique item;
	Customer cus;
	Auction start;
jump1:
	cout << "Please log in your account\n";	//log in of the staff
	cout << "username : ";
	cin >> user;
	cout << "password : ";
	cin >> pass;
	if (user == username && pass == password)
	{
		cout << "Welcome back admin! ";
		cout << "Press any key to continue";
		system("pause>nul");
		system("cls");
	}
	else
	{
		cout << "Your username or password is wrong. Please enter again!\n";
		system("pause>nul");
		system("cls");
		goto jump1;
	}
	do
	{
		cout << "What do you want to do? \n";
		cout << "1. Add a new item into list\n";		
		cout << "2. Delete a item from a list\n";
		cout << "3. Set the price of the item\n";
		cout << "4. Set the order of the item list\n";
		cout << "5. Display customer list\n";
		cout << "6. Display item list\n";
		cout << "7. Start the auction\n";
		cout << "8. Return\n";
		cout << "Your choice : ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			addItem();
			break;
		case 2:
			deleteItem();
			break;
		case 3:
			setPrice();
			break;
		case 4:
			setOrder();
			break;
		case 5:
			if (cus.head == NULL)
			{
				cus.readFile();
			}
			cus.displayCustomer(cus.head);
			cout << "Press any key to continue";
			system("pause>nul");
			system("cls");
			break;
		case 6:
			item.antiqueFunction(user);
			break;
		case 7:
			item.deleteList(item.head);
			item.openfile();
			start.auction("admin", true);
			displayProfit();
			break;
		case 8:
			system("cls");
			inter();
			break;
		default:
			cout << "Invalid input! Please enter again!\n\n";
			cout << "Press any key to continue";
			system("pause>nul");
			system("cls");
		}
	} while (choice >= 1 && choice <= 5);
}
//display the profit of the auction after the program is end
void Staff::displayProfit()
{
	string items, name;
	int  price, addprice, pro;
	ifstream Myfile;
	cout << "------------------------------------------------------------------------------------------------------\n";
	cout << "|" << setw(12) << "Item" << setw(10) << "|" << setw(13) << "Winner" << setw(7) << "|" << setw(14) << "Ori price" << setw(6) << "|" << setw(15) << "Addprice" << setw(5) << "|" << setw(13) << "Profit" << setw(7) << "|\n";
	cout << "------------------------------------------------------------------------------------------------------\n";
	Myfile.open("profit.txt");
	while (getline(Myfile, items, '|'), getline(Myfile, items, '|'), getline(Myfile, name, '|'), Myfile >> price >> addprice >> pro)
	{
		cout << "|" << setw(19) << items << setw(3) << "|" << setw(12) << name << setw(8) << "|" << setw(13) << price << setw(7) << "|" << setw(15) << addprice << setw(5) << "|" << setw(15) << pro << setw(5) << "|\n";
		cout << "------------------------------------------------------------------------------------------------------\n";
	}
	Myfile.close();
	cout << "Press any key to end the program";
	system("pause>nul");
	system("cls");
}
//choose the identity of the user
void Staff::inter()
{
	bool check = true;
	int choice;
	antique item;
	Customer cus;
	cout << setw(80)<<"***************************************\n";
	cout << setw(80) << "*Welcome to our antique auction system*\n";
	cout << setw(81) <<"***************************************\n\n";
	cout << setw(70) << "Press any key to continue";
	system("pause>nul");
	system("cls");
	jump:
		cout << "What is your identity? \n";
		cout << "1. Staff\n";
		cout << "2. User\n";
		cout << "3. Quit\n";
		cout << "Your choice : ";
		cin >> choice;
		switch (choice)
		{
		case 3:
			return;
			break;
		case 2:
			cus.logIn();
			return;
			break;
		case 1:
			system("cls");
			staffFunction();
			return;
			break;
		default:
			cout << "Invalid choice! Please try again!\n\n";
			cout << "Press any key to continue";
			system("pause>nul");
			system("cls");
			goto jump;
			return;
		}
}