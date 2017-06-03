#include"rail.h"
#include<bits/stdc++.h>
using namespace std;
int D0[5000],DR[5000],DL[5000];
struct Rail
{
	int id,loc;
	Rail(){}
	Rail(const int _id,const int _loc):id(_id),loc(_loc){}
	bool operator<(const Rail &r)const{return loc<r.loc;}
};
void findLocation(int N,int FIRST,int LOCATION[],int TYPE[])
{
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
	D0[0]=DR[0]*2;
	for(int i=0;i<N;i++)if(i!=lb&&i!=rb)DL[i]=D0[i]-(DR[0]-DR[lb]);
	vector<Rail>left,right;
	for(int i=0;i<N;i++)if(i!=rb&&i!=lb)
	{
		if(DR[i]<DL[i])left.push_back(Rail(i,LOCATION[rb]-DR[i]));
		else right.push_back(Rail(i,LOCATION[lb]+DL[i]));
	}
	if(!left.empty())
	{
		for(const Rail &r:left)LOCATION[r.id]=r.loc,TYPE[r.id]=1;
		sort(left.begin(),left.end());
		map<int,int>lbs;
		lbs[left.back().loc]=left.back().id;
		for(int i=(int)left.size()-2;i>=0;i--)
		{
			const Rail &r=left[i];
			const int dis=(DR[lbs.begin()->second]+getDistance(lbs.begin()->second,r.id)-DR[r.id])/2;
			if(lbs.find(lbs.begin()->first+dis)!=lbs.end())
			{
				LOCATION[r.id]=lbs.begin()->first+(lbs.begin()->first-r.loc)+dis*2,TYPE[r.id]=2;
			}
			else lbs[r.loc]=r.id;
		}
	}
	if(!right.empty())
	{
		for(const Rail &r:right)LOCATION[r.id]=r.loc,TYPE[r.id]=2;
		sort(right.begin(),right.end());
		map<int,int>rbs;
		rbs[right.front().loc]=right.front().id;
		for(int i=1;i<(int)right.size();i++)
		{
			const Rail &r=right[i];
			const int dis=(DL[rbs.rbegin()->second]+getDistance(r.id,rbs.rbegin()->second)-DL[r.id])/2;
			if(rbs.find(rbs.rbegin()->first-dis)!=rbs.end())
			{
				LOCATION[r.id]=rbs.rbegin()->first-(r.loc-rbs.rbegin()->first)-dis*2,TYPE[r.id]=1;
			}
			else rbs[r.loc]=r.id;
		}
	}
}
