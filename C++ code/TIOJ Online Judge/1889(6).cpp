//#define SELF
#ifndef SELF
#include "lib1889.h"
#endif
#include<cstdio>
#include<cassert>
#include<vector>
#include<set>
#include<map>
#include<algorithm>
using namespace std;
#ifdef SELF
int Init()
{
	exit(0);
	static int kase=0;
	if(kase++)return 1;
}
void answer(int v)
{
	printf("ans=%d\n",v);
}
int getDistance(int a,int b)
{
	return a||b?-1:-1;
}
#endif
map<int,int>ET[110];
int Dist(const int a,const int b)
{
	if(a==b)return 0;
	const auto it=ET[a].find(b);
	if(it!=ET[a].end())return it->second;
	return ET[a][b]=ET[b][a]=getDistance(a,b);
}
int N,A,B;
int LEN[110],LOC[110];
void Filter(set<int>&s)
{
	assert((int)s.size()==2);
	int cnt=0;
	for(int i=0;i<N;i++)if(LOC[i]>*s.begin())cnt++;
	s.erase(cnt*2>N?s.begin():next(s.begin()));
}
bool Check(const int loc)
{
	int cnt1=0,cnt2=0;
	for(int i=0;i<N;i++)
	{
		if(LOC[i]<loc)cnt1++;
		if(LOC[i]>loc)cnt2++;
	}
	return cnt1*2<=N&&cnt2*2<=N;
}
bool InSameTree(const int a,const int b)
{
	return Dist(a,b)<LEN[a]+LEN[b];
}
bool Solve(const vector<int>&ps)
{
	vector<int>stk,hp;
	for(const int p:ps)
	{
		if(stk.empty())stk.push_back(p);
		else if(InSameTree(stk.back(),p))hp.push_back(p);
		else
		{
			stk.push_back(p);
			if(!hp.empty())stk.push_back(hp.back()),hp.pop_back();
		}
	}
	const int king=stk.back();
	int cnt=0;
	for(;!stk.empty();)
	{
		if(InSameTree(stk.back(),king))
		{
			cnt++;
			if((int)stk.size()==1)break;
			stk.pop_back(),stk.pop_back();
		}
		else
		{
			if(hp.empty())return false;
			cnt++;
			hp.pop_back(),stk.pop_back();
		}
	}
	cnt+=hp.size();
	return cnt*2>N;
}
int main()
{
	for(;;)
	{
		N=Init();
		for(int i=0;i<N;i++)ET[i].clear();
		A=1;
		for(int i=0;i<N;i++)if(i!=0&&Dist(0,i)>Dist(0,A))A=i;
		B=0;
		for(int i=0;i<N;i++)if(i!=A&&Dist(A,i)>Dist(A,B))B=i;
		map<int,set<int> >minloc;
		for(int i=0;i<N;i++)
		{
			LEN[i]=(Dist(A,i)+Dist(i,0)-Dist(A,0))/2;
			LOC[i]=Dist(i,A)-LEN[i];
			minloc[max(LOC[i],Dist(A,B)-LOC[i])].insert(LOC[i]);
		}
		const int radius=minloc.begin()->first;
		if((int)minloc.begin()->second.size()==2)Filter(minloc.begin()->second);
		assert((int)minloc.begin()->second.size()==1);
		const int midloc=*minloc.begin()->second.begin();
		if(!Check(midloc))
		{
			answer(-radius);
			continue;
		}
		vector<int>ps;
		for(int i=0;i<N;i++)if(LOC[i]==midloc)ps.push_back(i);
		answer(Solve(ps)?-radius:radius);
	}
	return 0;
}

