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
const int W=64;
unsigned long long CNT[2000][1999/16+1];
char ANS[2000][2001];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%s",EDGE[i]);
		const vector<int>&o=GetTopuOrder();
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<=(N-1)/32;j++)CNT[i][j]=0;
			CNT[i][i/W]|=1ULL<<(i%W);
			for(int j=0;j<N;j++)ANS[i][j]='0';
			ANS[i][N]='\0';
		}
		for(int i=1;i<N;i++)
		{
			for(int j=i-1;j>=0;j--)if((unsigned)(EDGE[o[j]][o[i]]-'0')!=((CNT[i][j/W]>>(j%W))&1))
			{
				ANS[o[j]][o[i]]='1';
				for(int k=j/W;k>=0;k--)CNT[i][k]^=CNT[j][k];
			}
		}
		for(int i=0;i<N;i++)puts(ANS[i]);
	}
	return 0;
}
