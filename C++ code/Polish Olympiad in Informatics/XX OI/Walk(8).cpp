#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
using namespace std;
typedef long long LL;
//const LL MOD1=17483647,MOD2=MOD1+2;
LL MOD1;
template<class T>struct Hasher
{
	T S1[MOD1];//,S2[MOD2];
	void Clear(const T &val)
	{
		for(int i=0;i<MOD1;i++)S1[i]=val;
//		for(int i=0;i<MOD2;i++)S2[i]=val;
	}
	inline T Get(const LL v)const{return S1[v%MOD1];}
//	T Get(const LL v)const{const T &val=S1[v%MOD1];return val==S2[v%MOD2]?val:T();}
	inline void Set(const LL v,const T &val){S1[v%MOD1]=val;}//S2[v%MOD2]=val;}
};
LL ReadBinaryLL()
{
	static char s[100];
	scanf("%s",s);
	LL ans=0LL;
	for(int i=0;s[i];i++)assert('0'<=s[i]&&s[i]<='1'),ans=(ans<<1)+(s[i]-'0');
	return ans;
}
Hasher<bool>VIS;
Hasher<vector<LL>*>DISAPPEAR;
int N,K;
LL START,END;
bool Solve()
{
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
						q.push(k);
						swap(k,et->back());
						et->pop_back();
						j--,sz--;
					}
				}
			}
		}
	}
	return false;
}
int main()
{
//	freopen("in.txt","r",stdin);
	freopen("spa2b.in","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		MOD1=min(47483647,K*60);
		START=ReadBinaryLL(),END=ReadBinaryLL();
		VIS.Clear(false),DISAPPEAR.Clear(NULL);
		for(int i=0;i<K;i++)
		{
			const LL v=ReadBinaryLL();
			vector<LL>*s=new vector<LL>();s->push_back(-1);
			VIS.Set(v,true),DISAPPEAR.Set(v,s);
		}
		puts(Solve()?"TAK":"NIE");
	}
	return 0;
}
