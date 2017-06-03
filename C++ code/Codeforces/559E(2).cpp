#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<utility>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
struct SpotLight
{
	int a,l;
	SpotLight(){}
	SpotLight(const int _a,const int _l):a(_a),l(_l){}
	bool operator<(const SpotLight &s)const{return a<s.a;}
};
int N,M;
vector<int>VALS;
vector<SpotLight>S;
int Id(const int v){return lower_bound(VALS.begin(),VALS.end(),v)-VALS.begin();}
void Discretize()
{
	vector<int>&s=VALS;
	s.clear();
	for(const auto &v:S)s.push_back(v.a-v.l),s.push_back(v.a),s.push_back(v.a+v.l);
	sort(s.begin(),s.end()),s.resize(unique(s.begin(),s.end())-s.begin());
	M=s.size();
}
bool SEG[300][300];
int DP[300]; 
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		S.clear();
		for(int i=0,a,b;i<N;i++)scanf("%d%d",&a,&b),S.push_back(SpotLight(a,b));
		sort(S.begin(),S.end());
		Discretize();
		for(int i=0;i<M;i++)for(int j=i;j<M;j++)SEG[i][j]=(i==j);
		for(int i=0;i<N;i++)
		{
			{
				int cur=S[i].a+S[i].l,d=0;
				for(int j=i+1;j<N;j++)
				{
					if(!d&&cur<S[j].a)d=1;
					else cur=S[j].a+S[j].l;
					if(d&&cur<S[j].a-S[j].l)break;
					else cur=S[j].a;
					SEG[Id(S[i].a)][Id(cur)]=true;
				}
			}
			{
				int cur=S[i].a+S[i].l;
				for(int j=i+1;j<N;j++)
				{
					if(cur<S[j].a)break;
					else cur=S[j].a+S[j].l;
					SEG[Id(S[i].a)][Id(cur)]=true;
				}
			}
			{
				int cur=S[i].a;
				for(int j=i+1;j<N;j++)
				{
					if(cur<S[j].a-S[j].l)break;
					else cur=S[j].a;
					SEG[Id(S[i].a-S[i].l)][Id(cur)]=true;
				}
			}
		}
		for(int i=0,mx=0;i<M;i++)
		{
			DP[i]=mx;
			for(int j=1;j<=i;j++)if(SEG[j][i])
			{
				getmax(DP[i],DP[j-1]+(VALS[i]-VALS[j]));
			}
			mx=DP[i];
		}
		printf("%d\n",DP[M-1]);
	}
	return 0;
}
