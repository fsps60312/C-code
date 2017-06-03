#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
typedef long long LL;
LL A,B;
int main()
{
//	freopen("in.txt","r",stdin);
	vector<LL>tmp;
	for(int d=2;d<=62;d++)
	{
		const LL all=(1LL<<d)-1LL;
		for(int i=0;i+1<d;i++)tmp.push_back(all-(1LL<<i));
	}
	while(scanf("%I64d%I64d",&A,&B)==2)
	{
		int ans=0;
		for(const LL &v:tmp)if(A<=v&&v<=B)ans++;
		printf("%d\n",ans);
		break;
	}
	return 0;
}
