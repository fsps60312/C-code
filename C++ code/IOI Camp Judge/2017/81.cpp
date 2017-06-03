#include<cstdio>
#include<cassert>
#include<queue>
#include<vector>
using namespace std;
int N;
char EDGE[2000][2001];
vector<int>GetTopuOrder()
{
	static int cnt[2000];
	for(int i=0;i<N;i++)cnt[i]=0;
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)if(i!=j&&EDGE[i][j]=='1')++cnt[j];
	vector<int>ans;
	queue<int>q;
	for(int i=0;i<N;i++)if(cnt[i]==0)q.push(i);
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		ans.push_back(u);
		for(int i=0;i<N;i++)if(EDGE[u][i]=='1'&&!--cnt[i])q.push(i);
	}
	assert((int)ans.size()==N);
	return ans;
}
int CNT[2000][2000];
char ANS[2000][2001];
int main()
{
	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%s",EDGE[i]);
		const vector<int>&o=GetTopuOrder();
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)CNT[i][j]=(i==j?1:0),ANS[i][j]='0';
			ANS[i][N]='\0';
		}
		for(int i=1;i<N;i++)
		{
			for(int j=i-1;j>=0;j--)if(EDGE[o[j]][o[i]]-'0'!=CNT[j][i])
			{
				ANS[o[j]][o[i]]='1';
				for(int k=j;k>=0;k--)CNT[k][i]^=CNT[k][j];
			}
		}
		for(int i=0;i<N;i++)puts(ANS[i]);
	}
	return 0;
}
