#include<cstdio>
#include<cassert>
#include<vector>
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
LL Find(map<LL,LL>&s,const LL a)
{
	if(!s.count(a))return -1LL;
	assert(s.count(a));
	return s[a]==a?a:(s[a]=Find(s,s[a]));
}
int N,K,START,END;
set<LL>DISAPPEAR;
map<LL,LL>DJ,BLOCK;
bool Solve()
{
	const LL dif=START^END;
	LL now=START;
	vector<LL>path;
	if(BLOCK.count(now))path.push_back(now);
	for(int i=0;i<N;i++)if(dif&(1LL<<i))
	{
		now^=(1LL<<i);
		if(BLOCK.count(now))path.push_back(now);
	}
	assert(now==END);
	if((int)path.size()<=1)return true;
	for(int i=1;i<(int)path.size();i++)if(DJ.count(path[i-1])&&DJ.count(path[i]))DJ[Find(DJ,path[i-1])]=Find(DJ,path[i]);
//	for(int i=0;i<(int)path.size();i++)printf(" (%lld,%lld)(%d)",Find(BLOCK,path[i]),Find(DJ,path[i]),DJ.count(path[i]));puts("");
	return Find(DJ,path.front())==Find(DJ,path.back());
}
int main()
{
//	freopen("in.txt","r",stdin);
	freopen("spa1d.in","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		START=ReadBinaryLL(),END=ReadBinaryLL();
		DISAPPEAR.clear(),DJ.clear(),BLOCK.clear();
		for(int i=0;i<K;i++)
		{
			const LL v=ReadBinaryLL();
			DISAPPEAR.insert(v);
			BLOCK[v]=v;
		}
		for(set<LL>::const_iterator it=DISAPPEAR.begin();it!=DISAPPEAR.end();it++)
		{
			vector<LL>nxt;
			for(int d=0;d<N;d++)
			{
				const LL u=(*it)^(1LL<<d);
				if(!DISAPPEAR.count(u))
				{
					nxt.push_back(d);
					if(!DJ.count(u))DJ[u]=u,BLOCK[u]=(*it);
					else BLOCK[Find(BLOCK,u)]=Find(BLOCK,*it);
				}
			}
			for(int a=0;a<(int)nxt.size();a++)for(int b=a+1;b<(int)nxt.size();b++)
			{
				if(!DISAPPEAR.count((*it)^(1LL<<nxt[a])^(1LL<<nxt[b])))
				{
					DJ[Find(DJ,(*it)^(1LL<<nxt[a]))]=Find(DJ,(*it)^(1LL<<nxt[b]));
				}
			}
		}
		puts(Solve()?"TAK":"NIE");
	}
	return 0;
}
