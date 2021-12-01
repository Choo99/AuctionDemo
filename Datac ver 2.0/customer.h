#ifndef CUSTOMER_H
#define CUSTOMER_H
#include<string>
class Customer
{
public:
	struct customer
	{
		std::string username;
		std::string password;
		std::string name;
		int age;
		customer* next;
		customer* before;
	}*head, * tail;

	Customer();
	~Customer();
	customer* iniNode(std::string, std::string, std::string,int);
	void addNode(customer*);										// pass customer information to list											
	void deleteList(customer*);
	void readFile();													 
	void writeFile(std::string, std::string, std::string,int);		//	write customer information into "customer" file
	void logIn();													// customer and staff login interface
	void reg();														// customer registration interface
	void Function(std::string);										// interface to let customer choose function
	void displayCustomer(customer*);								// show customer information
};
#endif
