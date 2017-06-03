#include<bits/stdc++.h>
using namespace std;
int N;
map<int,int>IDX;
int DP[100000],ANS;
int main()
{
	scanf("%d",&N);
	static int v,l,r,mid;
	for(int i=0;i<N;i++){scanf("%d",&v);IDX[v]=i;}
	scanf("%d",&v);
	DP[0]=IDX[v];
	ANS=1;
	for(int i=1;i<N;i++)
	{
		scanf("%d",&v);
		v=IDX[v];
		l=0,r=ANS;
		while(l<r)
		{
			mid=(l+r)>>1;
			if(v>DP[mid])l=mid+1;
			else r=mid; 
		}
		if(l==ANS)DP[ANS++]=v;
		else if(v<DP[l])DP[l]=v;
	}
	printf("%d\n",ANS);
	return 0;
}
