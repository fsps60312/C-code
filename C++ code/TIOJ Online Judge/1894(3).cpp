//#define SELF
#ifndef SELF
#include "lib1894.h"
#endif
#include<cassert>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
#ifdef SELF
int SS[4][4]=
{
	{0,3,5,7},
	{3,0,2,4},
	{5,2,0,6},
	{7,4,6,0}
};
int getDistance(int x, int y){return SS[x][y];}
#endif
#define loc first
#define id second
int D0[5000],DR[5000],DL[5000];
int *LOCATION,*TYPE;
void AddBrack(const int id,const int loc,const int type)
{
	LOCATION[id]=loc,TYPE[id]=type;
}
//void Insert(map<int,int>&s,const int key,const int value)
//{
//	assert(s.find(key)==s.end());
//	s[key]=value;
//}
void findLocation(int N,int FIRST,int _LOCATION[],int _TYPE[])
{
	LOCATION=_LOCATION,TYPE=_TYPE;
	for(int i=0;i<N;i++)TYPE[i]=0;
	LOCATION[0]=FIRST,TYPE[0]=1;
	if(N==1)return;
	int rb=1;
	for(int i=0;i<N;i++)if(i!=0)
	{
		D0[i]=getDistance(0,i);
		if(D0[i]<D0[rb])rb=i;
	}
	LOCATION[rb]=FIRST+D0[rb],TYPE[rb]=2;
	if(N==2)return;
	int lb=0;
	for(int i=0;i<N;i++)if(i!=rb)
	{
		DR[i]=getDistance(rb,i);
		if(DR[i]<DR[lb])lb=i;
	}
	LOCATION[lb]=LOCATION[rb]-DR[lb],TYPE[lb]=1;
//	printf("lb=%d,rb=%d\n",lb,rb);
	D0[0]=DR[0]*2;
	for(int i=0;i<N;i++)if(i!=lb&&i!=rb)
	{
		DL[i]=D0[i]-(DR[0]-DR[lb]);
	}
	vector<pair<int,int> >left,right;
	for(int i=0;i<N;i++)if(i!=lb&&i!=rb)
	{
		if(DL[i]<DR[i])right.push_back(make_pair(LOCATION[lb]+DL[i],i));
		else left.push_back(make_pair(LOCATION[rb]-DR[i],i));
	}
	if(!right.empty())
	{
		sort(right.begin(),right.end());
		map<int,int>bracks;
		if(true)
		{
			const auto &p=right.front();
			AddBrack(p.id,p.loc,2);
			bracks[p.loc]=p.id;
		}
		for(int i=1;i<(int)right.size();i++)
		{
			const auto lastbrack=*bracks.rbegin();
			const int gap=getDistance(right[i].id,lastbrack.id);
			const int turn=right[i].loc;
			const int dis=gap+lastbrack.loc-turn;
			assert(dis%2==0);
			if(bracks.find(lastbrack.loc-dis/2)!=bracks.end())
			{
				AddBrack(right[i].id,lastbrack.loc-gap,1);
			}
			else
			{
				AddBrack(right[i].id,right[i].loc,2);
				bracks[right[i].loc]=right[i].id;
			}
		}
	}
	if(!left.empty())
	{
		sort(left.begin(),left.end());
		map<int,int>bracks;
		if(true)
		{
			const auto &p=left.back();
			AddBrack(p.id,p.loc,1);
			bracks[p.loc]=p.id;
		}
		for(int i=(int)left.size()-2;i>=0;i--)
		{
			const auto lastbrack=*bracks.begin();
			const int gap=getDistance(left[i].id,lastbrack.id);
			const int turn=-left[i].loc;
			const int dis=gap+(-lastbrack.loc)-turn;
			assert(dis%2==0);
			if(bracks.find(lastbrack.loc+dis/2)!=bracks.end())
			{
				AddBrack(left[i].id,lastbrack.loc+gap,2);
			}
			else
			{
				AddBrack(left[i].id,left[i].loc,1);
				bracks[left[i].loc]=left[i].id;
			}
		}
	}
}
#ifdef SELF
int main()
{
	int ans1[4],ans2[4];
	findLocation(4,2,ans1,ans2);
	for(int i=0;i<4;i++)printf("id=%d,loc=%d,type=%d\n",i,ans1[i],ans2[i]);
	return 0;
}
#endif
