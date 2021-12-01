#ifndef ANQIQUE_H
#define ANTIQUE_H
class antique
{
public:
	struct Antique
	{
		int code = 0;
		int id;
		int price;
		std::string name;
		Antique* next;
		Antique* before;
	}*head, * tail;

	antique();
	~antique();
	//function of list
	Antique* iniNode(int, int, std::string);
	void addNode(Antique*);
	void openfile();
	void deleteNode(Antique*);

	//function of display
	void displayNode(Antique*);
	void displayList(Antique*, int);

	//function of swap element in node
	void swapInt(int*, int*);
	void swapStr(std::string*, std::string*);

	//function of sort
	Antique* partition(Antique*, Antique*, int);
	void quickSort(Antique*, Antique*, int);

	//function of search
	bool sentinelsearch(Antique*, int, int);
	Antique* binary(Antique*, Antique*, int, int);
	Antique* middle(Antique*, Antique*);

	void antiqueFunction(std::string);
	void deleteList(Antique*);
};

#endif

