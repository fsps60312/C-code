#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
int N,M,K,A[100],B[100];
int DP[1001][101];
vector<int>TMPX,TMPY;
void Update(const int full,const int cnt,const int content)
{
	assert(content>=0);
	if(full>M||cnt>K)return;
	if(DP[full][cnt]>=content)return;
	if(DP[full][cnt]==-1)TMPX.push_back(full),TMPY.push_back(cnt);
	DP[full][cnt]=content;
}
vector<int>RECX,RECY;
void Move()
{
	assert(TMPX.size()==TMPY.size());
	for(int i=0;i<(int)TMPX.size();i++)RECX.push_back(TMPX[i]),RECY.push_back(TMPY[i]);
	TMPX.clear(),TMPY.clear();
}
int main()
{
//	freopen("in.txt","r",stdin);
	static int casecount;scanf("%d",&casecount);
	while(casecount--)
	{
		scanf("%d%d%d",&N,&M,&K);
		for(int i=0;i<N;i++)scanf("%d%d",&A[i],&B[i]);
		for(int i=0;i<=M;i++)for(int j=0;j<=K;j++)DP[i][j]=-1;
		TMPX.clear(),TMPY.clear(),RECX.clear(),RECY.clear();
		Update(0,0,0),Move();
		for(int i=0;i<N;i++)
		{
			assert(RECX.size()==RECY.size());
			for(int j=0;j<(int)RECX.size();j++)
			{
				const int full=RECX[j],cnt=RECY[j];
				Update(full+A[i],cnt+1,DP[full][cnt]+B[i]);
			}
			Move();
		}
		int ans=-1;
		for(int i=0;i<(int)RECX.size();i++)
		{
			const int full=RECX[i],cnt=RECY[i];
			if(DP[full][cnt]>ans)ans=DP[full][cnt];
		}
		assert(ans!=-1);
		printf("%d\n",ans);
	}
	return 0;
}
