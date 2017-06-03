#include<cstdio>
#include<vector>
#include<queue>
#include<set>
#include<algorithm>
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
//	for(int i=0;i<ans.size();i++)printf(" %d",ans[i]);puts("");
}
struct Pq
{
	int f,cost,pre;
	Pq(){}
	Pq(int f,int cost,int pre):f(f),cost(cost),pre(pre){}
	bool operator<(const Pq &p)const{return cost>p.cost;}
};
int CNT[100];
int Solve()
{
	for(int i=0;i<100;i++)CNT[i]=0;
	priority_queue<Pq>pq;
	pq.push(Pq(0,-5,-1));
	while(!pq.empty())
	{
		Pq p=pq.top();pq.pop();
		if(CNT[p.f]>=100)continue;
		CNT[p.f]++;
//		printf("%d->%d:%d\n",p.pre,p.f,p.cost);
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
				pq.push(Pq(k,cost+abs(k-p.f)*T[i],p.f));
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
