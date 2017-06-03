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
		int *pre=new int[mod];
		for(int i=0;i<mod;i++)pre[i]=-1;
		pre[1]=0;
		for(int i=1;;i++)
		{
			const LL v=nxto[i-1]*A[dep]%mod;
			nxto.push_back(v);
			if(pre[v]!=-1)
			{
				ans=Solve(dep+1,nxto,i-pre[v]);
				break;
			}
			else pre[v]=i;
		}
		delete[]pre;
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
