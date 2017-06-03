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
	for(int i=0;s[i];i++)assert('0'<=s[i]&&s[i]<='1'),ans=(ans<<1)+(s[i]-'0');
	return ans;
}
const LL MOD1=(1<<22)+1;
int N,K;
LL START,END;
struct Solver2
{
	template<class T>struct Hasher
	{
		int HEAD[MOD1];
		vector<LL>KEY;
		vector<T>VALUE;
		vector<int>NEXT;
		int NSZ;
		void Clear()
		{
			for(int i=0;i<MOD1;i++)HEAD[i]=-1;
			NSZ=0;
			KEY.clear(),VALUE.clear(),NEXT.clear();
		}
		inline T Get(const LL v)const
		{
			int cur=HEAD[v%MOD1];
			for(;cur!=-1;cur=NEXT[cur])if(KEY[cur]==v)return VALUE[cur];
			return NULL;
		}
		inline void Set(const LL v,const T &val)
		{
			int cur=HEAD[v%MOD1];
			for(;cur!=-1;cur=NEXT[cur])if(KEY[cur]==v){VALUE[cur]=val;return;}
			KEY.push_back(v),VALUE.push_back(val),NEXT.push_back(HEAD[v%MOD1]);
			HEAD[v%MOD1]=NSZ++;
		}
	};
	Hasher<bool>VIS;
	Hasher<vector<LL>*>DISAPPEAR;
	bool Run()
	{
		VIS.Clear(),DISAPPEAR.Clear();
		for(int i=0;i<K;i++)
		{
			const LL v=ReadBinaryLL();
			vector<LL>*s=new vector<LL>();s->push_back(-1);
			VIS.Set(v,true),DISAPPEAR.Set(v,s);
		}
		queue<LL>q;
		q.push(START);
		while(!q.empty())
		{
			const LL u=q.front();q.pop();
			if(VIS.Get(u))continue;
			if(u==END)return true;
			VIS.Set(u,true);
			if(true)
			{
				const LL dif=u^END;
				q.push(u^(dif&(-dif)));
			}
			for(int i=0;i<N;i++)
			{
				const LL nxt=u^(1LL<<i);
				vector<LL>*et=DISAPPEAR.Get(nxt);
				if(et)
				{
					if(!et->empty()&&et->front()==-1)
					{
						et->clear();
						for(int j=0;j<N;j++)et->push_back(nxt^(1LL<<j));
					}
					int sz=et->size();
					for(int j=0;j<sz;j++)if((*et)[j]!=u)
					{
						LL &k=(*et)[j];
						if(!DISAPPEAR.Get(u^(nxt^k)))
						{
							q.push(k);
							k=et->back();
							et->pop_back();
							j--,sz--;
						}
					}
				}
			}
		}
		return false;
	}
}SOLVE2;
bool VIS[1<<22],DISAPPEAR[1<<22];
bool Solve()
{
	for(int i=0;i<(1<<N);i++)VIS[i]=DISAPPEAR[i]=false;
	for(int i=0;i<K;i++)
	{
		const LL v=ReadBinaryLL();
		VIS[v]=DISAPPEAR[v]=true;
	}
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
//	freopen("spa7a.in","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
//		printf("N=%d,K=%d\n",N,K);
		START=ReadBinaryLL(),END=ReadBinaryLL();
		puts((N<=22?Solve():SOLVE2.Run())?"TAK":"NIE");
	}
	return 0;
}
