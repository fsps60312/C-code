#include<bits/stdc++.h>
using namespace std;
//WIN: aabbccddee...zz
int T,N,S[1000];
vector<int>V;
bool Solve()
{
	int idx=(N&1?0:1);
	V.clear();
	for(;idx<N;idx+=2)
	{
		int v=(idx==0?S[idx]:S[idx]-S[idx-1]);
		if(v)V.push_back(v);
	}
	//first take out V will win
	bool all1=true;
	for(int i=0;i<V.size();i++)if(V[i]!=1){all1=false;break;}
	if(all1)return V.size()&1?true:false;
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			scanf("%d",&N);
			for(int i=0;i<N;i++)scanf("%d",&S[i]);
			puts(Solve()?"TAK":"NIE");
		}
	}
	return 0;
}
