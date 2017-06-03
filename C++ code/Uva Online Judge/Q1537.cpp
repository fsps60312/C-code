#include<cstdio>
#include<string>
#include<map>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;
const int INF=2147483647;
map<string,int>IDX;
int GetIdx(string s)
{
	if(IDX.find(s)==IDX.end())
	{
		static int sz;sz=IDX.size();
printf("%d=%s\n",sz,s.c_str());
		return IDX[s]=sz;
	}
	return IDX[s];
}
struct Edge
{
	int a,b,w;
	Edge(){}
	Edge(int a,int b,int w):a(a),b(b),w(w){}
	bool operator<(const Edge &e)const{return w<e.w;}
};
vector<Edge>EDGE;
int DJ[21];
int FindDJ(int a){return DJ[a]==a?a:(DJ[a]=FindDJ(DJ[a]));}
bool AddEdge(int e,int &ans,int &cnt)
{
	int &a=EDGE[e].a,&b=EDGE[e].b;
	if(FindDJ(a)==FindDJ(b))return false;
    DJ[FindDJ(a)]=FindDJ(b);
    ans+=EDGE[e].w;
    cnt--;
    printf("Add %d\n",e);
    return true;
}
void ClearDJ()
{
	for(int i=0;i<IDX.size();i++)DJ[i]=i;
}
int Cntbits(int a)
{
	a=((a&0xaaaaaaaa)>>1)+(a&0x55555555);
	a=((a&0xcccccccc)>>2)+(a&0x33333333);
	a=((a&0xf0f0f0f0)>>4)+(a&0x0f0f0f0f);
	a=((a&0xff00ff00)>>8)+(a&0x00ff00ff);
	a=((a&0xffff0000)>>16)+(a&0x0000ffff);
	return a;
}
int LIMIT;
int Solve()
{
	vector<int>rt;
	for(int i=0;i<EDGE.size();i++)
	{
		int &a=EDGE[i].a,&b=EDGE[i].b;
		if(!a||!b)rt.push_back(i);
	}
	int ans=INF;
	for(int s=1,limit=(1<<rt.size());s<limit;s++)
	{
		if(Cntbits(s)>LIMIT)continue;
		//printf("s=%d\n",s);
		ClearDJ();
		int ta=0,cnt=IDX.size();
		for(int i=0;i<rt.size();i++)if(s&(1<<i))AddEdge(rt[i],ta,cnt);
		for(int i=0;cnt!=1&&i<EDGE.size();i++)AddEdge(i,ta,cnt);
		if(cnt==1)ans=min(ans,ta);
		printf("s=%d,ta=%d\n",s,ta);
//if(ta==215)printf("s=%d\n",s);
	}
	//assert(ans==INF);
	return ans;
}
int T,M;
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			scanf("%d",&M);
			IDX.clear();
			EDGE.clear();
			GetIdx("Park");
			static int tmp[21][21];
			for(int i=0;i<21;i++)for(int j=0;j<21;j++)tmp[i][j]=INF;
			while(M--)
			{
				static char sa[11],sb[11];
				static int a,b,w;
				scanf("%s%s%d",sa,sb,&w);
				a=GetIdx(sa),b=GetIdx(sb);
				tmp[a][b]=tmp[b][a]=min(tmp[a][b],w);
			}
			scanf("%d",&LIMIT);
			for(int i=0;i<21;i++)for(int j=i+1;j<21;j++)if(tmp[i][j]!=INF)EDGE.push_back(Edge(i,j,tmp[i][j]));
			sort(EDGE.begin(),EDGE.end());
			for(int i=0;i<EDGE.size();i++)printf("%d %d %d\n",EDGE[i].a,EDGE[i].b,EDGE[i].w);
//			printf("Park=%d\n",IDX["Park"]);
            printf("Total miles driven: %d\n",Solve());
		}
	}
	return 0;
}

