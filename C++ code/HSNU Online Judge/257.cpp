#include<cstdio>
#include<map>
#include<cassert>
#include"interactive/257.h"
using namespace std;
//int Init(){return 15;}
//void Alois(int v){static int cnt=0;if(cnt>100)exit(0);printf("cnt=%d\n",cnt++);}
//int Byteasar(){return 1;}
int N,POT,STK;
map<pair<int,int>,bool>DP;
bool Win(const int pot,const int stk)
{
	if(pot+stk>=N)return false;
	const auto s=make_pair(pot,stk);
	const auto it=DP.find(s);
	if(it!=DP.end())return it->second;
	if(Win(pot*2,stk)&&Win(pot*3,stk)&&Win(1,stk+pot))return DP[s]=false;
	return DP[s]=true;
}
int main()
{
	N=Init();
	POT=1,STK=0;
	DP.clear();
	for(;;)
	{
		if(!Win(POT*2,STK))Alois(2),POT*=2;
		else if(!Win(POT*3,STK))Alois(3),POT*=3;
		else if(!Win(1,STK+POT))Alois(1),STK+=POT,POT=1;
		else assert(0);
		const int result=Byteasar();
		if(result==2)POT*=2;
		else if(result==3)POT*=3;
		else if(result==1)STK+=POT,POT=1;
		else assert(0);
	}
	return 0;
}
