#include "dna.h"

#include <cstdlib>
#include<cassert>
#include<string>
using namespace std;
unsigned int Rand()
{
	static unsigned int seed=0x20160722;
	seed*=0xdefaced,seed+=0x165805;
	return seed+=seed>>20;
}
void Flip(char &c)
{
	if(c=='0')c='1';
	else if(c=='1')c='0';
	else assert(0);
}
void GoRight(string &s,int wrong_try)
{
	if(wrong_try==10)
	{
		if(make_test(s))wrong_try=0;
		else
		{
			s.pop_back();
			while(!s.empty()&&!make_test(s))s.pop_back();
			return;
		}
	}
	if(Rand()&1)
	{
		if(make_test(s+"0"))s.push_back('0'),GoRight(s,0);
		else s.push_back('1'),GoRight(s,wrong_try+1);
	}
	else
	{
		if(make_test(s+"1"))s.push_back('1'),GoRight(s,0);
		else s.push_back('0'),GoRight(s,wrong_try+1);
	}
}
string GoLeft(const string &s,const int n)
{
	if((int)s.size()==n)return s;
	if(make_test("0"+s))return GoLeft("0"+s,n);
	else return GoLeft("1"+s,n);
}
std::string analyse(int n, int t) {
	string ans="";
	GoRight(ans,0);
    return GoLeft(ans,n);
}                       
