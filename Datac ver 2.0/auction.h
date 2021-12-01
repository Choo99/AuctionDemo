#ifndef AUCTION_H
#define AUCTION_H

class Auction
{
private:
	int num1, num2, num3, num4;
public:
	Auction(int, int, int, int);
	Auction();
	~Auction();
	void intro(int);					// introduce the antique details
	void auction(std::string,bool);		//	start auction 
	bool bot(std::string, std::string&, int&, int, bool&, bool&, bool&, bool&, bool&, bool&, bool&);
};
#endif
