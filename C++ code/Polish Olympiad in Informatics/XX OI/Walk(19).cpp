#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
#include<utility>
#include<algorithm>
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
const LL MOD1=(1<<22)-11603,MOD2=MOD1+2;
int N,K;
LL START,END;
struct Solver2
{
	template<class T>struct Hasher
	{
		vector<pair<LL,T> >A[MOD1];
		void Clear()
		{
			for(int i=0;i<MOD1;i++)A[i].clear();
		}
		inline T Get(const LL v)const
		{
			const vector<pair<LL,T> >&s=A[v%MOD1];
			int l=0,r=(int)s.size()-1;
			while(l<r)
			{
				const int mid=(l+r)/2;
				if(s[mid].first<v)l=mid+1;
				else r=mid;
			}
			return r!=-1&&s[r].first==v?s[r].second:NULL;
		}
		inline void Set(const LL v,const T val)
		{
			vector<pair<LL,T> >&s=A[v%MOD1];
			int l=0,r=(int)s.size()-1;
			while(l<r)
			{
				const int mid=(l+r)/2;
				if(s[mid].first<v)l=mid+1;
				else r=mid;
			}
			if(r==-1||s[r].first!=v)
			{
				s.push_back(make_pair(v,val));
				for(int i=(int)s.size()-1;i>=1&&s[i-1].first>s[i].first;--i)swap(s[i-1],s[i]);
			}
			else s[r].second=val;
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
			if(u==END)return true;
			VIS.Set(u,true);
			if(true)
			{
				const LL dif=u^END,p=u^(dif&(-dif));
				if(!VIS.Get(p))q.push(p);
			}
			for(int i=0;i<N;i++)
			{
				const LL nxt=u^(1LL<<i);
				vector<LL>*et=DISAPPEAR.Get(nxt);
				if(et)
				{
					if(et->front()==-1)
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
							if(!VIS.Get(k))q.push(k);
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
//	freopen("inn.txt","r",stdin);
//	freopen("spa3c.in","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
//		printf("N=%d,K=%d\n",N,K);
		START=ReadBinaryLL(),END=ReadBinaryLL();
		puts((N<=22?Solve():SOLVE2.Run())?"TAK":"NIE");
	}
	return 0;
}


