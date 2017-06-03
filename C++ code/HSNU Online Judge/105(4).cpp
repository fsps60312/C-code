#include<cstdio>
#include<vector>
using namespace std;
typedef long long LL;
int T,N,A,B,C;
LL F[5000];
LL GetF(const LL u){return A*u*u+B*u+C;}
LL Gcd(const LL a,const LL b){return b==0LL?a:Gcd(b,a%b);}
int DJ[5000];
int Find(const int a){return DJ[a]==a?a:(DJ[a]=Find(DJ[a]));}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d%d",&N,&A,&B,&C);
		for(int i=0;i<N;i++)DJ[i]=i,F[i]=GetF(i);
		int ans=N;
		for(int i=0,a,b;i<N;i++)
		{
			for(int j=i+1;j<N;j++)if((a=Find(i))!=(b=Find(j))&&Gcd(F[i],F[j])==1LL)ans--,DJ[a]=b;
		}
		printf("%d\n",ans);
	}
	return 0;
}
