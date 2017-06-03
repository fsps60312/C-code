#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
typedef long long LL;
int N;
LL S[50];
vector<LL>operator*(const vector<LL>&a,const vector<LL>&b)
{
	vector<LL>ans;ans.resize(a.size()+b.size()-1,0LL);
	for(int i=0;i<(int)a.size();i++)for(int j=0;j<(int)b.size();j++)ans[i+j]+=a[i]*b[j];
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%lld",&S[i]);
		vector<LL>ans{1LL};
		for(int i=0;i<N;i++)ans=ans*vector<LL>{-S[i],1LL};
		for(int i=(int)ans.size()-1;i>=0;i--)
		{
			const LL &v=ans[i];
			if(v==0&&i>0)continue;
			if(i<(int)ans.size()-1)printf(" %c ",v>=0LL?'+':'-');
			if(i==0||(v!=-1LL&&v!=1LL))printf("%lld",v>=0?v:-v);
			if(i>0)printf("x");
			if(i>1)printf("^%d",i);
		}
		puts(" = 0");
	}
	return 0;
}
