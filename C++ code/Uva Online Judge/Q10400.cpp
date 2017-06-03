#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
int N,TARGET,S[100];
bool VIS[100][64001];
bool Dfs(const int depth,vector<char>&ans,const int number)
{
	if(number<-32000||number>32000)return false;
	if(VIS[depth][number+32000])return false;
	VIS[depth][number+32000]=true;
	if(depth==N-1)
	{
		if(number==TARGET)
		{
			for(int i=0;i<N;i++)
			{
				if(i)putchar(ans[i-1]);
				printf("%d",S[i]);
			}
			printf("=%d\n",TARGET);
			return true;
		}
		else return false;
	}
	ans.push_back(' ');
	ans.back()='+';
	if(Dfs(depth+1,ans,number+S[depth+1]))return true;
	ans.back()='-';
	if(Dfs(depth+1,ans,number-S[depth+1]))return true;
	ans.back()='*';
	if(Dfs(depth+1,ans,number*S[depth+1]))return true;
	ans.back()='/';
	if(number%S[depth+1]==0&&Dfs(depth+1,ans,number/S[depth+1]))return true;
	ans.pop_back();
	return false;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		for(int i=0;i<N;i++)for(int j=0;j<=64000;j++)VIS[i][j]=false;
		vector<char>ans;
		scanf("%d",&TARGET);
		if(!Dfs(0,ans,S[0]))puts("NO EXPRESSION");
	}
	return 0;
}
