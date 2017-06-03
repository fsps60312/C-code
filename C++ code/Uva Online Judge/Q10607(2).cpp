#include<cstdio>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<cassert>
#define termin(x,...) {printf(x,##__VA_ARGS__);while(1)printf("E");assert(0);}
using namespace std;
const int INF=2147483647;
int M,N,MAP[250][250],VIS[150],SZ;
map<char,int>IDX;
vector<set<int> >TO;
void Connect(int a,int b)
{
	if(a==b)return;
	TO[a].insert(b);
	TO[b].insert(a);
}
///////////////////////////////////////////////////////////
set<int>CAP;
int DJ[150],DIS[150],PRE[150];
int findDJ(int a){return DJ[a]==a?a:(DJ[a]=findDJ(DJ[a]));}
int CAPG(){return findDJ(*TO[0].begin());}
bool AllConnected()
{
	int g=CAPG();
	for(set<int>::iterator it=TO[0].begin();it!=TO[0].end();it++)
	{
		if(findDJ(*it)!=g)return false;
	}
	return true;
}
struct Capq
{
	int u,pre;
	Capq(){}
	Capq(int u,int pre):u(u),pre(pre){}
};
bool BuildCAP()
{
	CAP.clear();
	for(int i=0;i<SZ;i++)DJ[i]=i,DIS[i]=INF;
	queue<Capq>q;
	for(int tag=0;tag<=1;tag++)
	{
		for(set<int>::iterator it=TO[0].begin();it!=TO[0].end();it++)
		{
			CAP.insert(*it);
			q.push(Capq(*it,-1));
		}
		while(!q.empty())
		{
			Capq u=q.front();q.pop();
			if(u.pre==-1)DIS[u.u]=0;//initial point
			else if(DIS[u.u]==INF)
			{
				if(!tag)continue;
				DIS[u.u]=DIS[u.pre]+1,PRE[u.u]=u.pre;
			}
			else
			{
				if(findDJ(u.u)!=findDJ(u.pre))
				{
					DJ[findDJ(u.u)]=findDJ(u.pre);
					for(int i=0,loc=u.u;i<DIS[u.u];i++,loc=PRE[loc])CAP.insert(loc),DJ[findDJ(loc)]=findDJ(PRE[loc]);
					for(int i=0,loc=u.pre;i<DIS[u.pre];i++,loc=PRE[loc])CAP.insert(loc),DJ[findDJ(loc)]=findDJ(PRE[loc]);
				}
				if(tag&&AllConnected())return true;
				continue;
			}
			for(set<int>::iterator it=TO[u.u].begin();it!=TO[u.u].end();it++)q.push(Capq(*it,u.u));
		}
	}
//	termin("can't connect caps\n");
	return false;
}
//////////////////////////////////////////////////////////////
struct War
{
	int u,cnt;
	War(){}
	War(int u,int cnt):u(u),cnt(cnt){}
};
int solve()
{
	if(SZ==1||!TO[0].size())return -1;
	set<int>out;
	for(int i=0;i<M;i++)out.insert(MAP[i][0]),out.insert(MAP[i][N-1]);
	for(int i=0;i<N;i++)out.insert(MAP[0][i]),out.insert(MAP[M-1][i]);
	if(out.find(0)!=out.end())return -1;
	if(!BuildCAP())return -1;
	for(int i=0;i<SZ;i++)VIS[i]=0;
	queue<War>q;
	for(set<int>::iterator it=out.begin();it!=out.end();it++)q.push(War(*it,1));
	while(!q.empty())
	{
		War w=q.front();q.pop();
		if(VIS[w.u]++)continue;
		if(CAP.find(w.u)!=CAP.end())return w.cnt+CAP.size()-1;
		for(set<int>::iterator it=TO[w.u].begin();it!=TO[w.u].end();it++)
		{
			q.push(War(*it,w.cnt+1));
		}
	}
//	termin("capital unreachable\n");
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&M,&N)==2&&(M||N))
	{
		if(M>250||N>250)termin("M=%d,N=%d\n",M,N);
		TO.clear();
		IDX.clear();
		IDX['A']=0;
		TO.push_back(set<int>());
		SZ=1;
		for(int i=0;i<M;i++)
		{
			for(int j=0;j<N;j++)
			{
				static char v;
				do{if(scanf("%c",&v)!=1)return 0;}while(v==' '||v=='\n');
				if(IDX.find(v)==IDX.end())
				{
					TO.push_back(set<int>());
					IDX[v]=SZ++;
				}
				MAP[i][j]=IDX[v];
				if(i)Connect(MAP[i][j],MAP[i-1][j]);
				if(j)Connect(MAP[i][j],MAP[i][j-1]);
			}
		}
		if(SZ>150)termin("SZ==%d>150\n",SZ);
		printf("%d\n",solve());
	}
	return 0;
}
