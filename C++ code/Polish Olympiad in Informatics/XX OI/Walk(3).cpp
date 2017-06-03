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
	return s[a]==a?a:(s[a]=Find(s,s[a]));
}
int N,K,START,END;
set<LL>DISAPPEAR;
map<LL,LL>DJ,BLOCK;
bool Solve()
{
	const LL dif=START^END;
	LL now=START;
	vector<LL>path;path.push_back(now);
	for(int i=0;i<N;i++)if(dif&(1LL<<i))path.push_back(now^=(1LL<<i));
	LL dj0=-1LL,bl0=-1LL,dj1=-1LL,bl1=-1LL;
	for(int i=0;i<(int)path.size();i++)if(DJ.count(path[i]))
	{
		dj0=Find(DJ,path[i]);
		bl0=Find(BLOCK,path[i]);
		break;
	}
	if(dj0==-1LL)return true;
	for(int i=(int)path.size()-1;i>=0;i--)if(DJ.count(path[i]))
	{
		dj1=Find(DJ,path[i]);
		bl1=Find(BLOCK,path[i]);
		break;
	}
	if(dj0==dj1)return true;
	if(bl0!=bl1)return true;
	return false;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		START=ReadBinaryLL(),END=ReadBinaryLL();
		DISAPPEAR.clear(),DJ.clear(),BLOCK.clear();
		for(int i=0;i<K;i++)DISAPPEAR.insert(ReadBinaryLL());
		for(set<LL>::iterator it=DISAPPEAR.begin();it!=DISAPPEAR.end();it++)
		{
			BLOCK[*it]=*it;
			vector<LL>nxt;
			for(int d=0;d<N;d++)
			{
				const LL u=(*it)^(1LL<<d);
				if(!DISAPPEAR.count(u))
				{
					nxt.push_back(u);
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
