#include<cstdio>
#include<map>
#include<vector>
#include<cassert>
using namespace std;
typedef long long LL;
int N,S[100000],DP[100000];
map<int,LL>ANS[100000];
LL GetCost(const int len,const int v)
{
	if(len==-1)return 0LL;
	auto it=ANS[len].lower_bound(v);
	assert(it!=ANS[len].begin());
	return (--it)->second;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%d",&S[i]);
	for(int i=0;i<N;i++)ANS[i].clear();
	int len=0;
	for(int i=0;i<N;i++)
	{
		int l=0,r=len;
		while(l<r)
		{
			const int mid=(l+r)/2;
			if(DP[mid]<S[i])l=mid+1;
			else r=mid;
		}
		DP[r]=S[i];
		if(r==len)len++;
//		printf("i=%d,r=%d,len=%d\n",i,r,len);
		const LL cost=GetCost(r-1,S[i])+(i+1LL);
		auto it=ANS[r].upper_bound(S[i]);
		if(it==ANS[r].begin()||((--it)->second)>cost)
		{
			it=ANS[r].lower_bound(S[i]);
			vector<map<int,LL>::iterator>to_erase; 
			while(it!=ANS[r].end()&&(it->second)>=cost)to_erase.push_back(it++);
			for(const auto &v:to_erase)ANS[r].erase(v);
			ANS[r][S[i]]=cost;
		}
	}
//	printf("len=%d\n",len);
	auto it=ANS[len-1].end();it--;
	printf("%lld\n",it->second);
	return 0;
}
