#include<cstdio>
#include<cassert>
#include<algorithm>
#include<utility>
using namespace std;
typedef long long LL;
int N;
pair<int,int>TMP1[2][1000001],*A=TMP1[0],*B=TMP1[1];
LL TMP2[2][1000001],*ASUM=TMP2[0],*BSUM=TMP2[1];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=1;i<=N;i++)scanf("%d",&A[i].first),A[i].second=i;
		for(int i=1;i<=N;i++)scanf("%d",&B[i].first),B[i].second=i;
		sort(A+1,A+N+1),sort(B+1,B+N+1);
		ASUM[0]=BSUM[0]=0;
		for(int i=1;i<=N;i++)ASUM[i]=ASUM[i-1]+A[i].first,BSUM[i]=BSUM[i-1]+B[i].first;
		bool exchanged=false;
		if(ASUM[N]<BSUM[N])swap(A,B),swap(ASUM,BSUM),exchanged=true;
		static pair<int,int>pre[1000000];
		for(int i=0;i<N;i++)pre[i].first=-1;
		for(int i=0,j=0;;i++)
		{
			assert(i<=N);
			while(j+1<=N&&BSUM[j+1]<=ASUM[i])++j;
			assert(ASUM[i]>=BSUM[j]&&ASUM[i]-BSUM[j]<N);
			const LL dif=ASUM[i]-BSUM[j];
			if(pre[dif].first==-1)pre[dif]=make_pair(i,j);
			else
			{
				vector<int>ansa,ansb;
				for(int k=pre[dif].first+1;k<=i;k++)ansa.push_back(A[k].second);
				for(int k=pre[dif].second+1;k<=j;k++)ansb.push_back(B[k].second);
				if(exchanged)ansa.swap(ansb);
				printf("%d\n",(int)ansa.size());
				for(int k=0;k<(int)ansa.size();k++)
				{
					if(k)putchar(' ');
					printf("%d",ansa[k]);
				}
				puts("");
				printf("%d\n",(int)ansb.size());
				for(int k=0;k<(int)ansb.size();k++)
				{
					if(k)putchar(' ');
					printf("%d",ansb[k]);
				}
				puts("");
				break;
			}
		}
	}
	return 0;
}
