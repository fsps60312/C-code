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
map<int,int> colorcollect;
int tmp[200][200][200],T,n,Ssum;
int dp(int a,int b,int c)//from, to, 
{
	if(tmp[a][b][c]!=-1) return tmp[a][b][c];
	if(a==b) return tmp[a][b][c]=(c+S[b].sum)*(c+S[b].sum);
	tmp[a][b][c]=dp(a,b-1,0)+(c+S[b].sum)*(c+S[b].sum);
	for(int i=b-1;i>=a;i--)
	{
		if(S[i].color==S[b].color)
		{
			int j=dp(i+1,b-1,0)+dp(a,i,S[b].sum+c);
			if(j>tmp[a][b][c]) tmp[a][b][c]=j;
		}
	}
	return tmp[a][b][c];
}
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%d",&T);
	int t=1;
	while(T--)
	{
		scanf("%d",&n);
		colorcollect.clear();
		Ssum=0;
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
			else if(S[Ssum].color!=j)
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
		for(int i=0;i<=Ssum;i++)
		{
			for(int j=0;j<=Ssum;j++)
			{
				for(int k=0;k<=n;k++)
				{
					tmp[i][j][k]=-1;
				}
			}
		}
		printf("Case %d: %d\n",t++,dp(0,Ssum,0));
	}
	return 0;
}
