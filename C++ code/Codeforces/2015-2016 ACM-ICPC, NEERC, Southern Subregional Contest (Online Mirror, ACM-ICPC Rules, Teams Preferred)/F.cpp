#include<cstdio>
#include<algorithm>
using namespace std;
int N;
struct Dish
{
	int a,b;
	bool operator<(const Dish &d)const{return a<d.a;}
}DISH[100];
bool Fit(const int v)
{
	static bool vis[10001];
	for(int i=0;i<=10000;i++)vis[i]=false;
	int cnt=0;
	for(int i=0;i<N;i++)
	{
		Dish &d=DISH[i];
		for(int j=d.a;j<d.b;j++)if(!vis[j])vis[j]=true,cnt++;
		if(cnt<v)return false;
		cnt-=v;
	}
	return true;
}
int main()
{
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		Dish &d=DISH[i];
		scanf("%d%d",&d.a,&d.b);
	}
	sort(DISH,DISH+N);
	int l=0,r=10000,mid;
	while(l<r)
	{
		mid=(l+r+1)/2;
		if(!Fit(mid))r=mid-1;
		else l=mid;
	}
	printf("%d\n",l*N);
	return 0;
}
