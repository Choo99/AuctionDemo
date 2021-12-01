#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "antique.h"
#include "customer.h"
#include "staff.h"
using namespace std;

antique::antique()
{
	head = NULL;
	tail = NULL;
}

antique::~antique() {}


//initiate a new node and insert data into it
antique::Antique* antique::iniNode(int id, int price, string name)
{
	Antique* newNode = new Antique;
	newNode->id = id;
	newNode->price = price;
	newNode->name = name;
	return newNode;
}
//open the input file and take data from the file to add into item list 
void antique::openfile()
{
	int price, id;
	string name;
	ifstream Myfile;
	antique::Antique* ptr;
	Myfile.open("data.txt");
	while (Myfile >> id, getline(Myfile, name, '|'), getline(Myfile, name, '|'), Myfile >> price)
	{
		ptr = iniNode(id, price, name);
		addNode(ptr);
	}
	Myfile.close();
}
//add the initiated node into the linked list
void antique::addNode(Antique* newNode)
{
	if (head == NULL)					// if newNode is the first node
	{
		head = newNode;
		tail = newNode;
		tail->before = NULL;
		return;
	}
	tail->next = newNode;
	newNode->before = tail;
	newNode->next = NULL;
	tail = newNode;						// every added newNode will be the tail
}

//delete the a item from list when needed
void antique::deleteNode(Antique* ptr)
{
	Antique* temp, * prev;
	temp = ptr;
	prev = head;

	if (temp == prev)
	{
		head = head->next;
		if (tail == temp)
		{
			tail = tail->next;
		}
		delete temp;
	}
	else
	{
		while (prev->next != temp)
		{
			prev = prev->next;
		}
		if (prev->next != NULL)
		{
			prev->next = temp->next;
		}
		if (tail == temp)
		{
			tail = prev;
		}
		delete temp;
	}
}

// display the item details in a single node
void antique::displayNode(Antique* ptr)
{
	cout << "--------------------------------------------------------------------------\n";
	cout << "|" << setw(20) << "Items" << setw(15) << "|" << setw(10) << "ID" << setw(10) << "|" << setw(12) << "Price" << setw(7) << "|\n";
	cout << "--------------------------------------------------------------------------\n";
	cout << "|" << setw(25) << ptr->name << setw(10) << "|" << setw(11) << ptr->id << setw(9) << "|" << setw(12) << ptr->price << setw(7) << "|\n";
	cout << "--------------------------------------------------------------------------\n";
}

//display details of the whole item list and user can decide the ways of tables presented by select "id", "price" and name
void antique::displayList(Antique* ptr, int type)
{

	switch (type)
	{
	case 1: //display the table odered by price
		cout << "--------------------------------------------------------------------------\n";
		cout << "|" << setw(12) << "Price" << setw(7) << "|" << setw(10) << "ID" << setw(10) << "|" << setw(20) << "Items" << setw(15) << "|\n";
		cout << "--------------------------------------------------------------------------\n";
		while (ptr)
		{
			cout << "|" << setw(12) << ptr->price << setw(7) << "|" << setw(11) << ptr->id << setw(9) << "|" << setw(25) << ptr->name << setw(10) << "|\n";
			cout << "--------------------------------------------------------------------------\n";
			ptr = ptr->next;
		}
		break;
	case 2: //display the table odered by id
		cout << "--------------------------------------------------------------------------\n";
		cout << "|" << setw(10) << "ID" << setw(10) << "|" << setw(20) << "Items" << setw(15) << "|" << setw(12) << "Price" << setw(7) << "|\n";
		cout << "--------------------------------------------------------------------------\n";
		while (ptr)
		{
			cout << "|" << setw(11) << ptr->id << setw(9) << "|" << setw(25) << ptr->name << setw(10) << "|" << setw(12) << ptr->price << setw(7) << "|\n";
			cout << "--------------------------------------------------------------------------\n";
			ptr = ptr->next;
		}
		break;
	case 3: //display the table odered by name of items
		cout << "--------------------------------------------------------------------------\n";
		cout << "|" << setw(20) << "Items" << setw(15) << "|" << setw(10) << "ID" << setw(10) << "|" << setw(12) << "Price" << setw(7) << "|\n";
		cout << "--------------------------------------------------------------------------\n";
		while (ptr)
		{
			cout << "|" << setw(25) << ptr->name << setw(10) << "|" << setw(11) << ptr->id << setw(9) << "|" << setw(12) << ptr->price << setw(7) << "|\n";
			cout << "--------------------------------------------------------------------------\n";
			ptr = ptr->next;
		}
		break;
	}
}

