#include<cstdio>
#define LL long long
const LL MOD=1000000003;
int N,K,MX,V[50];
void getmax(int &a,int b){if(b>a)a=b;}
int main()
{
	while(scanf("%d%d",&N,&K)==2&&(N||K))
	{
		MX=0;
		for(int i=0;i<N;i++)
		{
			scanf("%d",V+i);
			getmax(MX,V[i]);
		}
		for(int i=0,j,d=1,v=0,tmp=0,cnt=0;i<31&&d<=MX;i++,d<<=1,v=0,tmp=0,cnt=0)
		{
			for(j=0;j<N;j++)if(d&V[i])cnt++;
			if(((cnt&1)==0)^((d&K)==0))j=cnt-1;
			else j=cnt;
			for(;j>=0;j-=2)
		}
		printf("%lld\n",ans);
	}
	return 0;
}
