#include<cstdio>
#include<cassert>
#include<set>
using namespace std;
typedef long long LL;
LL L,R;
set<LL>S;
int main()
{
	S.clear();
	for(LL v=0LL;;)
	{
		v=v*10LL+1LL;
		for(LL i=1LL;i<=9LL;i++)S.insert(v*i);//,printf("%lld\n",v*i);
		if(v==111111111111111111LL)break;
	}
    int testcount;scanf("%d",&testcount);
    while(testcount--)
    {
        scanf("%lld%lld",&L,&R);
        int ans=0;
        for(const LL &v:S)if(L<=v&&v<=R)ans++;
        printf("%d\n",ans);
    }
    return 0;
}
