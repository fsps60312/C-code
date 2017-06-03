#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
vector<LL>F;
int GetAns(const LL n)
{
	vector<LL>::iterator itr=lower_bound(F.begin(),F.end(),n);
	if(*itr==n)return 1;
	vector<LL>::iterator itl=lower_bound(F.begin(),F.end(),n);
	itl--;
	return GetAns(min(*itr-n,n-*itl))+1;
}
LL N;
int main()
{
	F.push_back(1LL),F.push_back(2LL);
	for(int i=2;;i++)
	{
		F.push_back(F[i-2]+F[i-1]);
		if(F[i]>=1000000000000000000LL)break;
	}
//	for(const LL v:F)printf(" %lld",v);puts("");
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%lld",&N);
		printf("%d\n",GetAns(N));
	}
	return 0;
}
