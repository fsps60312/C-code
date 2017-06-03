#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int T,DP[101][3][3];
char S[101];
void buildDP()
{
	for(int i=0;i<9;i++)DP[0][i/3][i%3]=0,DP[1][i/3][i%3]=1;
	DP[0][1][2]=DP[0][2][1]=1;
	DP[1][1][2]=DP[1][2][1]=0;
	vector<int> sg;
	for(int len=2;len<=100;len++)
	{
		for(int l=0;l<=2;l++)
		{
			for(int r=0;r<=2;r++)
			{
				sg.clear();
				for(int i=1;i<=len;i++)
				{
					if(i==1)
					{
						if(l!=1)sg.push_back(DP[len-i][1][r]);
						if(l!=2)sg.push_back(DP[len-i][2][r]);
					}
					else if(i==len)
					{
						if(r!=1)sg.push_back(DP[i-1][l][1]);
						if(r!=2)sg.push_back(DP[i-1][l][2]);
					}
					else
					{
						sg.push_back(DP[i-1][l][1]^DP[len-i][1][r]);
						sg.push_back(DP[i-1][l][2]^DP[len-i][2][r]);
					}
				}
				sort(sg.begin(),sg.end());
				int &dp=DP[len][l][r]=0;
				for(int i=0;i<sg.size();i++)
				{
					if(sg[i]==dp)dp++;
					else if(sg[i]>dp)break;
				}
//				if(len<=5)printf("dp(%d,%d,%d) => %d\n",len,l,r,dp);
			}
		}
	}
}
int getSG(char *s,int &l,int &i)
{
	int j=i,r;while(s[j]=='.')j++;
	if(s[j]=='O')r=1;
	else if(s[j]=='X')r=2;
	else r=0;//s[i]==0
	int ans=DP[j-i][l][r];
//	printf("%d %d %d => %d\n",j-i,l,r,ans);
	l=r,i=j-1;
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	buildDP();
	scanf("%d",&T);
	int ans;
	while(T--)
	{
		scanf("%s",S);
		ans=0;
		int cnt=0;
		for(int i=0,l=0;S[i];i++)
		{
			switch(S[i])
			{
				case'O':l=1,cnt++;break;
				case'X':l=2,cnt++;break;
				case'.':ans^=getSG(S,l,i);break;
			}
		}
		if(cnt&1)ans=ans?0:1;
		printf(ans?"Possible.\n":"Impossible.\n");
	}
	return 0;
}
