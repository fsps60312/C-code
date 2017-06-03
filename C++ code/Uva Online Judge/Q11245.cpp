#include<cstdio>
#include<cassert>
#include<set>
using namespace std;
typedef long long LL;
LL N;
int P;
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%lld%d",&N,&P);
		set<int>s;
		for(int i=1;i<=1000;i++)
		{
			bool valid=true;
			for(const int v:s)
			{
				bool fit=true;
				for(int j=2;j<P;j++)if(!s.count(i-j*(i-v))){fit=false;break;}
				if(fit){valid=false;break;}
			}
			if(valid)s.insert(i);
		}
		for(const int v:s)printf("%d\n",v);puts("");
	}
	return 0;
}
