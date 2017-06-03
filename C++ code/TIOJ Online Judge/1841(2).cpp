#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long LL;
void getmax(int &a,const int b){if(b>a)a=b;}
int N,L[1000000];
LL S[1000000];
int main()
{
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%lld",&S[i]);
		LL sum=0LL;
		for(int i=0,left=0;i<N;i++)
		{
			sum+=S[i];
			if(sum<0LL)sum=0LL,left=i+1;
			L[i]=left;
		}
		int ans=0;
		sum=0LL;
		for(int i=N-1,right=N-1;i>=0;i--)
		{
			sum+=S[i];
			if(sum<0LL)sum=0LL,right=i-1;
			else if(i>=L[right])getmax(ans,right-i+1);
		}
		printf("%d\n",ans);
	}
	return 0;
}
