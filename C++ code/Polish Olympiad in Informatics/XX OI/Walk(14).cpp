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
	for(int i=0;s[i];i++)assert('0'<=s[i]&&s[i]<='1'),ans=(ans<<1)+(s[i]-'0');
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
			for(int i=0;i<MOD1;i++)HEAD[i]=-1;
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
	int HEAD[1000001],NEXT[4701060],NSZ;
	LL VAL[4701060];
	bool Run()
	{
		NSZ=0;
		VIS.Clear(),DISAPPEAR.Clear();
		for(int i=1;i<=K;i++)
		{
			const LL v=ReadBinaryLL();
			NEXT[NSZ]=-1;
			VAL[NSZ]=-1LL;
			HEAD[i]=NSZ++;
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
			for(int i=0;i<N;i++)
			{
				const LL nxt=u^(1LL<<i);
				const int hid=DISAPPEAR.Get(nxt);
				if(hid)
				{
					if(HEAD[hid]!=-1&&VAL[HEAD[hid]]==-1LL)
					{
						VAL[HEAD[hid]]=nxt^1LL;
						for(int j=1;j<N;j++)
						{
							NEXT[NSZ]=HEAD[hid];
							VAL[NSZ]=nxt^(1LL<<j);
							HEAD[hid]=NSZ++;
						}
					}
					for(int cur=HEAD[hid],*pre=&HEAD[hid];cur!=-1;pre=&NEXT[cur],cur=NEXT[cur])if(VAL[cur]!=u)
					{
						LL &k=VAL[cur];
						if(!DISAPPEAR.Get(u^(nxt^k)))
						{
							if(++r==QSZ)r=0;
							q[r]=k;
							*pre=NEXT[cur];
						}
					}
					else *pre=NEXT[cur];
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
