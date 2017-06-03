#include<cstdio>
#include<set>
#include<cassert>
#include<algorithm>
using namespace std;
int N;
set<int>LOSE[100000];
struct Pair
{
	int cnt,idx;
	bool operator<(const Pair &p)const{return cnt<p.cnt;}
}P[100000];
bool ISANS[100000];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)LOSE[i].clear();
	for(int i=0,cnt,v;i<N;i++)
	{
		scanf("%d",&cnt);
		while(cnt--)
		{
			scanf("%d",&v);
			v--;
			assert(v!=i&&LOSE[i].find(v)==LOSE[i].end());
			LOSE[v].insert(i);
		}
	}
	for(int i=0;i<N;i++)
	{
		Pair &p=P[i];
		p.idx=i;
		p.cnt=LOSE[i].size();
		ISANS[i]=true;
	}
	sort(P,P+N);
	int ans=N;
	for(int i=N-1;P[i].cnt==i&&i>=0;i--)ISANS[P[i].idx]=false,ans--;
	printf("%d",ans);
	int cnt=0;
	for(int i=0;i<N;i++)if(ISANS[i])printf(" %d",i+1),cnt++;
	assert(cnt==ans);
	puts("");
	return 0;
}
