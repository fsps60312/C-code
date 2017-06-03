#include<cstdio>
#include<algorithm>
using namespace std;
int N,H[100000],IDX[100000],VIS[100000];
bool Cmp(const int a,const int b)
{
	return H[a]!=H[b]?H[a]<H[b]:a<b;
}
int main()
{
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&H[i]);
		for(int i=0;i<N;i++)IDX[i]=i,VIS[i]=false;
		sort(IDX,IDX+N,Cmp);
		int ans=0;
		for(int i=0,cnt=0;i<N;i++)
		{
			if(VIS[i])cnt++;
			VIS[IDX[i]]=true;
			if(IDX[i]<=i)cnt++;
			if(cnt==i+1)ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
