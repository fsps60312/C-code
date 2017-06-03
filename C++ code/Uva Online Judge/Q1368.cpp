#include<bits/stdc++.h>
using namespace std;
//ATCG
int T,N,M,CNT[1000][4];
char ANS[1001],CHAR[4]={'A','C','G','T'};
int ID[256];
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=0;i<256;i++)ID[i]=-1;
	ID['A']=0,ID['C']=1,ID['G']=2,ID['T']=3;
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			scanf("%d%d",&N,&M);
			for(int i=0;i<M;i++)for(int j=0;j<4;j++)CNT[i][j]=0;
			for(int i=0;i<N;i++)
			{
				for(int j=0;j<M;j++)
				{
					static char c;
					do{scanf("%c",&c);}while(ID[c]==-1);
					CNT[j][ID[c]]++;
				}
			}
			int ans=0;
			for(int i=0;i<M;i++)
			{
				static int idx;idx=3;
				for(int j=2;j>=0;j--)if(CNT[i][j]>=CNT[i][idx])idx=j;
				ans+=N-CNT[i][idx];
				ANS[i]=CHAR[idx];
			}
			ANS[M]='\0';
			printf("%s\n%d\n",ANS,ans);
		}
	}
	return 0;
}
