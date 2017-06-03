#include<cstdio>
const int INF=2147483647;
char SCANF[128][11];
int F[128],N,M;
void getmax(int &a,int b){if(b>a)a=b;}
void getmin(int &a,int b){if(b<a)a=b;}
int max(int a,int b){return a>b?a:b;}
int countbits(int a)
{
	a=((a&0xaaaaaaaa)>>1)+(a&0x55555555);
	a=((a&0xcccccccc)>>2)+(a&0x33333333);
	a=((a&0xf0f0f0f0)>>4)+(a&0x0f0f0f0f);
	a=((a&0xff00ff00)>>8)+(a&0x00ff00ff);
	a=((a&0xffff0000)>>16)+(a&(0x0000ffff));
	return a;
}
int DP[1<<11][1<<11];
int get_ANS(int q,int id)
{
	int &ans=DP[q][id];
	if(ans!=INF)return ans;
	int rep=0;
	for(int i=0;i<N;i++)
	{
		if((F[i]&q)==id)rep++;
	}
	if(rep<=1)return ans=0;
	for(int i=0,j=1;i<M;i++,j<<=1)
	{
		if(j&q)continue;
		getmin(ans,max(get_ANS(q|j,id),get_ANS(q|j,id|j))+1);
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
		for(int i=0;i<(1<<M);i++)
		{
			for(int j=0;j<(1<<M);j++)
			{
				DP[i][j]=INF;
			}
		}
		int ans=get_ANS(0,0);
		printf("%d\n",ans);
	}
}
