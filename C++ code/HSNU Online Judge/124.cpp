#include<cstdio>
#include<cassert>
#include<vector>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
int N,M,H[10001];
int DJ[10001],SZ[10001];
int Find(const int a){return DJ[a]==a?a:(DJ[a]=Find(DJ[a]));}
bool Merge(const int a,const int b,const int h)
{
	assert(H[a]-1==h);
	if(H[b]-1>h)return false;
	if(Find(a)==Find(b))return false;
	SZ[Find(b)]+=SZ[Find(a)],SZ[Find(a)]=0;
	DJ[Find(a)]=Find(b);
	return true;
}
vector<int>FLOOD[10000];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf(2,"%d%d",&N,&M);
	for(int i=0;i<=N*M;i++)DJ[i]=i,SZ[i]=1;SZ[N*M]=0;
	for(int i=0;i<10000;i++)FLOOD[i].clear();
	for(int i=0;i<N*M;i++)scanf(1,"%d",&H[i]),FLOOD[H[i]-1].push_back(i);
	H[N*M]=-1;
	int ans=0;
	for(int h=0,area=0;h<10000;h++)
	{
		for(const int i:FLOOD[h])
		{
			area++;
			const int r=i/M,c=i%M;
			Merge(i,r?(r-1)*M+c:N*M,h);
			Merge(i,r+1<N?(r+1)*M+c:N*M,h);
			Merge(i,c?r*M+(c-1):N*M,h);
			Merge(i,c+1<M?r*M+(c+1):N*M,h);
		}
		ans+=area-SZ[Find(N*M)];
//		printf("ans=%d\n",ans);
	}
	printf("%d\n",ans);
	return 0;
}
