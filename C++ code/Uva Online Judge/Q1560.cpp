#include<cstdio>
int T,M[7][8],ANS[6];
void push(int i,int j)
{
	i++,j++;
	M[i][j]^=1;
	M[i-1][j]^=1;
	M[i+1][j]^=1;
	M[i][j-1]^=1;
	M[i][j+1]^=1;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	int kase=1;
	while(T--)
	{
		for(int i=1,j;i<=5;i++)
		for(j=1;j<=6;j++)scanf("%d",&M[i][j]);
//		puts("a");
		for(int i=(1<<5)-1;i>=0;i--)
		{
			ANS[0]=i;
			for(int k=0;k<5;k++)
			{
				if(ANS[0]&(1<<k))push(k,0);
			}
			for(int j=1;j<6;j++)
			{
				int &ans=ANS[j]=0;
				for(int k=0;k<5;k++)
				{
					if(M[k+1][j])
					{
						push(k,j);
						ans|=1<<k;
					}
				}
			}
			bool found=true;
			for(int k=1;k<=5;k++)if(M[k][6]==1){found=false;break;}
			if(found)break;
			for(int j=0;j<6;j++)
			{
				for(int k=0;k<5;k++)
				{
					if(ANS[j]&(1<<k))push(k,j);
				}
			}
		}
//		puts("b");
		for(int i=0;i<6;i++)
		{
			for(int j=0;j<5;j++)
			{
				M[j][i]=ANS[i]&(1<<j)?1:0;
			}
		}
		printf("PUZZLE #%d\n",kase++);
		for(int i=0;i<5;i++)
		{
			for(int j=0;j<6;j++)
			{
				if(j)printf(" ");
				printf("%d",M[i][j]);
			}
			puts("");
		}
	}
	return 0;
}
