#include<cstdio>
int N,BONE[24];
char STR[1000000];
void getmax(int &a,int b){if(b>a)a=b;}
int main()
{
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)
		{
			scanf("%s",STR);
			BONE[i]=0;
			for(int j=0;STR[j];j++)
			{
				BONE[i]^=1<<(STR[j]-'A');
			}
		}
		int ans=0;
		for(int i=0,v=0,cnt=0;i<(1<<N);i++,v=0,cnt=0)
		{
			for(int j=0;j<N;j++)if(i&(1<<j))v^=BONE[j],cnt++;
			if(!v)getmax(ans,cnt);
		}
		printf("%d\n",ans);
	}
	return 0;
}
