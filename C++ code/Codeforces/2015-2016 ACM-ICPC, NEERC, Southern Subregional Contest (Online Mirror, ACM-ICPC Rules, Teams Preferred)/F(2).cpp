#include<cstdio>
#include<algorithm>
using namespace std;
int N;
struct Dish
{
	int a,b;
	bool operator<(const Dish &d)const{return a<d.a;}
}DISH[100];
int CNT[10000];
bool VIS[10000];
bool Fit(const int v)
{
	for(int i=0;i<10000;i++)CNT[i]=0,VIS[i]=false;
	int cnt=0,remain=N;
	for(;remain;)
	{
		bool found=false;
		for(int j=0;j<N;j++)
		{
			if(VIS[j])continue;
			Dish &d=DISH[j];
			for(int j=d.a;j<d.b;j++)
			{
				if(CNT[j]++==0)cnt++;
			}
			if(cnt<v)
			{
				for(int j=d.a;j<d.b;j++)
				{
					if(--CNT[j]==0)cnt--;
				}
			}
			else cnt-=v,found=true,remain--,VIS[j]=true;
		}
		if(!found)return false;
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
