#include<cstdio>
#include<vector>
#include<queue>
#include<set>
#include<algorithm>
#include<cassert>
using namespace std;
int N,K;
vector<int>T;
vector<int>F[50];
set<int>FS[50];
void GetNumbers(vector<int>&ans)
{
	ans.clear();
	static char s[1000];
	gets(s);
	int idx=0;
	for(;;)
	{
		for(;s[idx]&&(s[idx]<'0'||s[idx]>'9');idx++);
		if(!s[idx])break;
		int v=0;
		for(;s[idx]>='0'&&s[idx]<='9';idx++)v=v*10+s[idx]-'0';
		ans.push_back(v);
	}
}
struct Pq
{
	int f,cost;
	Pq(){}
	Pq(int f,int cost):f(f),cost(cost){}
	bool operator<(const Pq &p)const{return cost>p.cost;}
};
bool VIS[100];
int Solve()
{
	if(K==0)return 0;
	for(int i=0;i<100;i++)VIS[i]=false;
	priority_queue<Pq>pq;
	pq.push(Pq(0,-5));
	while(!pq.empty())
	{
		Pq p=pq.top();pq.pop();
		if(VIS[p.f])continue;
		VIS[p.f]=true;
		if(p.f==K)return p.cost;
		for(int i=0;i<N;i++)
		{
			if(FS[i].find(p.f)==FS[i].end())continue;
			int sz=F[i].size();
			int cost=p.cost+5;
			cost+=max(p.f-F[i][0],F[i][sz-1]-p.f)*T[i];
			for(int j=0;j<F[i].size();j++)
			{
				int &k=F[i][j];
				if(k==p.f)continue;
				pq.push(Pq(k,cost+abs(k-p.f)*T[i]));
			}
		}
	}
	return -1;
}
int main()
{
//	freopen("in.txt","r",stdin);
	static char input[1000];
	while(gets(input))
	{
		sscanf(input,"%d%d",&N,&K);
		if(!(N||K))break;
		GetNumbers(T);
		assert(T.size()==N);
		for(int i=0;i<N;i++)
		{
			GetNumbers(F[i]);
			sort(F[i].begin(),F[i].end());
			FS[i].clear();
			for(int j=0;j<F[i].size();j++)FS[i].insert(F[i][j]);
		}
		int ans=Solve();
		if(ans==-1)puts("IMPOSSIBLE");
		else printf("%d\n",ans);
	}
	return 0;
}
