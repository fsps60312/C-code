#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<set>
#include<map>
using namespace std;
int SG[21][21];
int GetSG(const int row,const int col)
{
	int &ans=SG[row][col];
	if(ans!=-1)return ans;
	vector<int>s;
	for(int i=0;i<row;i++)for(int j=0;j<col;j++)
	{
		s.push_back(GetSG(i,j)^GetSG(i,col)^GetSG(row,j));
	}
	sort(s.begin(),s.end()),s.resize(unique(s.begin(),s.end())-s.begin());
	for(ans=0;ans<(int)s.size()&&s[ans]==ans;ans++);
	return ans;
}
int N,M;
multiset<int>ANS;
bool Solve(int K)
{
	vector<int>s;
	s.push_back(-1);
	for(int i=1;i<=N;i++)for(int j=1;j<=M;j++)s.push_back(GetSG(i,j));
	static bool dp[401][401][512],used[401][401][512];
	for(int i=0;i<=400;i++)for(int j=0;j<512;j++)dp[0][i][j]=false;
	dp[0][0][0]=true,used[0][0][0]=false;
	for(int idx=1;idx<(int)s.size();idx++)
	{
		for(int i=0;i<=400;i++)for(int j=0;j<512;j++)dp[idx][i][j]=false;
		for(int i=0;i<=400;i++)for(int j=0;j<512;j++)if(dp[idx-1][i][j])
		{
			dp[idx][i][j]=true,used[idx][i][j]=false;
			dp[idx][i+1][j^s[idx]]=true,used[idx][i+1][j^s[idx]]=true;
		}
	}
	assert(N*M==(int)s.size()-1);
	if(!dp[N*M][K][0])return false;
	ANS.clear();
	for(int cur=0,i=N*M;i>=0;i--)
	{
		if(used[i][K][cur])
		{
			ANS.insert(s[i]);
			cur^=s[i];
			K--;
		}
	}
	return true;
}
int K;
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=0;i<=20;i++)for(int j=0;j<=20;j++)SG[i][j]=0;
	for(int i=1;i<=20;i++)for(int j=1;j<=20;j++)SG[i][j]=-1;
//	for(int i=1;i<=20;i++)
//	{
//		for(int j=1;j<=20;j++)printf("%d ",GetSG(i,j));
//		puts("");
//	}
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d%d",&N,&M,&K);
		if(Solve(K))
		{
			puts("^v^;;");
			assert((int)ANS.size()==K);
			int check=0;
			for(int i=1;i<=N;i++)
			{
				for(int j=1;j<=M;j++)
				{
					const auto it=ANS.find(GetSG(i,j));
					if(it!=ANS.end()){ANS.erase(it);putchar('C');check^=GetSG(i,j);}
					else putchar('A');
				}
				puts("");
			}
			assert(ANS.empty());
			assert(check==0);
		}
		else puts("ko_ko_ko");
	}
	return 0;
}
