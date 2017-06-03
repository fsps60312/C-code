#include<cstdio>
const int INF=2147483647;
char SCANF[128][11];
int F[128],N,M;
void getmax(int &a,int b){if(b>a)a=b;}
void getmin(int &a,int b){if(b<a)a=b;}
int countbits(int a)
{
	a=((a&0xaaaaaaaa)>>1)+(a&0x55555555);
	a=((a&0xcccccccc)>>2)+(a&0x33333333);
	a=((a&0xf0f0f0f0)>>4)+(a&0x0f0f0f0f);
	a=((a&0xff00ff00)>>8)+(a&0x00ff00ff);
	a=((a&0xffff0000)>>16)+(a&(0x0000ffff));
	return a;
}
bool can_idfy(int v)
{
	for(int i=0;i<N;i++)
	{
		for(int j=i+1;j<N;j++)
		{
			if((F[i]&v)==(F[j]&v))return false;
		}
	}
	return true;
}
int main()
{
	//freopen("in.txt","r",stdin); 
	while(scanf("%d%d",&M,&N)==2&&(N||M))
	{
		for(int i=0;i<N;i++)
		{
			scanf("%s",SCANF[i]);
		}
		for(int i=0;i<N;i++)
		{
			F[i]=0;
			for(int j=0;j<M;j++)
			{
				if(SCANF[i][j]=='0')continue;
				F[i]|=(1<<j);
			}
		}
		int ans=INF;
		for(int v=0;v<(1<<M);v++)
		{
			if(can_idfy(v))
			{
				getmin(ans,countbits(v));
			}
		}
		printf("%d\n",ans);
	}
}
