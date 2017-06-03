#include<cstdio>
#include<cassert>
#include<set>
#include<hash_set>
#include<queue>
using namespace std;
using namespace __gnu_cxx;
typedef long long LL;
namespace __gnu_cxx
{
	template<> struct hash<LL>
    {
        size_t operator()(const LL& x)const
        {
            return hash<LL>()(x);
        }
    };
}
void GetBitLL(LL &v)
{
	v=0;
	int c=getchar();
	while(c<'0'||c>'1')c=getchar();
	while(c>='0'&&c<='1')v=v*2LL+(c-'0'),c=getchar();
}
int N,K;
LL START,END;
set<LL>BANNED;
bool Solve(const LL &start,const LL &end)
{
	set<LL>vis;
	queue<LL>q;q.push(start);
	for(int cnt=0;!q.empty()&&cnt<K*10;cnt++)
	{
		const LL u=q.front();q.pop();
		if(u==end)return true;
		for(int i=0;i<N;i++)
		{
			const LL &nxt=u^(1LL<<i);
			if(vis.find(nxt)==vis.end()&&BANNED.find(nxt)==BANNED.end())
			{
				q.push(nxt),vis.insert(nxt);
			}
		}
	}
	return !q.empty();
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		GetBitLL(START),GetBitLL(END);
		BANNED.clear();
		for(int i=0;i<K;i++)
		{
			LL v;GetBitLL(v);
			BANNED.insert(v);
		}
		puts(Solve(START,END)||Solve(END,START)?"TAK":"NIE");
	}
	return 0;
}
