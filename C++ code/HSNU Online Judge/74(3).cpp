#include<cstdio>
#include<set>
using namespace std;
typedef long long LL;
int N;
multiset<LL>S;
int main()
{
	scanf("%d",&N);
	LL ans=0LL;
	while(N--)
	{
		static int k;scanf("%d",&k);
		while(k--)
		{
			static LL v;scanf("%lld",&v);
			S.insert(v);
		}
		multiset<LL>::iterator it=S.end();
		it--;
		ans+=*it;
		S.erase(it);
		it=S.begin();
		ans-=*it;
		S.erase(it);
	}
	printf("%lld\n",ans);
	return 0;
}
