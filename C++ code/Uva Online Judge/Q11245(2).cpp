#include<cstdio>
#include<cassert>
#include<vector>
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
		static bool vis[10001];
		vector<int>s;
		for(int i=1;i<=1000;i++)
		{
			bool &valid=vis[i]=true;
			for(const int v:s)
			{
				bool fit=true;
				for(int j=2;j<P;j++)if(i-j*(i-v)<1||!vis[i-j*(i-v)]){fit=false;break;}
				if(fit){valid=false;break;}
			}
			if(valid)s.push_back(i);
		}
		for(int i=0;i<(int)s.size();i++)printf("%d\n",s[i]);
		set<int>all;
		for(int i=2*(P-1);i<(int)s.size();i+=2*(P-1))
		{
//			printf("%d\n",s[i]);
			const int dis=s[i]-s[i-2*(P-1)];
//			printf("%d\n",dis);
			all.insert(dis);
		}
		puts("");
		for(const int v:all)printf("%d ",v);puts("");
		puts("pass");
	}
	return 0;
}
