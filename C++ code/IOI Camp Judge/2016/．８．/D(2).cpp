#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
int GetSG(const int total,const int sg_zero,const int l,const int r)
{
	const int value=total%(l+r);
	if(value==0||value>=l+r-(l-1))return sg_zero;
	const int g=(value-1)/l;
	if(g<sg_zero)return g;
	return g+1;
}
int N,L,R,S[100000];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d%d",&N,&L,&R);
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		int sg=0;
		for(int i=N-1;i>=0;i--)sg=GetSG(S[i],sg,L,R);
		for(int i=0;i<N;i++)printf(sg?"Bo":"Ong");puts("");
	}
	return 0;
}
