#include<cstdio>
#include<algorithm>
#include<queue>
#include<cassert>
using namespace std;
int N;
struct Dish
{
	int a,b;
	bool operator<(const Dish &d)const{return a<d.a;}
}DISH[100];
vector<int>S[10000];
int CNT[10000];
bool VIS[10000];
bool Fit(const int v)
{
	for(int i=0;i<10000;i++)VIS[i]=false;
	for(int i=0;i<N;i++)CNT[i]=DISH[i].b-DISH[i].a;
	int cnt=0;
	for(int i=0;i<N;i++)
	{
		int idx=-1,mx=0;
		for(int j=0;j<N;j++)if(CNT[j]>mx)mx=CNT[j],idx=j;
		Dish &d=DISH[idx];
		for(int j=d.a;j<d.b;j++)if(!VIS[j])
		{
			VIS[j]=true,cnt++;
			for(int k=0;k<S[j].size();k++)CNT[S[j][k]]--;
		}
		assert(CNT[idx]==0);
		if(cnt<v)return false;
		cnt-=v;
	}
	for(int i=0;i<N;i++)assert(CNT[i]==0);
	return true;
}
int main()
{
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		Dish &d=DISH[i];
		scanf("%d%d",&d.a,&d.b);
		for(int j=d.a;j<d.b;j++)S[j].push_back(i); 
	}
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
