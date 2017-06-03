#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
#include<map>
#include<set>
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
set<LL>DISAPPEAR,VIS;
bool Solve()
{
	queue<LL>q;
	q.push(START);
	while(!q.empty())
	{
		const LL u=q.front();q.pop();
		if(VIS.find(u)!=VIS.end())continue;
		if(u==END)return true;
		VIS.insert(u);
		if(true)
		{
			const LL dif=u^END;
			q.push(u^(dif&(-dif)));
		}
		for(int i=0;i<N;i++)
		{
			const LL nxt=u^(1LL<<i);
			if(DISAPPEAR.find(nxt)!=DISAPPEAR.end())
			{
				for(int j=0;j<N;j++)if(j!=i)
				{
					if(DISAPPEAR.find(u^(1LL<<j))==DISAPPEAR.end())q.push(nxt^(1LL<<j));
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
		START=ReadBinaryLL(),END=ReadBinaryLL();
		VIS.clear();
		for(int i=0;i<K;i++)
		{
			const LL v=ReadBinaryLL();
			VIS.insert(v),DISAPPEAR.insert(v);
		}
		puts(Solve()?"TAK":"NIE");
	}
	return 0;
}