/* swap the id and price of antique */
void antique::swapInt(int* a, int* b)
{
	int c = *a;
	*a = *b;
	*b = c;
}

/* swap the name of antique*/
void antique::swapStr(string* a, string* b)
{
	string c = *a;
	*a = *b;
	*b = c;
}

//find out the middle node in the linked list to associate the function of binary search
antique::Antique* antique::middle(Antique* start, Antique* last)
{
	if (start == NULL)					// if the list is empty force the function to stop and return NULL
		return NULL;

	Antique* slow = start;
	Antique* fast = start->next;

	while (fast != last)			//middle of the list will found when the faster node become NULL and middle is the slower node
	{
		fast = fast->next;
		if (fast != last)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}

	return slow;
}

//function that help the function quick sort. 
//It seperate the list of item become two parts which is greater then pivot  at the right side and smaller then pivot at the left side
//This function can sort the item's id,price and name
antique::Antique* antique::partition(Antique* low, Antique* high, int type)
{
	int pivot = 0;				//case 1 = price
								//case 2 = id
	switch (type)				//case 3 = name
	{
	case 1:							
		pivot = high->price;	//set the tail of the list as pivot
		break;
	case 2:
		pivot = high->id;
		break;
	case 3:
		pivot = (int)(high->name[0]);
		break;
	}

	Antique* i = low->before;

	for (Antique* j = low; j != high; j = j->next) //set j as the head of the list
	{
		switch (type)
		{
		case 1:
			if (j->price <= pivot)	//swap with i when j found a data is smaller then pivot
			{
				if (i == NULL)
				{
					i = low;
				}
				else
				{
					i = i->next;
				}
				swapInt(&(i->price), &(j->price)); //swap data inside the node
				swapInt(&(i->id), &(j->id));
				swapStr(&(i->name), &(j->name));
			}
			break;
		case 2:
			if (j->id <= pivot)
			{
				if (i == NULL)
				{
					i = low;
				}
				else
				{
					i = i->next;
				}
				swapInt(&(i->price), &(j->price));
				swapInt(&(i->id), &(j->id));
				swapStr(&(i->name), &(j->name));
			}
			break;
		case 3:
			if ((int)(j->name[0]) <= pivot)
			{
				if (i == NULL)
				{
					i = low;
				}
				else
				{
					i = i->next;
				}
				swapInt(&(i->price), &(j->price));
				swapInt(&(i->id), &(j->id));
				swapStr(&(i->name), &(j->name));
			}
			break;
		}
	}
	if (i == NULL)
	{
		i = low;
	}
	else
	{
		i = i->next;
	}
	swapInt(&(i->price), &(high->price));	//swap pivot with i to place the pivot in correct place
	swapInt(&(i->id), &(high->id));
	swapStr(&(i->name), &(high->name));
	return i;
}

//sort the list in ascending order
void antique::quickSort(Antique* head, Antique* tail, int type)
{
	if (tail != NULL && head != tail && head != tail->next)
	{
		Antique* temp;
		temp = antique::partition(head, tail, type);	//seperate the list  into two part
		antique::quickSort(head, temp->before, type);	//quick sort the left side part
		antique::quickSort(temp->next, tail, type);		//quick sort the right side part
	}
}

// to check whether the target (id/price) is inside the list or not
bool antique::sentinelsearch(Antique* ptr, int target, int type)
{
	bool found = false;			    //case 1 = price
	int temp;						//case 2 = id
	switch (type)
	{
	case 1:
		if (tail->price == target) //check the tail of list before set as sentinel data
		{
			return found = true;
		}
		else
		{
			temp = tail->price;
			tail->price = target;
			while (ptr->price != target)
			{
				ptr = ptr->next;
			}
		}
		if (ptr != tail)
		{
			found = true;
		}
		tail->price = temp;
		break;
	case 2:
		if (tail->id == target)
		{
			return found = true;
		}
		else
		{
			temp = tail->id;
			tail->id = target;
			while (ptr->id != target)
			{
				ptr = ptr->next;
			}
		}
		if (ptr != tail)
		{
			found = true;
		}
		tail->id = temp;
		break;
	}

	return found;
}

