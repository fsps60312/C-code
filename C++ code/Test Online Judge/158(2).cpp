#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
using namespace std;
int N,M,K,A[100],B[100];
int DP[1001][101];
struct Pair
{
	int full,cnt;
	Pair(){}
	Pair(const int _f,const int _c):full(_f),cnt(_c){}
	bool operator<(const Pair &p)const{return cnt>p.cnt;}
};
vector<Pair>TMP;
void Update(const int full,const int cnt,const int content)
{
	assert(content>=0);
	if(full>M||cnt>K)return;
	if(DP[full][cnt]>=content)return;
	if(DP[full][cnt]==-1)TMP.push_back(Pair(full,cnt));
	DP[full][cnt]=content;
}
vector<Pair>REC;
void Move()
{
	for(int i=0;i<(int)TMP.size();i++)REC.push_back(TMP[i]);
	TMP.clear();
	sort(REC.begin(),REC.end());
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
		TMP.clear(),REC.clear();
		Update(0,0,0),Move();
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<(int)REC.size();j++)
			{
				const int full=REC[j].full,cnt=REC[j].cnt;
				Update(full+A[i],cnt+1,DP[full][cnt]+B[i]);
			}
			Move();
		}
		int ans=-1;
		for(int i=0;i<(int)REC.size();i++)
		{
			const int full=REC[i].full,cnt=REC[i].cnt;
			if(DP[full][cnt]>ans)ans=DP[full][cnt];
		}
		assert(ans!=-1);
		printf("%d\n",ans);
	}
	return 0;
}
