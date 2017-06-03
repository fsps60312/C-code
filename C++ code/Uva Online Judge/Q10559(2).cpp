#include<cstdio>
#include<cstdlib>
#include<map>
using namespace std; 
struct pairtype
{
	int color;
	int sum;
};
pairtype S[200];
int Ssum,T,n;
map<int,int> colorcollect;
int tmp[200][200][200];//from, to, last clicked length(color is S[j].color)
int Max[200][200];
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		colorcollect.clear();
		Ssum=0;
		scanf("%d",&n);
		for(int i=0,j;i<n;i++)
		{
			scanf("%d",&j);
			if(colorcollect.find(j)==colorcollect.end()) colorcollect[j]=colorcollect.size()-1;
			j=colorcollect[j];
			if(i==0)
			{
				S[0].color=j;
				S[0].sum=1;
			}
			else
			{
				if(j!=S[Ssum].color)
				{
					Ssum++;
					S[Ssum].color=j;
					S[Ssum].sum=1;
				}
				else
				{
					S[Ssum].sum++;
				}
			}
		}
		for(int i=0;i<=Ssum;i++)
		{
			for(int j=0;j<=Ssum;j++)
			{
				for(int k=0;k<=n;k++)
				{
					tmp[i][j][k]=0;
				}
				Max[i][j]=0;
			}
		}
		for(int i=0;i<=Ssum;i++)
		{
			tmp[i][i][S[i].sum]=Max[i][i]=S[i].sum*S[i].sum;
		}
		for(int i=1;i<=Ssum;i++)
		{
			for(int j=0;j+i<=Ssum;j++)
			{
				for(int k=j+i-1;k>=j;k--)
				{
					if(S[k].color==S[j+i].color)
					{
						for(int l=1;l<=n;l++)
						{
							if(tmp[j][k][l]>0)
							{
								int m=l+S[j+i].sum;
								int o=tmp[j][k][l]-l*l+m*m;
								if(k+1<=j+i-1) o+=Max[k+1][j+i-1];
								if(o>tmp[j][j+i][m])
								{
									tmp[j][j+i][m]=o;
									if(tmp[j][j+i][m]>Max[j][j+i]) Max[j][j+i]=tmp[j][j+i][m];
								}
							}
						}
					}
					else
					{
						for(int l=1;l<=n;l++)
						{
							if(tmp[j][k][l]>0)
							{
								if(tmp[j][k][l]+S[j+i].sum*S[j+i].sum>tmp[j][j+i][S[j+i].sum])
								{
									tmp[j][j+i][S[j+i].sum]=tmp[j][k][l]+S[j+i].sum*S[j+i].sum;
									if(tmp[j][j+i][S[j+i].sum]>Max[j][j+i]) Max[j][j+i]=tmp[j][j+i][S[j+i].sum];
								}
							}
						}
					}
				}
			}
		}
		printf("%d\n",Max[0][Ssum]);
	}
	return 0;
}
