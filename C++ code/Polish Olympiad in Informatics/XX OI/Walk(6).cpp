#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
using namespace std;
typedef long long LL;
LL ReadBinaryLL()
{
	static char s[100];
	scanf("%s",s);
	LL ans=0LL;
	for(int i=0;s[i];i++)ans=(ans<<1)+(s[i]-'0');
	return ans;
}
int N,K,START,END;
//set<LL>DISAPPEAR,VIS;
bool DISAPPEAR[1<<25],VIS[1<<25];
bool Solve()
{
	queue<LL>q;
	q.push(START);
	while(!q.empty())
	{
		const LL u=q.front();q.pop();
		if(VIS[u])continue;
		if(u==END)return true;
		VIS[u]=true;
		if(true)
		{
			const LL dif=u^END;
			q.push(u^(dif&(-dif)));
		}
		for(int i=0;i<N;i++)
		{
			const LL nxt=u^(1LL<<i);
			if(DISAPPEAR[nxt])
			{
				for(int j=0;j<N;j++)if(j!=i)
				{
					if(!DISAPPEAR[u^(1LL<<j)])q.push(nxt^(1LL<<j));
				}
			}
		}
	}
	return false;
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("spa0a.in","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		assert(N<=25);
		START=ReadBinaryLL(),END=ReadBinaryLL();
		for(LL i=0;i<(1LL<<N);i++)VIS[i]=DISAPPEAR[i]=false;
//		VIS.clear(),DISAPPEAR.clear();
		for(int i=0;i<K;i++)
		{
			const LL v=ReadBinaryLL();
			VIS[v]=DISAPPEAR[v]=true;
		}
		puts(Solve()?"TAK":"NIE");
	}
	return 0;
}
