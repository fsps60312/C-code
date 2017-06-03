#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
struct Segment
{
	int l,r;
	Segment(){}
	Segment(const int _l,const int _r):l(_l),r(_r){}
	bool operator<(const Segment &s)const{return l!=s.l?l<s.l:r>s.r;}
};
vector<Segment>SEG[100][100];
int N;
void RemoveCovering(vector<Segment>&s)
{
	sort(s.begin(),s.end());
	vector<Segment>ans;
	for(int i=0,j;i<(int)s.size();)
	{
		ans.push_back(s[i]);
		for(j=i+1;j<(int)s.size()&&s[j].r<=s[i].r;j++);
		i=j;
	}
	s.clear(),ans.swap(s);
}
void Insert(vector<Segment>&ans,const vector<Segment>&ls,const vector<Segment>&rs)
{
	for(const Segment &s:ls)ans.push_back(s);
	for(const Segment &s:rs)ans.push_back(s);
	if(ls.empty()||rs.empty())return;
	for(int i=0,j=0;i<(int)ls.size();i++)
	{
		while(j+1<(int)rs.size()&&rs[j+1].l<=ls[i].r)j++;
//		puts("a");
//		printf("(%d,%d)(%d,%d)\n",i,j,(int)ls.size(),(int)rs.size());
		if(rs[j].l<=ls[i].r&&rs[j].r>=ls[i].l)ans.push_back(Segment(ls[i].l,rs[j].r));
//		puts("b");
	}
}
int M;
int DP[101][301];
vector<int>VALS;
int Id(const int v){return lower_bound(VALS.begin(),VALS.end(),v)-VALS.begin();}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		if(true)
		{
			vector<Segment>tmp;
			for(int i=0;i<N;i++)
			{
				static Segment s;
				scanf("%d%d",&s.l,&s.r);
				tmp.push_back(s);
			}
			sort(tmp.begin(),tmp.end());
			for(int i=0;i<N;i++)for(int j=i;j<N;j++)SEG[i][j].clear();
			VALS.clear();
			for(int i=0;i<N;i++)
			{
				const int a=tmp[i].l,l=tmp[i].r;
//				printf("(%d,%d)\n",a,l);
				SEG[i][i].push_back(Segment(a-l,a));
				SEG[i][i].push_back(Segment(a,a+l));
				VALS.push_back(a-l),VALS.push_back(a),VALS.push_back(a+l);
			}
			tmp.clear(),vector<Segment>().swap(tmp);
		}
		if(true)
		{
			auto &s=VALS;
			sort(s.begin(),s.end()),s.resize(unique(s.begin(),s.end())-s.begin());
			M=s.size();
		}
		for(int gap=1;gap<N;gap++)
		{
			for(int i=0;i+gap<N;i++)
			{
				const int j=i+gap;
				for(int k=i;k<j;k++)
				{
					Insert(SEG[i][j],SEG[i][k],SEG[k+1][j]);
					Insert(SEG[i][j],SEG[k+1][j],SEG[i][k]);
				}
				RemoveCovering(SEG[i][j]);
			}
		}
		for(int i=0;i<=M;i++)DP[0][i]=0;
		for(int i=1;i<=N;i++)
		{
			for(int j=0;j<=M;j++)DP[i][j]=DP[i-1][j];
			for(int j=1;j<=i;j++)for(const auto &s:SEG[j-1][i-1])
			{
				const int l=Id(s.l)+1;
				for(int k=Id(s.r)+1;k<=M;k++)getmax(DP[i][k],DP[j-1][l-1]+(s.r-s.l));
			}
		}
		const int ans=DP[N][M];
//		if(VALID[0][M-1])ans=VALS[M-1]-VALS[0];
		printf("%d\n",ans);
	}
	return 0;
}
