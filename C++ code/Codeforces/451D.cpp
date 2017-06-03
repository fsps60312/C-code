#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
LL NOW[8];
int Get(const int a,const int b,const int c){return (a<<2)+(b<<1)+(c<<0);}
int main()
{
	freopen("in.txt","r",stdin);
	char *str=new char[100001];
	while(scanf("%s",str)==1)
	{
		for(int i=0;i<8;i++)NOW[i]=0LL;
		for(int i=0;str[i];i++)
		{
			const int v=str[i]-'a';
			LL *nxt=new LL[8];
			for(int j=0;j<8;j++)nxt[j]=NOW[j];
			nxt[Get(1,v,v)]++;
			for(int d=0;d<2;d++)
			{
				nxt[Get(d,0,v)]+=NOW[Get(d^1,0,0)]+NOW[Get(d^1,0,1)];
				nxt[Get(d,1,v)]+=NOW[Get(d^1,1,0)]+NOW[Get(d^1,1,1)];
			}
			for(int j=0;j<8;j++)NOW[j]=nxt[j];
			delete[]nxt;
		}
		printf("%lld %lld\n",NOW[Get(0,0,0)]+NOW[Get(0,1,1)],NOW[Get(1,0,0)]+NOW[Get(1,1,1)]);
	}
	return 0;
}
