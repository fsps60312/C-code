#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
struct DjSet
{
	int s[10001];
	void clear(const int n){for(int i=0;i<n;i++)s[i]=i;}
	int find(const int a){return s[a]==a?a:(s[a]=find(s[a]));}
	bool merge(int a,int b){if((a=find(a))==(b=find(b)))return false;s[a]=b;return true;}
}DJ;
struct Product
{
	int price,deadline;
	bool operator<(const Product &p)const{return price>p.price;}
}P[10000];
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d%d",&P[i].price,&P[i].deadline);
		sort(P,P+N);
		DJ.clear(10001);
		int ans=0;
		for(int i=0;i<N;i++)
		{
			const int d=DJ.find(P[i].deadline);
			if(d==0)continue;
			DJ.merge(d,d-1);
			ans+=P[i].price;
		}
		printf("%d\n",ans);
	}
	return 0;
}
