#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
int N,M;
vector<int>S;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	S.clear();
	for(int i=0,v;i<N;i++)scanf("%d",&v),S.push_back(v);
	sort(S.begin(),S.end()),S.resize(unique(S.begin(),S.end())-S.begin());
	scanf("%d",&M);
	for(int i=0,v;i<M;i++)scanf("%d\n",&v),printf("%d\n",(int)(S.size()-(upper_bound(S.begin(),S.end(),v)-S.begin())+1));
	return 0;
}
