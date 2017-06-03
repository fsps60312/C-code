#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
using namespace std;
vector<int>LOCS[26];
int N;
char A[1000001],B[1000001];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	scanf("%s%s",A,B);
	for(int i=0;i<26;i++)LOCS[i].clear();
	for(int i=N-1;i>=0;i--)LOCS[A[i]-'A'].push_back(i);
	long long ans=0;
	for(int i=0;i<N;i++)ans+=abs(i-LOCS[B[i]-'A'].back()),LOCS[B[i]-'A'].pop_back();
	assert(ans%2==0);
	printf("%lld\n",ans/2);
	return 0;
}
