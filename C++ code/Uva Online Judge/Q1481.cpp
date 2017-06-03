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
void Untag(const int &v)
{
	int i=L2[v];
	assert(VIS[i]==true);
	int add=1;
	if(i==0||!VIS[i-1])add--;
	if(i==N-1||!VIS[i+1])add--;
	CNT+=add;
	VIS[i]=false;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		for(int i=0;i<N;i++)scanf("%d",&S1[i]);
		for(int i=0;i<N;i++)scanf("%d",&S2[i]);
		for(int i=0;i<N;i++)L1[--S1[i]]=i,L2[--S2[i]]=i,VIS[i]=false;
		CNT=0;
		int l=0;
		int ans=0;
		for(int r=0;r<N;r++)
		{
			Tag(S1[r]);
			while(l>0&&CNT==1)Tag(S1[--l]);
//			printf("acnt=%d:",CNT);for(int i=0;i<N;i++)printf("%d",VIS[i]);puts("");
			while(l<=r&&CNT>1)Untag(S1[l++]);
			assert(l<=r);
			printf("bcnt=%d:",CNT);for(int i=0;i<N;i++)printf("%d",VIS[i]);puts("");
			if(r-l+1>=2)ans+=r-l;
		}
		sort(S1,S1+N),sort(S2,S2+N);
		for(int i=0;i<N;i++)assert(S1[i]==i&&S2[i]==i);
		printf("%d\n",ans);
	}
	return 0;
}
