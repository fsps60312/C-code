#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
typedef long long LL;
LL A[4];
LL Solve(const LL dep,const vector<LL>&offset,const LL mod)
{
	LL ans;
	if(dep==3)ans=A[dep];
	else
	{
		vector<LL>nxto;
		nxto.push_back(1LL);
		for(LL i=0,j=0;;)
		{
			i++;
			j++;
			nxto.push_back(nxto[j-1LL]*A[dep]%mod);
			j++;
			nxto.push_back(nxto[j-1LL]*A[dep]%mod);
			if(nxto[i]==nxto[j])
			{
				ans=Solve(dep+1,nxto,j-i);
				break;
			}
		}
	}
	if(dep==0)return ans;
	if(ans<(LL)offset.size())return offset[ans];
	const LL v=((ans-(LL)offset.size())/mod+1LL)*mod;
	assert((LL)offset.size()-mod<=ans-v&&ans-v<(LL)offset.size());
	return offset[ans-v];
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		for(int i=0;i<4;i++)scanf("%lld",&A[i]);
		LL m;scanf("%lld",&m);
		printf("%lld\n",Solve(0,vector<LL>(),m));
	}
	return 0;
}
