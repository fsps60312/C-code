//#define DEBUG
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
const LL MOD1=(1<<22)-11603;
int N,K;
LL START,END;
#ifdef DEBUG
int MX=0;
#endif
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
		inline bool Set(const LL v,const T val)
		{
			int cur=HEAD[v%MOD1]
			#ifdef DEBUG
			,cnt=0
			#endif
			;
			for(;cur!=-1;cur=NEXT[cur]
			#ifdef DEBUG
			,cnt++
			#endif
			)if(KEY[cur]==v){VALUE[cur]=val;return true;}
			KEY.push_back(v),VALUE.push_back(val),NEXT.push_back(HEAD[v%MOD1]);
			HEAD[v%MOD1]=NSZ++;
			#ifdef DEBUG
			if(cnt>MX)MX=cnt;
			#endif
			return false;
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
		deque<LL>q;
		q.push_back(START);
		while(!q.empty())
		{
			const LL u=q.front();q.pop_front();
			if(u==END)return true;
			if(true)
			{
				const LL dif=u^END,p=u^(dif&(-dif));
				if(!VIS.Set(p,true))q.push_front(p);
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
					for(int j=0;j<sz;j++)
					{
						LL &k=(*et)[j];
						if(k!=u)
						{
							if(!DISAPPEAR.Get(u^(nxt^k)))
							{
								if(!VIS.Set(k,true))q.push_back(k);
								k=et->back();
								et->pop_back();
								j--,sz--;
							}
						}
						else k=et->back(),et->pop_back(),j--,sz--;
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
		const int v=ReadBinaryLL();
		VIS[v]=DISAPPEAR[v]=true;
	}
	queue<int>q;
	q.push(START);
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		if(VIS[u])continue;
		if(u==END)return true;
		VIS[u]=true;
		if(true)
		{
			const int dif=u^END;
			q.push(u^(dif&(-dif)));
		}
		for(int i=0;i<N;i++)
		{
			const int nxt=u^(1<<i);
			if(DISAPPEAR[nxt])
			{
				for(int j=0;j<N;j++)if(j!=i)
				{
					if(!DISAPPEAR[u^(1<<j)])q.push(nxt^(1<<j));
				}
			}
		}
	}
	return false;
}
int main()
{
	#ifdef DEBUG
	freopen("inn.txt","r",stdin);
	#endif
	freopen("inn.txt","r",stdin);
//	freopen("spa3c.in","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
//		printf("N=%d,K=%d\n",N,K);
		START=ReadBinaryLL(),END=ReadBinaryLL();
		#ifdef DEBUG
		MX=0;
		#endif
		puts((N<=22?Solve():SOLVE2.Run())?"TAK":"NIE");
		#ifdef DEBUG
		printf("MX=%d\n",MX);
		#endif
	}
	return 0;
}


