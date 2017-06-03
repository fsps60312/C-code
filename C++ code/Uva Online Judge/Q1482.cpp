#include<cstdio>
#include<vector>
typedef long long LL;
using namespace std;
int T,N;
LL P;
vector<LL>WIN;
bool findWIN(LL p)
{
	int l=0,r=WIN.size()-1,mid;
	while(l<r)
	{
		mid=(l+r)>>1;
		if(WIN[mid]<p)l=mid+1;
		else r=mid;
	}
	return WIN[l]==p;
}
int main()
{
	WIN.push_back(2LL);
	for(int i=0;WIN[i]<=2000000000000000000LL;i++)WIN.push_back((WIN[i]<<1)+1LL);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		int ans=0;
		for(int i=0;i<N;i++)
		{
			scanf("%lld",&P);
			if(!findWIN(P))ans++;
		}
		if((ans+N)&1)printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
