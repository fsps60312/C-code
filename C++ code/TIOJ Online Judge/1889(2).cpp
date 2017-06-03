//#define SELF
#ifndef SELF
#include "lib1889.h"
#endif
#include<cstdio>
#include<cassert>
#include<map>
#include<set>
#include<algorithm>
#include<vector>
using namespace std;
#ifdef SELF
int Init(){static int kase=0;if(kase++)exit(0);return 11;}
void answer(int ans){printf("ans=%d\n",ans);}
int getDistance(int a,int b)
{
	static int ans[11][11]=
	{
		{0,17,18,20,17,12,20,16,23,20,11},
		{17,0,23,25,22,17,25,21,28,25,16},
		{18,23,0,12,21,16,24,20,27,24,17},
		{20,25,12,0,23,18,26,22,29,26,19},
		{17,22,21,23,0,9,21,17,26,23,16},
		{12,17,16,18,9,0,16,12,21,18,11},
		{20,25,24,26,21,16,0,10,29,26,19},
		{16,21,20,22,17,12,10,0,25,22,15},
		{23,28,27,29,26,21,29,25,0,21,22},
		{20,25,24,26,23,18,26,22,21,0,19},
		{11,16,17,19,16,11,19,15,22,19,0}
	};
	return ans[a][b];
}
#endif
map<int,int>ET[110];
int Dist(const int a,const int b)
{
	assert(a!=b);
	if(!ET[a].count(b))ET[a][b]=ET[b][a]=getDistance(a,b);
	return ET[a][b];
}
int N,A,B;
void GetAB()
{
	for(int i=0;i<N;i++)ET[i].clear();
	A=1;
	for(int i=0;i<N;i++)if(i!=0&&Dist(0,i)>Dist(0,A))A=i;
	B=0;
	for(int i=0;i<N;i++)if(i!=A&&Dist(A,i)>Dist(A,B))B=i;
}
int RADIUS,DIS[110];
map<int,vector<pair<int,int> > >LINE;
vector<int>WDIS;
void BuildDiameter()
{
	LINE.clear();
	map<int,set<int> >wp_map;
	for(int i=0;i<N;i++)if(i!=A&&i!=B)
	{
		const int len=(Dist(A,i)+Dist(B,i)-Dist(A,B))/2;
		DIS[i]=Dist(A,i)-len;
//		printf("dist[%d]=%d,len=%d\n",i,DIS[i],len);
		LINE[DIS[i]].push_back(make_pair(i,len));
		wp_map[max(DIS[i],Dist(A,B)-DIS[i])].insert(DIS[i]);
	}
	//call 3N times
	RADIUS=wp_map.begin()->first;
	WDIS.clear();
	for(const int v:wp_map.begin()->second)WDIS.push_back(v);
}
void FilterWDIS()
{
	assert((int)WDIS.size()==2);
	auto it=LINE.upper_bound(WDIS[0]);
	int cnt=0;
	while(it!=LINE.begin())cnt+=(--it)->second.size();
	if(cnt*2>N)WDIS.pop_back();
	else WDIS.erase(WDIS.begin());
}
bool CheckOnDiameter()
{
	assert((int)WDIS.size()==1);
	auto it=LINE.upper_bound(WDIS[0]);
	int cnt=0;
	for(;it!=LINE.end();it++)cnt+=it->second.size();
//	printf("cnt=%d\n",cnt);
	if(cnt*2>N)return false;
	it=LINE.lower_bound(WDIS[0]);
	cnt=0;
	for(;it!=LINE.begin();)cnt+=(--it)->second.size();
//	printf("cnt=%d\n",cnt);
	return cnt*2<=N;
}
int DJ[110];
int Find(const int a){return DJ[a]==a?a:(DJ[a]=Find(DJ[a]));}
bool Solve()
{
	const vector<pair<int,int> >&ps=LINE[WDIS[0]];
	for(int i=0;i<(int)ps.size();i++)DJ[i]=i;//,printf("%d ",ps[i].first);puts("");
	for(int i=0;i<(int)ps.size();i++)
	{
		for(int j=i+1;j<(int)ps.size();j++)
		{
			if(Dist(ps[i].first,ps[j].first)<ps[i].second+ps[j].second)DJ[Find(i)]=Find(j);
		}
	}
	map<int,int>cnt;
	for(int i=0;i<(int)ps.size();i++)cnt[Find(i)]++;
//	for(const auto &it:cnt)printf("%d ",it.second);puts("");
	for(const auto &it:cnt)if(it.second*2>N)return false;
	return true;
}
int main()
{
	for(;;)
	{
		N=Init();
		for(int i=0;i<N;i++)ET[i].clear();
		GetAB();
//		printf("A=%d,B=%d\n",A,B);
		BuildDiameter();
//		for(const auto &it:LINE)
//		{
//			printf("dist=%d,",it.first);
//			for(const auto v:it.second)printf(" (%d,%d)",v.first,v.second);puts("");
//		}
		if((int)WDIS.size()==2)FilterWDIS();
		if(!CheckOnDiameter()){answer(-RADIUS);continue;}
		if(Solve())answer(RADIUS);
		else answer(-RADIUS);
	}
	return 0;
}
