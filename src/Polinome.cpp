#include <Polinome.h>
#include <cmath>
double to_dig(std::string str) noexcept {
	int p_n = str.size() ;
	double answ = 0;
	std::string s = "";
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == '.')
			p_n = i;
		else
		{
			s += str[i];
		}
	}
	for (int i = 0; i < s.size(); i++)
	{
		if (p_n - i -1 == 0) {
			answ += (s[i] - '0');
		}
		else
		{
			answ += (s[i] - '0') * pow(10, p_n - i-1);
		}
		
	}
	return answ;
}
int to_dig(char c) noexcept {
	return int(c) - 48;
}
std::string to_str(double dec) {
	std::string t;
	int d = dec;
	double db = dec;
	if (d < 0) {
		d = -d; db = -db;
	}
	while (d!=0)
	{
		t += char(d % 10) + '0';
		d /= 10;
	}
	
	if (dec < 0) t += '-';
	for (size_t i = 0; i < t.size()/2; i++)
	{
		t[i] += t[t.size() - 1 - i];
		t[t.size() - 1 - i] = t[i] - t[t.size() - 1 - i];
		t[i] = t[i] - t[t.size() - 1 - i];
	}
	const double EPS = 1e-9;
	d = db;
	if (db - d > pow(10, -6)) {
		db += EPS;
		t += '.';
		db = db - d;
		for (size_t i = 0; db > pow(10,-6); i++)
		{
			t += char(int(db*=10) + '0');
			db -= int(db);
		}
	}
	return t;
}

PolNode::PolNode() {
	cnst = 0;
	power = 0;
}
PolNode::PolNode(const PolNode& p) {
	cnst = p.cnst;
	power = p.power;
}
PolNode::PolNode(int x, int y, int z, double c)
{
	if (x < 10 && y < 10 && z < 10)
		this->power = x * 100 + y * 10 + z;
	this->cnst = c;
}
PolNode::PolNode(std::string str) {
	int c = 1;
	int cns = 0;
	int i = 0;
	
	if (str[i] == '-') { c = -c; i++; }
	std::string s;
	while (str[i] != 'x' && str[i] != 'y' && str[i] != 'z') {
		s += str[i];
		i++;
	}
	cnst = to_dig(s)*c;
	c = i;
	while (str[i]!='x')
	{
		i++;
	}
	power = to_dig(str[i + 1])*100;
	i = c;
	while (str[i] != 'y')
	{
		i++;
	}
	
	power += to_dig(str[i + 1]) * 10;
	i = c;
	while (str[i] != 'z')
	{
		i++;
	}
	power += to_dig(str[i + 1]);
}
PolNode& PolNode::operator=(const PolNode& p)
{
	if (this != &p) {
		power = p.power;
		cnst = p.cnst;
	}
	return *this;
}
std::string PolNode::print() {
	std::string t;
	t+= to_str(this->get_const());
	t += 'x';
	t += to_str(this->get_power() / 100);
	t += 'y';
	t += to_str((this->get_power() / 10)%10);
	t += 'z';
	t += to_str(this->get_power() %10);
	return t;
}
PolNode& PolNode::operator+(PolNode& p)
{
	PolNode* t = new PolNode(*this);
	(*t).cnst += p.get_const();
	return *t;
}
Polinome::Polinome(const Polinome& other): nodes(other.nodes)
{
}

Polinome& Polinome::operator=(const Polinome& other)
{
	if (this != &other) {
		nodes = other.nodes;
	}
	return *this;
}
PolNode& PolNode::operator*(PolNode& p) {
	PolNode* t = new PolNode(*this);
	(*t).cnst *= p.get_const();
	(*t).power += p.power;
	if ((*t).power>999)
	{
		throw std::out_of_range("Too much power");
	}
	return (*t);
}
PolNode::~PolNode() {
	cnst = 0;
	power = 0;
}


Polinome::Polinome(std::string str)
{
	parse(str);
}
Polinome::Polinome() {
	parse("");
}
void Polinome::add(PolNode p) {

	TStack<PolNode> pols(nodes.StSize());

	while (!(nodes.is_empty()) && nodes.see().get_power() < p.get_power())
	{
		pols.push(nodes.pop());
	}
	if (nodes.is_empty()) {
		nodes.push(p);
	}
	else if (nodes.see().get_power() == p.get_power())
	{
		if ((nodes.see() + p).get_const() == 0) {
			nodes.pop();
		}else
			nodes.see() = nodes.see() + p;
	}
	else {
		nodes.push(p);
	}
	while (!(pols.is_empty()))
	{
		nodes.push(pols.pop());
	}
}
void Polinome::add(std::string str) {
	this->add(PolNode(str));
}
Polinome& Polinome::operator+(Polinome& other) {
	Polinome p(other);
	Polinome* t = new Polinome();
	while (!(nodes.is_empty()) && !(p.nodes.is_empty()))
	{
		if (nodes.see().get_power() > p.nodes.see().get_power()) {
			(*t).nodes.push(nodes.pop());
		}
		else if (nodes.see().get_power() == p.nodes.see().get_power()) {
			(*t).nodes.push(nodes.pop() + p.nodes.pop());
			if ((*t).nodes.see().get_const() == 0) {
				(*t).nodes.pop();
			}
		}
		else
		{
			(*t).nodes.push(p.nodes.pop());
		}
	}
	while (!(nodes.is_empty()))
	{
		(*t).nodes.push(nodes.pop());
	}while (!(p.nodes.is_empty()))
	{
		(*t).nodes.push(p.nodes.pop());
	}
	
	return *(t);
}
Polinome& Polinome::operator*(Polinome& other) {
	Polinome p(*this);
	Polinome* t = new Polinome();
	while (p.size()!=0)
	{
		PolNode node = p.nodes.pop();
		Polinome o(other);
		while (o.size()!=0)
		{
			(*t).add(o.nodes.pop() * node);
		}
	}
	return (*t);
}
void Polinome::parse(std::string str) {
	std::string t ="";
	for (int i = 0; i < str.size(); ++i)
	{
		if (str[i] == '+' ) {
			if (t.size() != 0) {
				this->add(PolNode(t));
			}
			t = "";
		}
		else if (str[i] == '-') {
			if (t.size() != 0) {
				this->add(PolNode(t));
			}
			t = '-';
		}
		else if(str[i] != ' ')
		{
			t += str[i];
		}
	}
	if (t.size() != 0) {
		this->add(PolNode(t));
	}
}
std::string Polinome::print() {
	TStack<PolNode> pols(this->nodes);
	std::string t;
	for (int i = 1; i < this->nodes.StSize(); i++)
	{
		t+=pols.pop().print();
		t+=" + ";
	}
	if (this->size()!=0)
	{
		t += pols.pop().print();
	}
	return t;
}