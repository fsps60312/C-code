#include<cstdio>
#include<cassert>
#include<algorithm>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
void getmax(int &a,const int b){if(b>a)a=b;}
int N,LIKE[2000000],DISH[2000000],LEFT[2000000],RIGHT[2000000];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf(1,"%d",&N);
	for(int i=0;i<N;i++)scanf(1,"%d",&LIKE[i]),LIKE[i]--;
	for(int i=0;i<N;i++)scanf(1,"%d",&DISH[i]),DISH[i]--;
	if(1)
	{
		static int tmp[2000000];
		for(int i=0;i<N;i++)tmp[DISH[i]]=i;
		for(int i=0;i<N;i++)tmp[DISH[i]]=i,RIGHT[i]=(i+N-tmp[LIKE[i]])%N;
		for(int i=N-1;i>=0;i--)tmp[DISH[i]]=i;
		for(int i=N-1;i>=0;i--)tmp[DISH[i]]=i,LEFT[i]=(tmp[LIKE[i]]+N-i)%N;
	}
	static int right[2000000];
	for(int i=0;i<N;i++)right[i]=0;
	for(int i=0;i<N;i++)getmax(right[RIGHT[i]],LEFT[i]);
	int ans=INF;
	for(int r=N-1,left=0;r>=0;r--)
	{
		getmin(ans,min(left,r)+left+r);
		getmax(left,right[r]);
	}
	printf("%d\n",ans);
	return 0;
}
