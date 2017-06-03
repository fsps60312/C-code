#include<cstdio>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<cassert>
#define termin(x,...) {printf(x,##__VA_ARGS__);while(1)printf("E");assert(0);}
using namespace std;
int M,N,MAP[200][200],VIS[1<<4][100],SZ;
map<char,int>IDX;
vector<set<int> >TO;
void Connect(int a,int b)
{
	TO[a].insert(b);
	TO[b].insert(a);
}
struct War
{
	int u,cnt,conq;
	War(){}
	War(int u,int cnt,int conq):u(u),cnt(cnt),conq(conq){}
};
int solve()
{
	map<int,int>cap;
	for(set<int>::iterator it=TO[0].begin();it!=TO[0].end();it++)
	{
		static int sz;
		sz=cap.size();
		cap[*it]=sz;
	}
//	if(cap.size()>4)termin("cap.size()==%d>4\n",cap.size());
	int goal=(1<<cap.size())-1;
	for(int i=0;i<=goal;i++)for(int j=0;j<SZ;j++)VIS[i][j]=0;
	set<int>out;
	for(int i=0;i<M;i++)out.insert(MAP[i][0]),out.insert(MAP[i][N-1]);
	for(int i=0;i<N;i++)out.insert(MAP[0][i]),out.insert(MAP[M-1][i]);
	if(out.find(0)!=out.end())return -1;
	queue<War>q;
	for(set<int>::iterator it=out.begin();it!=out.end();it++)q.push(War(*it,1,0));
	while(!q.empty())
	{
		War w=q.front();q.pop();
		if(cap.find(w.u)!=cap.end())w.conq|=1<<cap[w.u];
		if(VIS[w.conq][w.u])continue;
		if(w.conq==goal)return w.cnt;
		VIS[w.conq][w.u]=1;
		for(set<int>::iterator it=TO[w.u].begin();it!=TO[w.u].end();it++)
		{
			q.push(War(*it,w.cnt+1,w.conq));
		}
	}
	termin("capital unreachable\n");
}
int main()
{
	while(scanf("%d%d",&M,&N)==2&&(M||N))
	{
		if(M>200||N>200)termin("M=%d,N=%d\n",M,N);
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
				do{v=getchar();}while(v==' '||v=='\n');
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
		if(SZ>100)termin("SZ==%d>100\n",SZ);
		printf("%d\n",solve());
	}
	return 0;
}
