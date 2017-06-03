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
	int cnt1=0,cnt2=0;
	for(int i=0;i<V.size();i++)
	{
		if(V[i]==1)cnt1++;
		if(V[i]==2)cnt2++;
	}
	if(cnt1+cnt2<V.size())return true;
	if(!(cnt2&1))return false;
	if(cnt2)return true;
	return cnt1&1?true:false;
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
