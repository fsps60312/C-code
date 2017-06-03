#include<cstdio>
int S[17][17][17];
int main()
{
	freopen("in.txt","r",stdin);
	for(int a=1;a<=16;a++)for(int b=1;b<=16;b++)for(int c=1;c<=16;c++)S[a][b][c]=0;
	for(int s=0;s<14348907;s++)
	{
		int cnt[3]={0,0,0};
		int a[16];
		for(int i=0,t=s;i<15;i++)a[i]=t%3,t/=3,++cnt[a[i]];
		bool valid=true;
		for(int i=1;i<15;i++)if(a[i]==a[i-1]){valid=false;break;}
		if(valid)++S[cnt[0]][cnt[1]][cnt[2]];
	}
	for(int a,b,c;scanf("%d%d%d",&a,&b,&c)==3;)printf("%d\n",S[a][b][c]);
	return 0;
}
