#include<cstdio>
#include<cassert>
#include<utility>
#include<vector>
#include<cmath>
using namespace std;
int N;
double X,Y,D;
vector<pair<int,int> >S;
double Sq(const double &v){return v*v;}
double Dist(const pair<int,int>&a,const pair<int,int>&b){return sqrt(Sq(a.first-b.first)+Sq(a.second-b.second));}
int DJ[10002];
int Find(const int a){return DJ[a]==a?a:(DJ[a]=Find(DJ[a]));}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%lf%lf",&X,&Y)==2)
	{
		S.clear();
		S.push_back(make_pair(0.0,0.0));
		S.push_back(make_pair(X,Y));
		scanf("%d",&N);
		for(int i=0;i<N;i++)
		{
			scanf("%lf%lf",&X,&Y);
			S.push_back(make_pair(X,Y));
		}
		scanf("%lf",&D);
		N+=2;
		for(int i=0;i<N;i++)DJ[i]=i;
		for(int i=0;i<N;i++)for(int j=i+1;j<N;j++)if(Dist(S[i],S[j])<=D)DJ[Find(i)]=Find(j);
		if(Find(0)==Find(1))puts("I am lucky!");
		else puts("Boom!");
	}
	return 0;
}
