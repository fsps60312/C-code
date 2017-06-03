#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
char S[100002];
LL NOW[100001][8];
int N;
int Get(const int a,const int b,const int c){return (a<<2)+(b<<1)+(c<<0);}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%s",S+1)==1)
	{
		for(int i=0;i<8;i++)NOW[0][i]=0LL;
		for(N=1;S[N];N++)
		{
			const int v=S[N]-'a';
			LL *nxt=NOW[N];
			for(int j=0;j<8;j++)nxt[j]=NOW[N-1][j];
			nxt[Get(1,v,v)]++;
			for(int d=0;d<2;d++)
			{
				nxt[Get(d,0,v)]+=NOW[N-1][Get(d^1,0,0)]+NOW[N-1][Get(d^1,0,1)];
				nxt[Get(d,1,v)]+=NOW[N-1][Get(d^1,1,0)]+NOW[N-1][Get(d^1,1,1)];
			}
		}
		N--;
		printf("%lld %lld\n",NOW[N][Get(0,0,0)]+NOW[N][Get(0,1,1)],NOW[N][Get(1,0,0)]+NOW[N][Get(1,1,1)]);
	}
	return 0;
}
