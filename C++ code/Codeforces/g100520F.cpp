#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
struct Edge
{
	int a,b,val;
	Edge(){}
	Edge(const int _a,const int _b,const int _val):a(_a),b(_b),val(_val){}
};
vector<Edge>EDGE;
vector<int>ET[1000];
int N,M,SUM[1000];
int main()
{
	freopen("flights.in","r",stdin);
	freopen("flights.out","w",stdout);
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		if(N==0&&M==0)break;
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			EDGE.push_back(Edge(a,b,0));
			ET[a].push_back(i),ET[b].push_back(i);
		}
		for(int i=0;i<N;i++)SUM[i]=0;
		int count=0;
		for(int i=0;i<M;i++)
		{
			Edge &e=EDGE[i];
			if(e.a!=0&&e.b!=0)
			{
				count++;
				e.val=count;
				SUM[e.a]+=count,SUM[e.b]+=count;
			}
		}
		assert((int)ET[0].size()==N-1&&count+(N-1)==M);
		vector<int>order;
		for(int i=1;i<N;i++)order.push_back(i);
		sort(order.begin(),order.end(),[](const int a,const int b)->bool{return SUM[a]<SUM[b];});
		static int eis[1000];
		for(int i=0;i<N-1;i++)eis[max(EDGE[ET[0][i]].a,EDGE[ET[0][i]].b)]=ET[0][i];
		for(const int i:order)
		{
			Edge &e=EDGE[eis[i]];
			count++;
			e.val=count;
			assert(e.a==0||e.b==0);
			SUM[e.a]+=count,SUM[e.b]+=count;
		}
		assert(count==M);
		puts("Yes");
		for(int i=0;i<M;i++)
		{
			if(i)putchar(' ');
			printf("%d",EDGE[i].val);
		}
		puts("");
		sort(SUM,SUM+N);
		for(int i=1;i<N;i++)assert(SUM[i-1]<SUM[i]);
	}
	return 0;
}
