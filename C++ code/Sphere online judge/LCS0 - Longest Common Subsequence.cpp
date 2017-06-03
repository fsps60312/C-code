#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<map>
#include<utility>
using namespace std;
const int INF=1147483647;
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
int Pre(const vector<int>&s,const int val)
{
	auto it=lower_bound(s.begin(),s.end(),val);
	if(it==s.begin())return -1;
	else return *--it;
}
char A[50000],B[50000];
vector<int>LOC_A[26],LOC_B[26];
map<pair<int,int>,int>DP;
int GetDP(const int ai,const int bi)
{
//	printf("(%d,%d)\n",ai,bi);
	if(ai==-1||bi==-1)return 0;
	assert(A[ai]==B[bi]);
	const pair<int,int>&p=make_pair(ai,bi);
	{const auto &it=DP.find(p);if(it!=DP.end())return it->second;}
	int ans=0;
	for(int i=0;i<26;i++)
	{
//		printf("i=%d(%d,%d)\n",i,Pre(LOC_A[i],ai),Pre(LOC_B[i],bi));
		getmax(ans,GetDP(Pre(LOC_A[i],ai),Pre(LOC_B[i],bi))+1);
	}
	return DP[p]=ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%s%s",A,B);
	for(int i=0;i<26;i++)LOC_A[i].clear(),LOC_B[i].clear();
	DP.clear();
	for(int i=0;A[i];i++)LOC_A[A[i]-'a'].push_back(i);
	for(int i=0;B[i];i++)LOC_B[B[i]-'a'].push_back(i);
	int ans=0;
	//printf(" (%d,%d)\n",Pre(LOC_A[i],INF),Pre(LOC_B[i],INF)),
	for(int i=0;i<26;i++)getmax(ans,GetDP(Pre(LOC_A[i],INF),Pre(LOC_B[i],INF)));
	printf("%d\n",ans);
	return 0;
}
