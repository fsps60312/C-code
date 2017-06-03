#include<cstdio>
#include<cassert>
#include<queue>
using namespace std;
typedef long long LL;
LL ReadBinaryLL()
{
	static char s[100];
	scanf("%s",s);
	LL ans=0LL;
	for(int i=0;s[i];++i)assert('0'<=s[i]&&s[i]<='1'),ans=(ans<<1)+(s[i]-'0');
	return ans;
}
const LL MOD1=(1<<21)+1;
const int QSZ=5208695;
int N,K;
LL START,END;
//int DEB_MAX=0;
struct Solver2
{
	template<class T>struct Hasher
	{
		int HEAD[MOD1];
		LL *KEY;
		T *VALUE;
		int *NEXT;
		int NSZ;
		Hasher(const int sz):KEY(new LL[sz]),VALUE(new T[sz]),NEXT(new int[sz]){}
		void Clear()
		{
			for(int i=0;i<MOD1;++i)HEAD[i]=-1;
			NSZ=0;
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
			KEY[NSZ]=v,VALUE[NSZ]=val,NEXT[NSZ]=HEAD[v%MOD1];
			HEAD[v%MOD1]=NSZ++;
//			if(NSZ>DEB_MAX)DEB_MAX=NSZ;
		}
	};
	Hasher<bool>VIS;
	Hasher<int>DISAPPEAR;
	Solver2():VIS(Hasher<bool>(12307412)),DISAPPEAR(Hasher<int>(1000000)){}
	int SZ[1000001];
	int HEAD[1000001];
	LL VAL[1000001*5];
	bool Run()
	{
		VIS.Clear(),DISAPPEAR.Clear();
		for(int i=1;i<=K;++i)
		{
			const LL v=ReadBinaryLL();
			HEAD[i]=N*i;
			SZ[i]=1;
			VAL[N*i]=-1LL;
			VIS.Set(v,true),DISAPPEAR.Set(v,i);
		}
		static LL q[QSZ];int l=1,r=0;
		q[++r]=START;
		while(l<=r||r<l-1)
		{
			const LL u=q[l++];if(l==QSZ)l=0;
			if(VIS.Get(u))continue;
			if(u==END)return true;
			VIS.Set(u,true);
			if(true)
			{
				const LL dif=u^END;
				if(++r==QSZ)r=0;
				q[r]=u^(dif&(-dif));
			}
			for(int i=0;i<N;++i)
			{
				const LL nxt=u^(1LL<<i);
				const int hid=DISAPPEAR.Get(nxt);
				if(hid)
				{
					int &sz=SZ[hid];
					LL *head=VAL+HEAD[hid];
					if(sz==1&&*head==-1LL)
					{
						*head=nxt^1LL;
						for(int j=1;j<N;++j)
						{
							head[j]=nxt^(1LL<<j);
						}
						sz=N;
					}
					for(int j=0;j<sz;++j)
					{
						if(head[j]!=u)
						{
							LL &k=head[j];
							if(!DISAPPEAR.Get(u^(nxt^k)))
							{
								if(++r==QSZ)r=0;
								q[r]=k;
								head[j--]=head[--sz];
							}
						}
						else head[j--]=head[--sz];
					}
				}
			}
		}
		return false;
	}
}SOLVE2;
bool *VIS=SOLVE2.VIS.VALUE,*DISAPPEAR=VIS+(1<<22);
bool Solve()
{
	for(int i=0;i<(1<<N);++i)VIS[i]=DISAPPEAR[i]=false;
	for(int i=0;i<K;++i)
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
		for(int i=0;i<N;++i)
		{
			const LL nxt=u^(1LL<<i);
			if(DISAPPEAR[nxt])
			{
				for(int j=0;j<N;++j)if(j!=i)
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
//	freopen("inn.txt","r",stdin);
//	freopen("spa7a.in","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
//		printf("N=%d,K=%d\n",N,K);
		START=ReadBinaryLL(),END=ReadBinaryLL();
		puts((N<=22?Solve():SOLVE2.Run())?"TAK":"NIE");
//		printf("DEB_MAX=%d\n",DEB_MAX);
	}
	return 0;
}
