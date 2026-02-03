#include "Stack.h"
#include <string>
#include <iostream>
class PolNode
{
public:
	PolNode(int x,int y,int z,double c);
	PolNode(std::string str);
	PolNode(const PolNode& p);
	PolNode();
	std::string print();
	int get_power() noexcept { return power; };
	double get_const() noexcept { return cnst; };
	PolNode& operator+(PolNode& p);
	PolNode& operator*(PolNode& p);
	PolNode& PolNode::operator=(const PolNode& p);
	~PolNode();
private:
	int power{}; //Степень полинома в "свернутом" виде
	double cnst{}; //Константа 
};

class Polinome
{
public:
	Polinome(std::string str);
	Polinome();
	void add(PolNode p);
	void add(std::string str);
	Polinome(const Polinome& other); 
	Polinome& operator=(const Polinome& other);
	Polinome& operator+(Polinome& p);
	Polinome& operator*(Polinome& p);
	std::string print();
	int size() noexcept { return nodes.StSize(); }
private:
	TStack<PolNode> nodes;
	void parse(std::string str);
};