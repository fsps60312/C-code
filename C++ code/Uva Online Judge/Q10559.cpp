#include<cstdio>
#include<cstdlib>
#include<map>
using namespace std;
struct pairtype
{
	int type;
	int sum;
};
struct statetype
{
	int n;
	int rest;
};
int T,n,block;
pairtype S[200];
statetype state[200][200][200];//start, end, final color, 
map<int,int> colorcollect;
int max(int a,int b)
{
	return a>b?a:b;
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	for(int t=1;t<=T;t++)
	{
		scanf("%d",&n);
		colorcollect.clear();
		block=0;
		for(int i=0,j;i<n;i++)
		{
			scanf("%d",&j);
			if(colorcollect.find(j)==colorcollect.end())
			{
				colorcollect[j]=colorcollect.size()-1;
			}
			j=colorcollect[j];
			if(i==0)
			{
				S[0].sum=1;
				S[0].type=j;
			}
			else if(S[block].type!=j)
			{
				block++;
				S[block].sum=1;
				S[block].type=j;
			}
			else S[block].sum++;
		}
		printf(" %d\n",colorcollect.size());
		for(int k=0;k<colorcollect.size();k++)
		{
			for(int i=0;i<=block;i++)
			{
				for(int j=0;j<=block;j++)
				{
					state[i][j][k].n=state[i][j][k].rest=0;
				}
			}
		}
		for(int i=0;i<=block;i++)
		{
			state[i][i][S[i].type].n=S[i].sum*S[i].sum;
			state[i][i][S[i].type].rest=S[i].sum;
		}
		for(int i=1;i<=block;i++)
		{
			for(int j=0;j+i<=block;j++)
			{
				for(int k=0;k<colorcollect.size();k++)
				{
					if(state[j+1][j+i-1][k].n+S[j].sum*S[j].sum+S[j+i].sum*S[j+i].sum>state[j][j+i][k].n)
					{
						state[j][j+i][k].n=state[j+1][j+i-1][k].n+S[j].sum*S[j].sum+S[j+i].sum*S[j+i].sum;
						state[j][j+i][k].rest=state[j+1][j+i-1][k].rest;
					}
					if(state[j+1][j+i][k].n+S[j].sum*S[j].sum>state[j][j+i][k].n)
					{
						state[j][j+i][k].n=state[j+1][j+i][k].n+S[j].sum*S[j].sum;
						state[j][j+i][k].rest=state[j+1][j+i][k].rest;
					}
					if(state[j][j+i-1][k].n+S[j+i].sum*S[j+i].sum>state[j][j+i][k].n)
					{
						state[j][j+i][k].n=state[j][j+i-1][k].n+S[j+i].sum*S[j+i].sum;
						state[j][j+i][k].rest=state[j][j+i-1][k].rest;
					}
					if(S[j].type==S[j+i].type)
					{
						if(k==S[j].type)
						{
							statetype a=state[j][j+i][k];
							statetype b=state[j+1][j+i-1][k];
							int c=b.rest+S[j].sum+S[j+i].sum;
							if(b.n-b.rest*b.rest+c*c>a.n)
							{
								a.n=b.n-b.rest*b.rest+c*c;
								a.rest=c;
							}
						}
						else
						{
							statetype a=state[j][j+i][S[j].type];
							statetype b=state[j+1][j+i-1][k];
							int c=S[j].sum+S[j+i].sum;
							if(b.n+c*c>a.n)
							{
								a.n=b.n+c*c;
								a.rest=c;
							}
						}
					}
					else
					{
						if(k==S[j].type)
						{
							statetype a=state[j][j+i][S[j].type];
							statetype b=state[j+1][j+i-1][k];
							int c=b.rest+S[j].sum;
							if(b.n-b.rest*b.rest+c*c>a.n)
							{
								a.n=b.n-b.rest*b.rest+c*c;
								a.rest=c;
							}
						}
						else if(k==S[j+i].type)
						{
							statetype a=state[j][j+i][S[j+1].type];
							statetype b=state[j+1][j+i-1][k];
							int c=b.rest+S[j+i].sum;
							if(b.n-b.rest*b.rest+c*c>a.n)
							{
								a.n=b.n-b.rest*b.rest+c*c;
								a.rest=c;
							}
						}
						else
						{
							statetype a1=state[j][j+i][S[j].type];
							statetype a2=state[j][j+i][S[j+i].type];
							statetype b=state[j+1][j+i-1][k];
							if(b.n+S[j].sum*S[j].sum+S[j+i].sum*S[j+i].sum>a1.n)
							{
								a1.n=b.n+S[j].sum*S[j].sum+S[j+i].sum*S[j+i].sum;
								a1.rest=S[j].sum;
							}
							if(b.n+S[j].sum*S[j].sum+S[j+i].sum*S[j+i].sum>a2.n)
							{
								a2.n=b.n+S[j].sum*S[j].sum+S[j+i].sum*S[j+i].sum;
								a2.rest=S[j+i].sum;
							}
						}
					}
				}
			}
		}
		int ans=0;
		for(int i=0;i<colorcollect.size();i++) if(state[0][block][i].n>ans) ans=state[0][block][i].n;
		printf("Case %d: %d\n",t,ans);
	}
	return 0;
}
