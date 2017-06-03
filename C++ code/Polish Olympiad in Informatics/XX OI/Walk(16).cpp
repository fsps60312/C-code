#include<cstdio>
#include<cassert>
#include<queue>
using namespace std;
typedef long long LL;
inline char ReadChar()
{
//	return getchar();
	static char buf[1<<16],*cur=buf,*end=buf;
	if(cur==end)
	{
		if((end=buf+fread(buf,1,1<<20,stdin))==buf)return EOF;
		cur=buf;
	}
	return *cur++;
}
inline LL ReadBinaryLL()
{
	char c=ReadChar();
	while(c<'0'||'1'<c)c=ReadChar();
	LL ans=0LL;
	while('0'<=c&&c<='1')ans=(ans<<1)+(c-'0'),c=ReadChar();
	return ans;
}
const LL MOD1=(1<<21)+1;
const int QSZ=2753356;
int N,K;
bool ReadNK()
{
	char c=ReadChar();
	if(c==EOF)return false;
	while(c<'0'||'9'<c)
	{
		c=ReadChar();
		if(c==EOF)return false;
	}
	N=0;
	while('0'<=c&&c<='9')N=N*10+(c-'0'),c=ReadChar();
	while(c<'0'||'9'<c)
	{
		c=ReadChar();
		if(c==EOF)return false;
	}
	K=0;
	while('0'<=c&&c<='9')K=K*10+(c-'0'),c=ReadChar();
	return true;
}
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
		static LL q[QSZ];
		int l=1,r=0;
		q[++r]=START;
		while(l<=r||r!=l-1)
		{
			const LL u=q[l++];if(l==QSZ)l=0;
			if(u==END)return true;
			VIS.Set(u,true);
			if(true)
			{
				const LL dif=u^END,p=u^(dif&(-dif));
				if(!VIS.Get(p))
				{
					if(++r==QSZ)r=0;
					q[r]=p;
				}
//				if((int)q.size()>DEB_MAX)DEB_MAX=q.size();
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
								if(!VIS.Get(k))
								{
									if(++r==QSZ)r=0;
									q[r]=k;
								}
//								if((int)q.size()>DEB_MAX)DEB_MAX=q.size();
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
//	freopen("in.txt","r",stdin);
//	freopen("spa2e.in","r",stdin);
	while(ReadNK())
	{
//		printf("N=%d,K=%d\n",N,K);
		START=ReadBinaryLL(),END=ReadBinaryLL();
		puts((N<=22?Solve():SOLVE2.Run())?"TAK":"NIE");
//		printf("DEB_MAX=%d\n",DEB_MAX);
	}
	return 0;
}
