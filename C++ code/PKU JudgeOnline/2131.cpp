#include<cstdio>
int N,M,S[131072],DJ[131072*2],ANS[131072];
int FindDJ(const int &a){return DJ[a]==a?a:(DJ[a]=FindDJ(DJ[a]));}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N+M;i++)DJ[i]=i;
		for(int i=0;i<N;i++)scanf("%d",&S[i]),S[i]--;
		for(int i=N-1;i>=0;i--)
		{
			int loc=FindDJ(S[i]);
			ANS[loc]=i+1;
			DJ[loc]=loc+1;
		}
		int ans=0;
		for(int i=0;i<N+M;i++)if(DJ[i]!=i)ans=i+1;
		printf("%d\n",ans);
		for(int i=0;i<ans;i++)
		{
			if(i)printf(" ");
			printf("%d",DJ[i]==i?0:ANS[i]);
		}
		puts("");
	}
	return 0;
}
