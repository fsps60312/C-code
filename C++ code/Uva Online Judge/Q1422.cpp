#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
struct pairtype
{
	int a,b,c;
};
pairtype S[10000],tmp[10000];
int T,n;
vector<int> v1,v2;
void rangea(int a,int b)
{
	if(a==b) return;
	int mid=(a+b)/2;
	rangea(a,mid);
	rangea(mid+1,b);
	int c=a,d=mid+1;
	for(int i=a;i<=b;i++)
	{
		if(d>b||(c<=mid&&S[c].a<S[d].a)) tmp[i]=S[c++];
		else tmp[i]=S[d++];
	}
	for(int i=a;i<=b;i++) S[i]=tmp[i];
}
bool check(int a)
{
	v1.clear();
	v2.clear();
	int now=0;
	for(int i=1;i<n;i++)
	{
		now+=S[i-1].c;
		now-=a*(S[i].a-S[i-1].a);
		if(now<=0) now=0;
		else
		{
			v1.push_back(now);
			v2.push_back(S[i].b);
		}
	}
	return v1.size()==0;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=0;i<n;i++)
		{
			scanf("%d%d%d",&S[i].a,&S[i].b,&S[i].c);
		}
		rangea(0,n-1);
		int Min=2,Max=1000,mid;
		while(Min<Max)
		{
			mid=(Min+Max)/2;
			if(check(mid)) Min=mid+1;
			else Max=mid;
		}
		printf("%d\n",Max-1);
	}
	return 0;
}
