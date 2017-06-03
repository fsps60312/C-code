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
bool can_idfy(int o,int v)
{
	int a=F[o]&v;
	for(int i=0;i<N;i++)
	{
		if(i==o)continue;
		if(a==(F[i]&v))return false;
	}
	return true;
}
int get_MIN(int o)
{
	int ans=INF;
	for(int i=0;i<(1<<M);i++)
	{
		if(can_idfy(o,i))
		{
			getmin(ans,countbits(i));
		}
	}
	return ans;
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
		int ans=0;
		for(int i=0;i<N;i++)
		{
			getmax(ans,get_MIN(i));
		}
		printf("%d\n",ans);
	}
}
