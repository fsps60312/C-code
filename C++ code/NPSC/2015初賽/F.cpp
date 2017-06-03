#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
vector<LL>S;
LL N,LIMIT,CNT;
bool Valid(char *c)
{
	for(int i=0;c[i];i++)if(c[i]>='a'&&c[i]<='z')return false;
	return true;
}
int main()
{
	while(scanf("%lld",&N)==1)
	{
		S.clear();
		scanf("%lld%lld",&LIMIT,&CNT);
		for(LL i=0LL,v;i<N;i++)
		{
			static char tmp[1000];
			scanf("%s",tmp);
			if(!Valid(tmp))continue;
			sscanf(tmp,"%lld",&v),S.push_back(v);
		}
		sort(S.begin(),S.end(),greater<LL>());
		LL ans=0LL;
		for(int i=0;i<S.size()&&i<CNT&&S[i]>=LIMIT;i++)ans+=S[i];
		printf("%lld\n",ans);
	}
	return 0;
}
