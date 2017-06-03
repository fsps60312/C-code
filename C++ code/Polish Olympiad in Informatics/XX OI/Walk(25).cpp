#include<cstdio>
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
int BCNT[1<<16];
int CntBits(const LL v){return BCNT[v>>48]+BCNT[(v>>32)&0x000000000000ffffLL]+BCNT[(v>>16)&0x000000000000ffffLL]+BCNT[v&0x000000000000ffffLL];}
const LL MOD1=(1<<22)-11603;
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
			for(int i=0;i<MOD1;++i)HEAD[i]=-1;
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
			int cur=HEAD[v%MOD1];
			for(;cur!=-1;cur=NEXT[cur])if(KEY[cur]==v){VALUE[cur]=val;return true;}
			KEY.push_back(v),VALUE.push_back(val),NEXT.push_back(HEAD[v%MOD1]);
			HEAD[v%MOD1]=NSZ++;
			return false;
		}
	};
	Hasher<bool>VIS;
	Hasher<vector<LL>*>DISAPPEAR;
	bool Run()
	{
		START^=END;
		VIS.Clear(),DISAPPEAR.Clear();
		for(int i=0;i<K;i++)
		{
			const LL v=(ReadBinaryLL()^END);
			vector<LL>*s=new vector<LL>();s->push_back(-1LL);
			VIS.Set(v,true),DISAPPEAR.Set(v,s);
		}
		LL now=START;
		for(;;)
		{
			if(!now)return true;
			const LL greedy=now^(now&(-now));
			if(!DISAPPEAR.Get(greedy)){now=greedy;continue;}
			if(VIS.Set(now,true))return false;
			queue<LL>q;q.push(now);
			while(!q.empty())
			{
				const LL u=q.front();q.pop();
				if(!u)return true;
				if(CntBits(u)<CntBits(now))now=u;
				for(int i=0;i<N;i++)
				{
					const LL nxt=u^(1LL<<i);
					vector<LL>*et=DISAPPEAR.Get(nxt);
					if(et)
					{
						if(!et->empty()&&et->front()==-1LL)
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
									if(!VIS.Set(k,true))q.push(k);
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
		}
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
	for(int i=0;i<(1<<16);++i)
	{
		int &v=BCNT[i]=0;
		for(int j=0;j<16;++j)if(i&(1<<j))v++;
	}
//	for(int i=0;i<100;i++)printf("C[%d]=%d\n",i,CntBits(i));
//	freopen("inn.txt","r",stdin);
//	freopen("spa8d.in","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
//		printf("N=%d,K=%d\n",N,K);
		START=ReadBinaryLL(),END=ReadBinaryLL();
		puts((N<=22?Solve():SOLVE2.Run())?"TAK":"NIE");
	}
	return 0;
}


