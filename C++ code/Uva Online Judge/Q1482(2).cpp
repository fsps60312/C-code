#include<cstdio>
#include<vector>
typedef long long LL;
using namespace std;
int T,N;
LL P,SG;
LL getSG(LL v)
{
	if(v&1LL)return getSG(v>>=1);
	else return v>>=1;
}
int main()
{
//	int sg[101],vis[100];sg[1]=0;
//	for(int i=2;i<=100;i++)
//	{
//		for(int j=0;j<100;j++)vis[j]=0;
//		for(int j=(i+1)/2;j<i;j++)vis[sg[j]]=1;
//		sg[i]=0;while(vis[sg[i]])sg[i]++;
//	}
//	for(int i=1;i<=100;i++)printf("%d:%d\n",i,sg[i]);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		SG=0LL;
		for(int i=0;i<N;i++)
		{
			scanf("%lld",&P);
			SG^=getSG(P);
		}
		printf(SG?"YES\n":"NO\n");
	}
	return 0;
}
