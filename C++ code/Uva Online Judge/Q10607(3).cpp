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
//////////////////////////////////////////////////////////////
struct War
{
	int u,cnt;
	War(){}
	War(int u,int cnt):u(u),cnt(cnt){}
};
set<int>CAP;
int GetLen(queue<War>&q,bool &goout,int sp)
{
	for(int i=1;i<=SZ;i++)VIS[i]=0;
	while(!q.empty())
	{
		War w=q.front();q.pop();
		if(VIS[w.u]++)continue;
		if(w.u!=sp&&CAP.find(w.u)!=CAP.end())
		{
			if(w.u==SZ)goout=true;
			return w.cnt;
		}
		for(set<int>::iterator it=TO[w.u].begin();it!=TO[w.u].end();it++)
		{
			q.push(War(*it,w.cnt+1));
		}
	}
}
int solve()
{
	if(SZ==1||!TO[0].size()||TO[0].find(SZ)!=TO[0].end())return -1;
	CAP.clear();
	CAP.insert(SZ);
	for(set<int>::iterator it=TO[0].begin();it!=TO[0].end();it++)CAP.insert(*it);
	VIS[0]=1;
	int ans=0;
	bool goout=false;
	for(set<int>::iterator it=TO[0].begin();it!=TO[0].end();it++)
	{
		queue<War>q;
		q.push(War(*it,0));
		ans+=GetLen(q,goout,*it);
	}
	if(!goout)
	{
		queue<War>q;
		for(set<int>::iterator it=TO[0].begin();it!=TO[0].end();it++)q.push(War(*it,0));
		CAP.clear();
		CAP.insert(SZ);
		ans+=GetLen(q,goout,-1)-1;
	}
	return ans;
//	termin("capital unreachable\n");
}
char LINE[1000];
int main()
{
//	freopen("in.txt","r",stdin);
	while(gets(LINE))
	{
		sscanf(LINE,"%d%d",&M,&N);
		if(!M&&!N)break;
		if(M>250||N>250)termin("M=%d,N=%d\n",M,N);
		TO.clear();
		IDX.clear();
		IDX['A']=0;
		TO.push_back(set<int>());
		SZ=1;
		for(int i=0;i<M;i++)
		{
//			static char line[250];
			static char v;
			for(int j=0;j<N;j++)
			{
				do{v=getchar();}while(v=='\n');
//				line[j]=v;
				if(IDX.find(v)==IDX.end())
				{
					TO.push_back(set<int>());
					IDX[v]=SZ++;
				}
				MAP[i][j]=IDX[v];
				if(i)Connect(MAP[i][j],MAP[i-1][j]);
				if(j)Connect(MAP[i][j],MAP[i][j-1]);
			}
//			line[N]=0;
//			puts(line);
			do{v=getchar();}while(v!='\n');
		}
		TO.push_back(set<int>());
		for(int i=0;i<M;i++)Connect(SZ,MAP[i][0]),Connect(SZ,MAP[i][N-1]);
		for(int i=0;i<N;i++)Connect(SZ,MAP[0][i]),Connect(SZ,MAP[M-1][i]);
		if(SZ>150)termin("SZ==%d>150\n",SZ);
		printf("%d\n",solve());
	}
	return 0;
}
