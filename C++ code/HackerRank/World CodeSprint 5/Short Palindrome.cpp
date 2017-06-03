#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
const long long MOD=1000000007;
char S[1000001];
vector<int>LOC[26];
long long Solve(const int a,const int b)
{
	static long long lsum[1000000],rsum[1000000];
	for(int i=0,j=0;i<(int)LOC[a].size();i++)
	{
		lsum[i]=(i==0?j:lsum[i-1]+j);
		while(j<(int)LOC[b].size()&&LOC[b][j]<LOC[a][i])++j,++lsum[i];
	}
	long long ans=0;
	for(int i=(int)LOC[a].size()-1,j=0;i>=1;i--)
	{
		rsum[i]=(i==(int)LOC[a].size()-1?j:rsum[i+1]+j);
		while(j<(int)LOC[b].size()&&LOC[b][LOC[b].size()-1-j]>LOC[a][i])++j,++rsum[i];
//		if(rsum[i]*lsum[i-1])printf("c=(%c,%c), %lld*%lld\n",'a'+a,'a'+b,rsum[i],lsum[i-1]);
		(ans+=rsum[i]*lsum[i-1])%=MOD;
	}
	return ans;
}
long long C4(const long long v)
{
	vector<long long>s;
	for(int i=0;i<4;i++)s.push_back(v-i);
	for(int i=4;i>=2;i--)
	{
		bool found=false;
		for(int j=3;j>=0;j--)if(s[j]%i==0)
		{
			s[j]/=i;
			found=true;
			break;
		}
		assert(found);
	}
	long long ans=1;
	for(int i=0;i<4;i++)(ans*=s[i])%=MOD;
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%s",S)==1)
	{
		for(int i=0;i<26;i++)LOC[i].clear();
		for(int i=0;S[i];i++)LOC[S[i]-'a'].push_back(i);
		long long ans=0;
		for(int i=0;i<26;i++)
		{
			for(int j=0;j<26;j++)if(i!=j)(ans+=Solve(i,j))%=MOD;
			(ans+=C4((long long)LOC[i].size()))%=MOD;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
