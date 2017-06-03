#include<cstdio>
#include<vector>
#include<cassert>
#include<stack>
#define termin(x,...) {printf(x,##__VA_ARGS__);while(1)printf("E");assert(0);}
using namespace std;
int T,N,LASTCH,C[300000],TAG[300001];
vector<int>D[300000],P[300000];
void init()
{
	scanf("%d",&C[0]);
	TAG[0]=1;
	int i,j;
	for(i=1,j=0;i<N;i++)
	{
		scanf("%d",&C[i]);
		while(j<N&&D[j].size()==C[j])j++,TAG[j]=i;
		if(j<N)D[j].push_back(i),LASTCH=i;
	}
	for(;;i++)
	{
		while(j<N&&D[j].size()==C[j])j++,TAG[j]=i;
		if(j==N)break;
		D[j].push_back(i),LASTCH=i;
	}
}
void buildP(int _u,int _fa,int _dep)
{
	if(_u>=N)return;
	stack<int>us,fas,deps;
	us.push(_u),fas.push(_fa),deps.push(_dep);
	while(!us.empty())
	{
		int u=us.top(),fa=fas.top(),dep=deps.top();
		us.pop(),fas.pop(),deps.pop();
		if(u>=N)continue;
		int uplen=1;
		for(int i=0;i<P[fa].size();i++,uplen<<=1)
		{
			int &fap=P[fa][i];
			P[u].push_back(D[fap][C[fap]]);
		}
		if(uplen<=dep)P[u].push_back(0);
		for(int &i=C[u]=0;i<D[u].size();i++)
		{
			us.push(D[u][i]);
			fas.push(u);
			deps.push(dep+1);
		}
	}
}
bool serch(int t,int u)
{
	while(u>t)
	{
		int p=0;
		while(p+1<P[u].size()&&P[u][p+1]>=t)p++;
		u=P[u][p];
	}
	if(u==t)return true;
	else if(u<t)return false;
}
bool query(int a,int b)
{
	if(a>LASTCH||b>LASTCH)termin("a=%d,b=%d, out of range\n");
	if(a>=N)return false;
	if(b>=N)
	{
		int l=0,r=N-1,mid;
		while(l<r)
		{
			mid=(l+r+1)/2;
			if(TAG[mid]>b)r=mid-1;
			else l=mid;
		}
		b=l;
	}
	return serch(a,b);
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	int kase=1;
	while(T--)
	{
		scanf("%d",&N);
		if(N>300000)termin("N=%d, out of range\n",N);
		for(int i=0;i<N;i++)
		{
			D[i].clear();
			P[i].clear();
		}
		init();
		for(int &i=C[0]=0;i<D[0].size();i++)buildP(D[0][i],0,1);
//		for(int i=0;i<N;i++)
//		{
//			printf("p%d:",i);
//			for(int j=0;j<P[i].size();j++)printf(" %d",P[i][j]);
//			puts("");
//		}
		int Q;
		scanf("%d",&Q);
		printf("Case %d:\n",kase++);
		while(Q--)
		{
			static int a,b;
			scanf("%d%d",&a,&b);
			printf("%s\n",query(a,b)?"Yes":"No");
		}
		if(T)puts("");
	}
	return 0;
}
