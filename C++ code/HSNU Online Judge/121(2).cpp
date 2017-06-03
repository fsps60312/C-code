#include"interactive/121.h"
#include<cstdio>
#include<algorithm>
#include<cassert>
#include<map>
using namespace std;
//void Init(int &N,int &M,int x[])
//{
//	N=5,M=5;
//	int xx[]={2,4,1,3,3};
//	for(int i=1;i<=N;i++)x[i]=xx[i-1];
//}
//int getNumQuestions(){return 2;}
//void getQuestion(int &K,int &J)
//{
//	static int kase=0,k[]={3,5},j[]={4,5};
//	K=k[kase],J=j[kase];
//	kase++;
//}
//void answer(int x)
//{
//	static int kase=0,xx[]={1,4};
//	printf("Answer(%d)\n",x);
//	puts(xx[kase++]==x?"AC":"WA");
//}
//////////////////////////////////////////////////
int N,M,Q,K,J,X[300001];
map<int,int>BEAD[300000],LOC[300000];//column->bead,bead->column
int Query(map<int,int>&s,int version)
{
	auto it=s.upper_bound(version);
	it--;
	return it->second;
}
int main()
{
	Init(N,M,X);
	for(int i=0;i<N;i++)BEAD[i][0]=i,LOC[i][0]=i;
	for(int i=1;i<=M;i++)X[i]--;
	for(int i=1;i<=M;i++)
	{
		int b1=Query(BEAD[X[i]],i),b2=Query(BEAD[X[i]+1],i);
		BEAD[X[i]][i]=b2,BEAD[X[i]+1][i]=b1;
		LOC[b1][i]=X[i]+1,LOC[b2][i]=X[i];
	}
	Q=getNumQuestions();
	while(Q--)
	{
		getQuestion(K,J);
		K--;
		answer(Query(LOC[K],J)+1);
	}
	return 0;
}