// to retrieve the target data inside the list 
antique::Antique* antique::binary(Antique* head, Antique* tail, int target, int type)
{

	Antique* begin = head;				//case 1 = price
	Antique* end = NULL;				//case 2 = id

	while (end == NULL || end != begin)
	{
		Antique* mid = middle(begin, end);
		if (mid == NULL)
		{
			return NULL;
		}
		switch (type)
		{
		case 1:
			if (mid->price == target)
			{
				return mid;
			}
			else if (mid->price < target)
			{
				begin = mid->next;
			}
			else
			{
				end = mid;
			}
			break;
		case 2:
			if (mid->id == target)
			{
				return mid;
			}
			else if (mid->id < target)
			{
				begin = mid->next;
			}
			else
			{
				end = mid;
			}
		}
	}
	return NULL;
}

/* let customer and staff to search or display antique
information based on id, name, price of antique */
void antique::antiqueFunction(string user)
{
	Customer cus;
	Staff admin;
	Antique* ptr;
	int type = 1;
	int choice;
	int target;
	int choi;
	bool found;
	// if the list is empty, then read data from file and insert to list
	// if there is any data in list, the old data will be deleted everytime to ensure the data is updated 
	if (head == NULL)
	{
		openfile();
	}
	else
	{
		deleteList(head);
		openfile();
	}
	system("cls");

	do
	{
		displayList(head, type);
		cout << endl;
		cout << "What do you looking for?\n";
		cout << "1. Search\n";				//search a item in the list 
		cout << "2. Display in order\n";	//display the details of items
		cout << "3. Return\n";				//return to previous page
		cout << "Your choice:";
		cin >> choice;
		system("cls");
		switch (choice)
		{

		case 1:
			do
			{
				system("cls");
				displayList(head, type);
				cout << "Search in:\n";		//user can find a specific item by searching its price and id
				cout << "1. Price\n";
				cout << "2. Id\n";
				cout << "3. Return\n";
				cout << "Your choice:";
				cin >> choi;
				if (choi == 3)
				{
					antiqueFunction(user);
					return;
				}
			} while (choi > 3);
			cout << "Enter your target\n";
			cout << "Target: ";
			cin >> target;
			quickSort(head, tail, choi);
			found = sentinelsearch(head, target, choi);
			if (found == true)
			{
				ptr = binary(head, tail, target, choi);
				displayNode(ptr);
			}
			else
			{
				cout << "Unable find the target!" << endl;
			}
			cout << "Press any key to continue";
			system("pause>nul");
			antiqueFunction(user);
			break;

		case 2:
			do
			{
				system("cls");
				cout << "Display in order of:\n"; //display the item list in three ways : price,id and name
				cout << "1. Price\n";
				cout << "2. Id\n";
				cout << "3. Name\n";
				cout << "4. Return\n";
				cout << "Your choice:";
				cin >> choi;
				if (choi >= 1 && choi <= 3)
				{
					quickSort(head, tail, choi);
					displayList(head, choi);
					cout << "Press any key to continue";
					system("pause>nul");
					system("cls");
				}
				else if (choi == 4)
				{
					antiqueFunction(user);
				}
				else
				{
					cout << "Invalid input! Please try again!\n";
					cout << "Press any key to continue";
					system("pause>nul");
					system("cls");
				}
			} while (choi != 4);
			break;

		case 3:
			system("cls");
			if (user == "admin")
			{
				admin.staffFunction();
			}
			else
			{
				cus.Function(user);
			}
			break;
		default:
			cout << "invalid choice!";
			cout << "Press any key to continue";
			system("pause>nul");
			system("cls");
		}
	} while (choice > 3);
}

/*Whole linked list will be deleted to ensure all updated information will be the latest*/
void antique::deleteList(Antique* ptr)
{
	Antique* temp;

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

