#include<bits/stdc++.h>
using namespace std;
map<int,vector<int> >IDX;
struct Pair
{
	int x,y;
	Pair(){}
	Pair(int x,int y):x(x),y(y){}
};
vector<Pair>P;
int main()
{
	scanf("%d%d",&N,&M);
	static int v;
	for(int i=0;i<N;i++)
	{
		scanf("%d",&v);
		IDX[v].push_back(i);
	}
	for(int i=0;i<M;i++)
	{
		scanf("%d",&v);
		if(IDX.find(v)==IDX.end())continue;
		vector<int>&vec=IDX[v];
		for(int j=0;j<vec.size();j++)P.push_back(Pair())
	}
	return 0;
}
