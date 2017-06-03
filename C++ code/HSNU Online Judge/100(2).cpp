#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
#include<queue> 
using namespace std;
int N;
vector<int>WIN[100000];
struct Dj
{
	int dj[100000];
	void clear(){for(int i=0;i<N;i++)dj[i]=i;}
	int find(const int a){return dj[a]==a?a:(dj[a]=find(dj[a]));}
	bool Merge(const int a,const int b){if(find(a)==find(b))return false;dj[find(a)]=find(b);return true;}
}DJ;
void Solve()
{
	for(int i=0;i<N;i++)ANS[i]=true;
	int cnt=N;
	for(int i=0;i<N;i++)for(int j=0;j<WIN[i].size();j++)if(DJ.Merge(i,WIN[i][j]))cnt--;
	if(cnt>1)return;
	
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)WIN[i].clear();
	DJ.clear();
	for(int i=0,cnt,v;i<N;i++)
	{
		scanf("%d",&cnt);
		while(cnt--)
		{
			scanf("%d",&v);
			v--;
			WIN[i].push_back(v);
		}
	}
	Solve();
	int ans=0;
	for(int i=0;i<N;i++)if(ANS[i])ans++;
	printf("%d",ans);
	for(int i=0;i<N;i++)if(ANS[i])printf(" %d",i+1);
	puts("");
	return 0;
}
