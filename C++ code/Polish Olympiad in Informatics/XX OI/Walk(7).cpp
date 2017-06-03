#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
using namespace std;
typedef long long LL;
const LL MOD1=17483647,MOD2=MOD1+2;
struct Hasher
{
	bool S1[MOD1],S2[MOD2];
	void Clear()
	{
		for(int i=0;i<MOD1;i++)S1[i]=false;
		for(int i=0;i<MOD2;i++)S2[i]=false;
	}
	bool Get(const LL v)const{return S1[v%MOD1]&&S2[v%MOD2];}
	void Set(const LL v){S1[v%MOD1]=S2[v%MOD2]=true;}
}DISAPPEAR,VIS;
LL ReadBinaryLL()
{
	static char s[100];
	scanf("%s",s);
	LL ans=0LL;
	for(int i=0;s[i];i++)ans=(ans<<1)+(s[i]-'0');
	return ans;
}
int N,K,START,END;
bool Solve()
{
	queue<LL>q;
	q.push(START);
	while(!q.empty())
	{
		const LL u=q.front();q.pop();
		if(VIS.Get(u))continue;
		if(u==END)return true;
		VIS.Set(u);
		if(true)
		{
			const LL dif=u^END;
			q.push(u^(dif&(-dif)));
		}
		for(int i=0;i<N;i++)
		{
			const LL nxt=u^(1LL<<i);
			if(DISAPPEAR.Get(nxt))
			{
				for(int j=0;j<N;j++)if(j!=i)
				{
					if(!DISAPPEAR.Get(u^(1LL<<j)))q.push(nxt^(1LL<<j));
				}
			}
		}
	}
	return false;
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("spa2b.in","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		START=ReadBinaryLL(),END=ReadBinaryLL();
		VIS.Clear(),DISAPPEAR.Clear();
		for(int i=0;i<K;i++)
		{
			const LL v=ReadBinaryLL();
			VIS.Set(v),DISAPPEAR.Set(v);
		}
		puts(Solve()?"TAK":"NIE");
	}
	return 0;
}
