#define SELF
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
int Init(){return 11;}
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
	return ans[a-1][b-1];
}
#endif
map<int,int>ET[111];
int N,A,B;
void GetAB()
{
	for(int i=1;i<=N;i++)ET[i].clear();
	A=2;
	for(int i=2;i<=N;i++)
	{
		const int ans=getDistance(1,i);
		ET[1][i]=ET[i][1]=ans;
		if(ET[1][i]>ET[1][A])A=i;
	}
	B=1;
	for(int i=2;i<=N;i++)if(i!=A)
	{
		const int ans=getDistance(A,i);
		ET[A][i]=ET[i][A]=ans;
		if(ET[A][i]>ET[A][B])B=i;
	}
}
int RADIUS,DIS[111];
map<int,vector<pair<int,int> > >LINE;
vector<int>WDIS;
void BuildDiameter()
{
	map<int,set<int> >wp_map;
	for(int i=1;i<=N;i++)if(i!=A&&i!=B)
	{
		const int len=(ET[A][i]+ET[B][i]-ET[A][B])/2;
		DIS[i]=ET[A][i]-len;
		LINE[DIS[i]].push_back(make_pair(i,len));
		wp_map[max(DIS[i],ET[A][B]-DIS[i])].insert(DIS[i]);
	}
	RADIUS=wp_map.begin()->first;
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
	if(cnt*2>N)return false;
	it=LINE.lower_bound(WDIS[0]);
	cnt=0;
	for(;it!=LINE.begin();)cnt+=(--it)->second.size();
	return cnt*2<=N;
}
int DJ[111];
int Find(const int a){return DJ[a]==a?a:(DJ[a]=Find(DJ[a]));}
bool Solve()
{
	const vector<pair<int,int> >&ps=LINE[WDIS[0]];
	for(int i=0;i<(int)ps.size();i++)DJ[i]=i;
	for(int i=0;i<(int)ps.size();i++)
	{
		for(int j=i+1;j<(int)ps.size();j++)
		{
			if(getDistance(ps[i].first,ps[j].first)<ps[i].second+ps[j].second)DJ[Find(i)]=Find(j);
		}
	}
	map<int,int>cnt;
	for(int i=0;i<(int)ps.size();i++)cnt[Find(i)]++;
	for(const auto &it:cnt)if(it.second*2>N)return false;
	return true;
}
int main()
{
	N=Init();
	GetAB();
	BuildDiameter();
	if((int)WDIS.size()==2)FilterWDIS();
	printf("(A,B)=(%d,%d),WDIS=%d\n",A,B,WDIS[0]);
	if(!CheckOnDiameter()){answer(-RADIUS);return 0;}
	if(Solve())answer(RADIUS);
	else answer(-RADIUS);
	return 0;
}
