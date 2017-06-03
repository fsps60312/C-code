#include<cstdio>
#include<algorithm>
#include<set>
using namespace std;
typedef long long LL;
void getmax(int &a,const int b){if(b>a)a=b;}
int N,L[1000000];
LL S[1000000];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%lld",&S[i]);
		if(true)
		{
			LL sum=0LL;
			for(int i=0,left=0;i<N;i++)
			{
				sum+=S[i];
				if(sum<0LL)sum=0LL,left=i+1;
				L[i]=left;
			}
		}
		int ans=0;
		static LL sum[1000001];sum[N]=0LL;
		multiset<LL>height;height.insert(sum[N]);
		for(int i=N-1,right=N;i>=0;i--)
		{
			height.insert(sum[i]=sum[i+1]+S[i]);
			while(!height.empty()&&(L[right]>i||(*height.begin())<sum[right]))height.erase(height.find(sum[right--]));
			getmax(ans,right-i);
		}
		printf("%d\n",ans);
	}
	return 0;
}
