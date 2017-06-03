#include<cstdio>
#include<cstdlib>
int T,n,K;
char S[2001];
int A[2001][30][30];
int exist[2001][30];
int chunk[2001];
int main()
{
	//printf("%d\n",'z'-'a');
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%s",&K,S);
		n=0;
		for(int i=0;S[i];n++,i+=K)
		{
			for(int j=0;j<26;j++) exist[n][j]=0;
			chunk[n]=0;
			for(int j=0;j<K;j++)
			{
			    if(!exist[n][S[i+j]-'a']) chunk[n]++;
				exist[n][S[i+j]-'a']++;
			}
		}
		for(int i=0;i<n;i++)
        {
            for(int j=0;j<26;j++)
            {
                for(int k=0;k<26;k++)
                {
                    A[i][j][k]=1147483647;
                }
            }
        }
		for(int i=0;i<26;i++)
		{
			if(exist[0][i])
            {
                for(int j=0;j<26;j++)
                {
                    A[0][i][j]=chunk[0];
                }
            }
		}
		for(int m=1;m<n;m++)
        {
            for(int i=0;i<26;i++)
            {
                if(exist[m][i])
                {
                    for(int j=0;j<26;j++)
                    {
                        if(exist[m-1][j])
                        {
                            if(i==j)//head and tail is same
                            {
                                if(exist[m][i]>1&&chunk[m-1]>1)//divide to two
                                {
                                    for(int k=0;k<26;k++)
                                    {
                                        if(A[m][i][j]>A[m-1][j][k]+chunk[m])
                                        {
                                            A[m][i][j]=A[m-1][j][k]+chunk[m];
                                        }
                                    }
                                }
                                else if(chunk[m]==1||K==1)//all the same
                                {
                                    for(int k=0;k<26;k++)
                                    {
                                        if(A[m][i][j]>A[m-1][j][k])
                                        {
                                            A[m][i][j]=A[m-1][j][k];
                                        }
                                    }
                                }
                                //else impossible
                            }//head and tail is different
                            else if(exist[m][j])//can merge with former
                            {
                                for(int k=0;k<26;k++)
                                {
                                    if(A[m][i][j]>A[m-1][j][k]+chunk[m]-1)
                                    {
                                        A[m][i][j]=A[m-1][j][k]+chunk[m]-1;
                                    }
                                }
                            }
                            else//totally different
                            {
                                for(int k=0;k<26;k++)
                                {
                                    if(A[m][i][j]>A[m-1][j][k]+chunk[m])
                                    {
                                        A[m][i][j]=A[m-1][j][k]+chunk[m];
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
		int ans=1147483647;
		for(int i=0;i<26;i++)
        {
            for(int j=0;j<26;j++)
            {
                if(A[n-1][i][j]<ans) ans=A[n-1][i][j];
            }
        }
		printf("%d\n",ans);
	}
	return 0;
}
