#include <iostream>
#include <cstdio>
#include <VECtor>
#include <queue>
#define INF 1000000
using namespace std;
int N,K,P;
vector<int> VEC[100001];
int NUM[500000];
int VI[100001];
bool INQ[100001];
struct Sj
{
	int num, time;
	Sj(){}
	Sj(int n,int t):num(n),time(t){}
	bool operator()(Sj S,Sj J){return S.time<J.time;}
};
priority_queue<Sj,vector<Sj>,Sj>PRI;
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d%d%d",&N,&K,&P);
	for(int i=1;i<=N;i++)
	{
		VEC[i].clear();
		VI[i]=0;
		INQ[i]=false;
	}
	for(int i=0;i<P;i++)
	{
		scanf("%d",&NUM[i]);
		VEC[NUM[i]].push_back(i);
	}
	int cnt=0;
	int ans=0;
	for(int i=0;i<P;i++)
	{
		if(!INQ[NUM[i]])
		{
			if(cnt<K)cnt++;
			else
			{
				ans++;
				Sj t=PRI.top();PRI.pop();
				INQ[t.num]=false;
			}
			INQ[NUM[i]]=true;
		}
		VI[NUM[i]]++;
		if(VI[NUM[i]]>=VEC[NUM[i]].size())PRI.push(Sj(NUM[i],INF));
		else PRI.push(Sj(NUM[i],VEC[NUM[i]][VI[NUM[i]]]));
	}
	printf("%d\n", ans);
}
