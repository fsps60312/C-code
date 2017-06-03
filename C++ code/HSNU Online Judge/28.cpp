#include<bits/stdc++.h>
using namespace std;
int N,K,P,D[500000],INQ[100001];
queue<int>Q[100001];
struct Pq
{
	int d,nxt;
	Pq(){}
	Pq(int d,int n):d(d),nxt(n){}
	bool operator<(const Pq &p)const{return nxt>p.nxt;}
};
priority_queue<Pq>PQ;
int ANS;
void Push(const int &d)
{
	while(SZ==K)
	{
		int td=PQ.top().d;PQ.pop();
		INQ[td]--;
		if(!INQ[td])ANS++,SZ--;
	}
	Q[d].pop();
	if(!INQ[d]++)SZ++;
	PQ.push(Pq(d,Q[d].size()?Q[d].front():500001));
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d%d%d",&N,&K,&P);
	for(int i=1;i<=N;i++)INQ[i]=0;
	for(int i=0;i<P;i++)
	{
		int &d=D[i];
		scanf("%d",&d);
		Q[d].push(i);
	}
	ANS=0;
	for(int i=0;i<P;i++)
	{
		int &d=D[i];
		Push(d);
	}
	printf("%d\n",ANS);
	return 0;
}
