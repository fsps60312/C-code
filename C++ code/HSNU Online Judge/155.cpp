#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm> 
using namespace std;
struct Line
{
	int a,b1,b2;
	Line(){}
	Line(const int _a,const int _b1,const int _b2):a(_a),b1(min(_b1,_b2)),b2(max(_b1,_b2)){}
	bool operator<(const Line &l)const{return a!=l.a?a<l.a:b1<l.b1;}
};
vector<Line>LINE[2];
vector<bool>VIS[2];
bool AtRange(const int o,const int l,const int r){return l<=o&&o<=r;}
void Dfs(const int u,const int d,int *cnt)
{
	if(VIS[d][u])return;
	VIS[d][u]=true;
	cnt[d]++;
	const Line &now=LINE[d][u];
	for(int i=0;i<(int)LINE[d^1].size();i++)
	{
		const Line &nxt=LINE[d^1][i];
		if(AtRange(now.a,nxt.b1,nxt.b2)&&AtRange(nxt.a,now.b1,now.b2))Dfs(i,d^1,cnt);
	}
}
bool Intersect(const Line &l1,const Line &l2)
{
	if(l1.a!=l2.a)return false;
	return max(l1.b1,l2.b1)<=min(l1.b2,l2.b2);
}
void MergeLine(vector<Line>&data)
{
	if(data.empty())return;
	vector<Line>ans;
	sort(data.begin(),data.end());
	ans.push_back(data[0]);
	for(int i=1,j=0;i<(int)data.size();i++)
	{
		if(Intersect(ans[j],data[i]))ans[j]=Line(ans[j].a,min(ans[j].b1,data[i].b1),max(ans[j].b2,data[i].b2));
		else ans.push_back(data[i]),j++;
	}
	data=ans;
}
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	assert(scanf("%d",&N)==1);
	for(int d=0;d<2;d++)LINE[d].clear(),VIS[d].clear();
	for(int i=0,x1,y1,x2,y2;i<N;i++)
	{
		assert(scanf("%d%d%d%d",&x1,&y1,&x2,&y2)==4);
		assert((x1==x2)!=(y1==y2));
		if(x1==x2)LINE[0].push_back(Line(x1,y1,y2)),VIS[0].push_back(false);
		else LINE[1].push_back(Line(y1,x1,x2)),VIS[1].push_back(false);
	}
	for(int d=0;d<2;d++)MergeLine(LINE[d]);
//	for(int d=0;d<2;d++)for(Line l:LINE[d])printf("(%d,%d,%d)\n",l.a,l.b1,l.b2);
	int ans=0;
	for(int d=0;d<2;d++)
	{
		for(int i=0;i<(int)LINE[d].size();i++)if(!VIS[d][i])
		{
			int cnt[2]={0,0};
			Dfs(i,d,cnt);
			ans+=max(cnt[0],cnt[1]);
		}
	}
	printf("%d\n",ans);
	return 0;
}
