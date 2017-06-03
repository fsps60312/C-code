#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
int N,LIKE[2000000],DISH[2000000],LOC[2000000];
bool VIS[2000000];
vector<int>GAP;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf(1,"%d",&N);
	for(int i=0;i<N;i++)scanf(1,"%d",&LIKE[i]),LIKE[i]--;
	for(int i=0;i<N;i++)scanf(1,"%d",&DISH[i]),DISH[i]--,LOC[i]=-1;
	for(int i=0;i<N;i++)LOC[DISH[i]]=i,VIS[i]=false;
	for(int i=0;i<N;i++)VIS[(i+N-LOC[LIKE[i]])%N]=true,assert(LOC[i]!=-1);
	GAP.clear();GAP.push_back(0);
	for(int i=1,cnt=1;;i++)
	{
		if(i==N||VIS[i])
		{
			GAP.push_back(cnt);
			cnt=0;
			if(i==N)break;
		}
		cnt++;
	}
	int ans=INF;
//	for(const auto v:GAP)printf(" %d",v);puts("");
	for(int i=1;i<(int)GAP.size();i++)GAP[i]+=GAP[i-1];
	assert(GAP[(int)GAP.size()-1]==N);
	for(int i=1;i<(int)GAP.size();i++)getmin(ans,min(GAP[i-1],N-GAP[i])+GAP[i-1]+(N-GAP[i]));
	assert(ans!=INF);
	printf("%d\n",ans);
	return 0;
}
