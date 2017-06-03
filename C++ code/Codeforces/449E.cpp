#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
int Gcd(const int a,const int b){return b==0?a:Gcd(b,a%b);}
int N,M;
int main()
{
	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		int ans=0;
		for(int len=1;len<=min(N,M);len++)
		{
			int ta=0;
			for(int i=0;i<len;i++)
			{
				const int on_diagonal=len-Gcd(i,len-i);
				const int in_triangle=(i*(len-i)+on_diagonal)/2;
				ta+=len*len-4*in_triangle;
			}
			ans+=ta*(N-len+1)*(M-len+1);
		}
		printf("%d\n",ans);
	}
	return 0;
}
