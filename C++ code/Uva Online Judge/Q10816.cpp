#include<cstdio>
#include<vector>
#include<queue>
#include<cassert>
using namespace std;
const int INF=2147483647;
void getmin(int &a,int b){if(b<a)a=b;}
void getmax(int &a,int b){if(b>a)a=b;}
int N,E,S,T;
struct Way
{
	int a,b,t,d;
	Way(){}
	Way(int a,int b,int t,int d):a(a),b(b),t(t),d(d){}
	int To(int &from){return from!=a?a:b;}
};
vector<Way>WAY;
vector<int>AD[100];
int DP[100],PRE[100];
int Solve(int maxt)
{
	for(int i=0;i<N;i++)DP[i]=INF;
	queue<int>qu,qv,qp;
	qu.push(S),qv.push(0),qp.push(-1);
	while(!qu.empty())
	{
		int u=qu.front(),v=qv.front(),pre=qp.front();qu.pop(),qv.pop(),qp.pop();
		if(v>=DP[u])continue;
		DP[u]=v,PRE[u]=pre;
		for(int i=0;i<AD[u].size();i++)
		{
			Way &w=WAY[AD[u][i]];
			if(w.t>maxt)continue;
			qu.push(w.To(u));
			qv.push(v+w.d);
			qp.push(u);
		}
	}
	return DP[T];
}
void DfsPrint(int u)
{
	if(u==S){printf("%d",u+1);return;}
	DfsPrint(PRE[u]);
	printf(" %d",u+1);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&E)==2)
	{
		scanf("%d%d",&S,&T);
		S--,T--;
		for(int i=0;i<N;i++)
		{
			AD[i].clear();
		}
		WAY.clear();
		int l=INF,r=-INF,mid;
		for(int i=0;i<E;i++)
		{
			static int a,b,t,d,sz;
			static double tt,dd;
			scanf("%d%d%lf%lf",&a,&b,&tt,&dd);
			a--,b--;
			t=tt*10.0+0.5,d=dd*10.0+0.5;
			sz=WAY.size();
			WAY.push_back(Way(a,b,t,d));
			getmin(l,t);
			getmax(r,t);
			AD[a].push_back(sz);
			AD[b].push_back(sz);
		}
//		printf("l=%d,r=%d\n",l,r);
		while(l<r)
		{
			mid=(l+r)/2;
			int result=Solve(mid);
			if(result==INF)l=mid+1;
			else r=mid;
		}
//		printf("binary=%d\n",l);
		int ans=Solve(l);
		assert(ans!=INF);
		DfsPrint(T);puts("");
		printf("%.1f %.1f\n",ans/10.0,l/10.0);
	}
	return 0;
}
/*
6 9
1 6
1 2 37.1 10.2
2 3 40.5 20.7
3 4 42.8 19.0
3 1 38.3 15.8
4 5 39.7 11.1
6 3 36.0 22.5
5 6 43.9 10.2
2 6 44.2 15.2
4 6 34.2 17.4
*/
