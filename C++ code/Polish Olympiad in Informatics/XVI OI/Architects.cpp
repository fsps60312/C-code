#define SELF
#include<cstdio>
#include<cassert>
#include<vector>
#ifndef SELF
#include"carclib.h"
#endif
using namespace std;
struct Deq
{
	int S[15000000],L,R;
	void Clear(){L=0,R=-1;}
	void PushBack(const int v){S[++R]=v;}
	void PopBack(){--R;}
	void PopFront(){++L;}
	int Front()const{return S[L];}
	int Back()const{return S[R];}
	int Size()const{return R-L+1;}
	bool Empty()const{return R<L;}
}DEQ;
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
int main()
{
	freopen("in.txt","r",stdin);
	const int K=inicjuj();
	vector<int>S;
	for(int v;(v=wczytaj());)S.push_back(v);
	DEQ.Clear();
	for(int i=K,cur=0;i>=1;i--)
	{
		while(cur<=)
	}
	return 0;
}
