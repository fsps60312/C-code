#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
int N,S[100001];
/*
g: a[n]->m
h: a[m]->n
x: g(n->m)->h(m->n) = f(x)
x: h(m->n)->g(n->m) = x
m<=n

g[i]=rank(f(i))
h[rank(f(i))]=f(i)
g[rank(f(i))]=rank(f(f(i)))
f(i)=f(f(i))
*/
bool Solve()
{
	for(int i=1;i<=N;i++)if(S[i]!=S[S[i]])return false;
	vector<int>v;
	for(int i=1;i<=N;i++)v.push_back(S[i]);
	sort(v.begin(),v.end()),v.resize(unique(v.begin(),v.end())-v.begin());
	printf("%d\n",(int)v.size());
	for(int i=1;i<=N;i++)
	{
		if(i>1)putchar(' ');
		printf("%d",(int)(lower_bound(v.begin(),v.end(),S[i])-v.begin())+1);
	}
	puts("");
	for(int i=0;i<(int)v.size();i++)
	{
		if(i)putchar(' ');
		printf("%d",v[i]);
	}
	puts("");
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=1;i<=N;i++)scanf("%d",&S[i]);
		if(!Solve())puts("-1");
	}
	return 0;
}
