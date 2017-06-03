#include<bits/stdc++.h>
using namespace std;
struct Cow
{
	int h,a,c;
	bool operator<(const Cow &c)const{return a<c.a;}
}COW[400];
int N,VIS[40000],MX=0;
vector<int>V;
int main()
{
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		Cow &c=COW[i];
		scanf("%d%d%d",&c.h,&c.a,&c.c);
		MX=max(MX,c.a);
	}
	sort(COW,COW+N);
	for(int i=0;i<=MX;i++)VIS[i]=0;
	VIS[0]++;V.push_back(0);
	int ans=0;
	for(int i=0;i<N;i++)
	{
		Cow &c=COW[i];
		for(int j=0;j<V.size();j++)
		{
			int &v=V[j];
			if(v+c.h<=c.a&&!VIS[v+c.h]++){V.push_back(v+c.h);ans=max(ans,v+c.h);}
		}
	}
	printf("%d\n",ans);
	return 0;
}
