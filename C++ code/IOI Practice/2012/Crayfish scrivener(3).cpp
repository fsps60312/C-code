#include"grader.h"
#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
unsigned int Rand()
{
	static unsigned int seed=0x20160721;
	seed*=0x163636;
	return seed+=seed>>20;
}
struct Node
{
	char C;
	int CH[2];
	unsigned int SZ;
}POOL[1000000*20];
int NEW=0;
int NewNode(const char _C)
{
	Node &o=POOL[NEW];
	o.C=_C;
	o.CH[0]=o.CH[1]=-1;
	o.SZ=1;
	return NEW++;
}
int Copy(const int o)
{
	const int ans=NewNode(POOL[o].C);
	for(int d=0;d<2;d++)POOL[ans].CH[d]=POOL[o].CH[d];
	POOL[ans].SZ=POOL[o].SZ;
	return ans;
}
unsigned int Sz(const int o){return o!=-1?POOL[o].SZ:0;}
void Maintain(const int o)
{
	POOL[o].SZ=Sz(POOL[o].CH[0])+1+Sz(POOL[o].CH[1]);
}
int Merge(const int a,const int b)
{
	if(a==-1||b==-1)return a!=-1?a:b;
	if(Rand()%(Sz(a)+Sz(b))<Sz(a))
	{
		const int o=Copy(a);
		POOL[o].CH[1]=Merge(POOL[o].CH[1],b);
		Maintain(o);
		return o;
	}
	else
	{
		const int o=Copy(b);
		POOL[o].CH[0]=Merge(a,POOL[o].CH[0]);
		Maintain(o);
		return o;
	}
}
char GetLetter(const int o,const unsigned int i)
{
	assert(i<Sz(o));
	if(i==Sz(POOL[o].CH[0]))return POOL[o].C;
	if(i<Sz(POOL[o].CH[0]))return GetLetter(POOL[o].CH[0],i);
	else return GetLetter(POOL[o].CH[1],i-Sz(POOL[o].CH[0])-1);
}
int N;
vector<int>S;
void Init()
{
	S.clear(),S.push_back(-1);
}
void TypeLetter(char L)
{
	const int o=Merge(S.back(),NewNode(L));
	S.push_back(o);
}
void UndoCommands(int U)
{
	const int o=S[S.size()-1-U];
	S.push_back(o);
}
char GetLetter(int P)
{
	return GetLetter(S.back(),P);
}
