#include<cstdio>
#include<cassert>
#include<algorithm>
#include<map>
using namespace std;
void getmax(int &a,const int b){if(a<b)a=b;}
int N,S[1000];
map<int,int>COUNTS,WEIGHTS;
void Add(const int cnt,const int weight)
{
	COUNTS[weight]=cnt;
	WEIGHTS[cnt]=weight;
}
void Remove(const int cnt,const int weight)
{
	COUNTS.erase(weight);
	WEIGHTS.erase(cnt);
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%d",&S[i]);
	sort(S,S+N);
	COUNTS.clear(),WEIGHTS.clear();
	for(int i=0;i<N;i++)
	{
		auto it=COUNTS.upper_bound(S[i]-1);
		int cnt,weight;
		if(it!=COUNTS.begin())--it,cnt=it->second+1,weight=it->first+S[i];
		else cnt=1,weight=S[i];
//		printf("S[%d]=%d,cnt=%d,weight=%d\n",i,S[i],cnt,weight);
		it=WEIGHTS.lower_bound(cnt);
		if(it!=WEIGHTS.end()&&it->second<=weight)continue;
		it=WEIGHTS.upper_bound(cnt);
		if(it!=WEIGHTS.begin())
		{
			--it;
			for(;weight<=it->second;--it)
			{
				Remove(it->first,it->second);
				if(it==WEIGHTS.begin())break;
			}
		}
		Add(cnt,weight);
//		printf("size=%d\n",(int)COUNTS.size());
	}
	printf("%d\n",WEIGHTS.rbegin()->first);
	return 0;
}
