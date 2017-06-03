//#define SELF
#include<cstdio>
#include<cassert>
#include<vector>
#include<set>
#include<queue>
#ifndef SELF
#include"carclib.h"
#endif
using namespace std;
#ifdef SELF
int inicjuj(){return 3;}
int wczytaj()
{
	static int ans[]={12,5,8,3,15,8,0},kase=0;
	return ans[kase++];
}
void wypisz(int ans)
{
	printf("ans=%d\n",ans);
}
#endif
int GetNext(const int K,int &remain)
{
	static int last_val=2147483647;
	static queue<int>q;
	while(last_val&&(int)q.size()<K)
	{
		last_val=wczytaj();
		if(last_val)q.push(last_val);
	}
	if(q.empty())return 0;
	const int ans=q.front();q.pop();
	remain=(int)q.size();
	return ans;
}
int main()
{
	const int K=inicjuj();
	static int ANS[1000000],L=0,SZ=0;
	multiset<int>S;
	for(int v,remain;(v=GetNext(K,remain));)
	{
		if(L+1==K-1-remain)S.erase(S.find(ANS[L++]));
		while(!S.empty()&&*S.begin()<v)S.erase(S.find(ANS[--SZ]));
		if(SZ<K)S.insert(ANS[SZ++]=v);
	}
	assert(SZ==K);
	for(int i=0;i<K;i++)wypisz(ANS[i]);
	return 0;
}
