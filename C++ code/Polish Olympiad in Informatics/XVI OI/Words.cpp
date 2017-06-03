#include<cstdio>
#include<cassert>
#include<set>
using namespace std;
int N,S[100001],LEFT[100002],RIGT[100002];
struct Cmp{bool operator()(const int a,const int b)const{return S[a]!=S[b]?S[a]<S[b]:a>b;};};
int Solve()
{
	set<int,Cmp>p;
	for(int i=1;i<=N;i++)p.insert(i);
	while((int)p.size()>1)
	{
		const int loc=*p.begin();p.erase(p.begin());
		if(LEFT[loc]==0)
		{
			S[loc]+=2;
			p.insert(loc);
		}
		else if(S[LEFT[loc]]==S[loc]+1)
		{
			const int u=LEFT[loc];
			p.erase(u);
			++S[u];
			p.insert(u);
			LEFT[RIGT[loc]]=LEFT[loc];
			RIGT[LEFT[loc]]=RIGT[loc];
		}
		else if(RIGT[loc]==N+1&&S[loc]>0)
		{
			++S[loc];
			p.insert(loc);
		}
		else return -1;
	}
	return S[*p.begin()];
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		for(int i=1;i<=N;i++)scanf("%d",&S[i]);
		for(int i=0;i<=N;i++)LEFT[i+1]=i,RIGT[i]=i+1;
		const int ans=Solve();
		if(ans==-1)puts("NIE");
		else puts("TAK");//printf("%d\n",ans);
	}
	return 0;
}
