//#define SELF
#ifndef SELF
#include "cliclib.h"
#endif 
#include<cstdio>
#include<cassert>
#include<map>
using namespace std;
#ifdef SELF
int inicjuj(){return 15;}
void alojzy(const int x){if(x)return;}
int bajtazar(){return 1;}
#endif
int N;
map<pair<int,int>,bool>WIN;
pair<int,int>Pass(const pair<int,int>&p){return make_pair(1,p.first+p.second);}
pair<int,int>Double(const pair<int,int>&p){return make_pair(p.first*2,p.second);}
pair<int,int>Triple(const pair<int,int>&p){return make_pair(p.first*3,p.second);}
bool Win(const pair<int,int>&p)
{
	if(p.second>=N)return true;
	{const map<pair<int,int>,bool>::iterator it=WIN.find(p);if(it!=WIN.end())return it->second;}
	if(!Win(Pass(p)))return WIN[p]=true;
	if(p.first+p.second<N)
	{
		if(!Win(Double(p)))return WIN[p]=true;
		if(!Win(Triple(p)))return WIN[p]=true;
	}
	return WIN[p]=false;
}
int main()
{
	N=inicjuj();
	pair<int,int>p=make_pair(1,0);
	for(;;)
	{
			 if(!Win(Pass(p)))alojzy(1),p=Pass(p);
		else if(!Win(Double(p)))alojzy(2),p=Double(p);
		else if(!Win(Triple(p)))alojzy(3),p=Triple(p);
		else assert(0);
		const int move=bajtazar();
			 if(move==1)p=Pass(p);
		else if(move==2)p=Double(p);
		else if(move==3)p=Triple(p);
		else assert(0);
	}
	return 0;
}
