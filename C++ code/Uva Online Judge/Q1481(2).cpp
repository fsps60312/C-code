#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
int N,S1[3000],S2[3000],L1[3000],L2[3000];
bool VIS[3000];
int CNT;
void Tag(const int &v)
{
	int i=L2[v];
	assert(VIS[i]==false);
	int add=-1;
	if(i==0||!VIS[i-1])add++;
	if(i==N-1||!VIS[i+1])add++;
	CNT+=add;
	VIS[i]=true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		for(int i=0;i<N;i++)scanf("%d",&S1[i]);
		for(int i=0;i<N;i++)scanf("%d",&S2[i]);
		for(int i=0;i<N;i++)L1[--S1[i]]=i,L2[--S2[i]]=i,VIS[i]=false;
		int ans=0;
		for(int r=0;r<N;r++)
		{
			CNT=0;
			Tag(S1[r]);
			for(int l=r-1;l>=0;l--)
			{
				Tag(S1[l]);
				if(CNT==1)ans++;
			}
			for(int i=0;i<=r;i++)VIS[L2[S1[i]]]=false;
		}
		sort(S1,S1+N),sort(S2,S2+N);
		for(int i=0;i<N;i++)assert(S1[i]==i&&S2[i]==i);
		printf("%d\n",ans);
	}
	return 0;
}
