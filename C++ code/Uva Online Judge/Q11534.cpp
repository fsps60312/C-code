#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int T,DP[101][4];
char S[101];
void buildDP()
{
	for(int i=0;i<4;i++)DP[0][i]=0,DP[1][i]=1;
	DP[1][3]=0;
	vector<int> sg;
	for(int l=2;l<=100;l++)
	{
		for(int s=0;s<4;s++)
		{
			sg.clear();
			for(int i=1;i<=l;i++)
			{
				sg.push_back(DP[i-1][s&2]^DP[l-i][s&1]);
				sg.push_back(DP[i-1][(s&2)+1]^DP[l-i][2+(s&1)]);
			}
			sort(sg.begin(),sg.end());
			int &dp=DP[l][s]=0;
			for(int i=0;i<sg.size();i++)
			{
				if(sg[i]==dp)dp++;
				else if(sg[i]>dp)break;
			}
		}
	}
}
int main()
{
	scanf("%d",&T);
	int ans;
	while(T--)
	{
		scanf("%s",S);
		ans=0;
		for(int i=0;S[i];i++)
		{
			
		}
	}
	return 0;
}
