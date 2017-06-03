#include<cstdio>
#include<cassert>
using namespace std;
int N,P,L[100000],R[100000];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&P)==2)
	{
		double ans=0.0;
		for(int i=0;i<N;i++)scanf("%d%d",&L[i],&R[i]);
		for(int i=0;i<N;i++)
		{
			const int l=L[(i+1)%N],r=R[(i+1)%N];
			const double &lose=(1.0-(double)(R[i]/P-(L[i]-1)/P)/(R[i]-L[i]+1))*(1.0-(double)(r/P-(l-1)/P)/(r-l+1));
			ans+=(1.0-lose)*2000.0;
		}
		printf("%.9f\n",ans);
	}
	return 0;
}
