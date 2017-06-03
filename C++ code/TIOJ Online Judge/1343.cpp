#include<cstdio>
#include<cassert>
#include<utility>
#include<algorithm>
#include<vector>
#include<set>
using namespace std;
typedef long long LL;
int N;
vector<pair<int,int> >MASTS;
multiset<int>STAIR;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	MASTS.clear();
	for(int i=0,h,k;i<N;i++)scanf("%d%d",&h,&k),MASTS.push_back(make_pair(h,k));
	sort(MASTS.begin(),MASTS.end());
	STAIR.clear(),STAIR.insert(0);
	for(int i=0;i<N;i++)
	{
		const int h=MASTS[i].first,k=MASTS[i].second;
		assert(0<k&&k<=h);
		multiset<int>::iterator it=STAIR.lower_bound(h);it--;
		if(it==STAIR.begin())STAIR.insert(k);
		else if(h-k>=(*it))
		{
			const int r=(*it)+k;
			if(it!=STAIR.begin())STAIR.erase(it);
			STAIR.insert(r);
		}
		else
		{
			STAIR.insert(h);
			it=STAIR.upper_bound(h-k);
			const int r=(*it);
			STAIR.erase(it--);
			assert((*it)<r);
			STAIR.insert((*it)+(r-(h-k)));
			if(it!=STAIR.begin())STAIR.erase(it);
		}
//		for(multiset<int>::iterator iu=STAIR.begin();iu!=STAIR.end();iu++)printf("%d ",*iu);puts("");
	}
	LL ans=0;
	multiset<int>::iterator it=STAIR.end();it--;
	LL thick=0;
	for(int h=MASTS[N-1].first;h>0;h--)
	{
		while((*it)==h)it--,thick++;
		ans+=thick*(thick-1)/2;
	}
	printf("%lld\n",ans);
	return 0;
}
