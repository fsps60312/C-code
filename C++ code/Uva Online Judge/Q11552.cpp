#include<cstdio>
#include<cstdlib>
int T,K;
char S[1001];
int state[1000][26][26];//knob, first letter, last letter
int exist[1000][26];
int chunk[1000];
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%s",&K,S);
		int n=-1;
		while(S[++n]);
		if(K==1)
		{
			int ans=n;
			for(int i=1;i<n;i++)
			{
				if(S[i]==S[i-1]) ans--;
			}
			printf("%d\n",ans);
			continue;
		}
		if(n%K!=0)
		{
			printf("error\n");
			break;
		}
		n/=K;
		for(int i=0;i<n;i++)
		{
			chunk[i]=0;
			for(int j=0;j<26;j++)
			{
				exist[i][j]=0;
				for(int k=0;k<26;k++)
				{
					state[i][j][k]=1100000000;
				}
			}
			for(int j=0;j<K;j++)
			{
				if(!exist[i][S[i*K+j]-'a']) chunk[i]++;
				exist[i][S[i*K+j]-'a']++;
				//printf("%d ",i*K+j);
			}
		}
		//for(int i=0;i<n;i++) printf(" %d",chunk[i]);printf("\n");
		for(int i=0;i<26;i++)
		{
			for(int j=0;j<26;j++)
			{
				if(exist[0][i]&&exist[0][j])
				{
					int k;
					if(i!=j||chunk[0]==1) k=chunk[0];
					else if(exist[0][i]==1) continue;
					else k=chunk[0]+1;
					if(k<state[0][i][j]) state[0][i][j]=k;
				}
			}
		}
		for(int k=1;k<n;k++)
		{
			for(int i=0;i<26;i++)
			{
				for(int j=0;j<26;j++)
				{
					if(exist[k][i]&&exist[k][j])
					{
						if(i==j&&exist[k][i]==1) continue;
						int l;
						if(i!=j||chunk[k]==1) l=chunk[k];
						else l=chunk[k]+1;
						for(int i0=0;i0<26;i0++)
						{
							for(int j0=0;j0<26;j0++)
							{
								//state[k-1][i0][j0]
								//state[k][i][j0] -> depend on j and i0
								if(exist[k-1][i0]&&exist[0][j0])
								{
									int l0;
									if(j==i0) l0=state[k-1][i0][j0]+l-1;
									else l0=state[k-1][i0][j0]+l;
									//printf(" %d\n",l0);
									if(l0<state[k][i][j0]) state[k][i][j0]=l0;
								}
							}
						}
					}
				}
			}
		}
		int ans=1100000000;
		for(int i=0;i<26;i++)
		{
			for(int j=0;j<26;j++)
			{
				if(state[n-1][i][j]<ans) ans=state[n-1][i][j];
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
