#include<cstdio>
#include<cassert>
#include<map>
#include<set>
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
		map<int,int>tmp;
		for(int i=0;i<N;i++)tmp[DISH[i]]=i;
		for(int i=0;i<N;i++)tmp[DISH[i]]=i,RIGHT[i]=(i+N-tmp[LIKE[i]])%N;
		for(int i=N-1;i>=0;i--)tmp[DISH[i]]=i;
		for(int i=N-1;i>=0;i--)tmp[DISH[i]]=i,LEFT[i]=(tmp[LIKE[i]]+N-i)%N;
	}
	map<int,int,greater<int> >right;
	for(int i=0;i<N;i++)
	{
		auto it=right.find(RIGHT[i]);
		if(it!=right.end())getmax(it->second,LEFT[i]);
		else right[RIGHT[i]]=LEFT[i];
	}
	int ans=right.begin()->first;
	int left=0;
	while(!right.empty())
	{
		const auto it=right.begin();
		getmax(left,it->second);
		right.erase(it);
		const int r=(right.empty()?0:right.begin()->first);
		getmin(ans,min(left,r)+left+r);
	}
	printf("%d\n",ans);
	return 0;
}
