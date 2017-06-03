#include<cstdio>
#include<vector>
#include<cassert>
#include<map>
using namespace std;
const int MAX_BIG=500;
int N,R,Q;
int AREA[200000],BOSS[200000],DEP[200000];
vector<int>ET[200000],MEMBER[25000];
map<int,int>BIGA;
int UP[25000][MAX_BIG],DOWN[25000][MAX_BIG],ANS[MAX_BIG][MAX_BIG];
void BuildBIGA()
{
	BIGA.clear();
	multimap<int,int,greater<int> >tmp;
	for(int i=0;i<R;i++)tmp.insert(make_pair(MEMBER[i].size(),i));
	int cnt=0;
	for(const auto &it:tmp)if((BIGA[it.second]=cnt++)==MAX_BIG-1)break;
}
vector<int>FA[200000];
map<int,int>BuildUDA(const int u,const int dep,map<int,int>&tup)
{
	DEP[u]=dep;
	FA[u].clear();
	if(u)
	{
		for(int tmp=BOSS[u],i=0;;tmp=FA[tmp][i++])
		{
			FA[u].push_back(tmp);
			if(i>=(int)FA[tmp].size())break;
		}
	}
	for(const auto &it:tup)UP[AREA[u]][it.first]+=it.second;
	map<int,int>tdown;
	do
	{
		const auto it=BIGA.find(AREA[u]);
		if(it!=BIGA.end())
		{
			for(const auto &tit:tup)ANS[tit.first][it->second]+=tit.second;
			tup[it->second]++,tdown[it->second]++;
		}
	}while(0);
	for(const auto nxt:ET[u])
	{
		const map<int,int>&result=BuildUDA(nxt,dep+1,tup);
		for(const auto &it:result)tdown[it.first]+=it.second,DOWN[AREA[u]][it.first]+=it.second;
	}
	do
	{
		const auto it=BIGA.find(AREA[u]);
		if(it!=BIGA.end())tup[it->second]--;
	}while(0);
	return tdown;
}
bool IsBoss(const int a,int b)
{
	if(DEP[a]>=DEP[b])return false;
	for(int dis=DEP[b]-DEP[a],i=30;i>=0;i--)if(dis&(1<<i))b=FA[b][i];
	return a==b;
}
int Solve(const int r1,const int r2)
{
	const auto it1=BIGA.find(r1),it2=BIGA.find(r2);
	if(it1==BIGA.end()&&it2==BIGA.end())
	{
		int ans=0;
		for(const auto m1:MEMBER[r1])for(const auto m2:MEMBER[r2])if(IsBoss(m1,m2))ans++;
		return ans;
	}
	else if(it1==BIGA.end()&&it2!=BIGA.end())return DOWN[r1][it2->second];
	else if(it1!=BIGA.end()&&it2==BIGA.end())return UP[r2][it1->second];
	else return ANS[it1->second][it2->second];
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	assert(scanf("%d%d%d",&N,&R,&Q)==3);
	for(int i=0;i<R;i++)MEMBER[i].clear();
	BOSS[0]=-1;assert(scanf("%d",&AREA[0])==1),MEMBER[--AREA[0]].push_back(0);
	for(int i=1;i<N;i++)assert(scanf("%d%d",&BOSS[i],&AREA[i])==2),ET[--BOSS[i]].push_back(i),MEMBER[--AREA[i]].push_back(i);
	BuildBIGA();
	for(int i=0;i<(int)BIGA.size();i++)for(int j=0;j<(int)BIGA.size();j++)ANS[i][j]=0;
	for(int i=0;i<R;i++)for(int j=0;j<(int)BIGA.size();j++)UP[i][j]=DOWN[i][j]=0;
	map<int,int>tmp;
	BuildUDA(0,0,tmp);
	for(const auto &it:tmp)assert(it.second==0);
	while(Q--)
	{
		static int r1,r2;assert(scanf("%d%d",&r1,&r2)==2);
		assert((--r1)!=(--r2));
		printf("%d\n",Solve(r1,r2));
	}
	return 0;
}
