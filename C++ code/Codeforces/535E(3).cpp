#include<cstdio>
#include<cassert>
#include<algorithm>
#include<cmath>
#include<vector>
#include<map>
using namespace std;
const double EPS=1e-9;
struct Deq
{
	int S[200000],L,R;
	void Clear(){L=0,R=-1;}
	int Size(){return R-L+1;}
	void PushBack(const int v){S[++R]=v;}
	void PopBack(){R--;}
	void PopFront(){L++;}
	int Back(const int i){return S[R-i];}
	int Front(const int i){return S[L+i];}
}DEQ;
struct Competitor
{
	int s,r;
	bool operator<(const Competitor &c)const{return 1.0/r-1.0/s>1.0/c.r-1.0/c.s;}
}S[200000];
int N;
double GetA(const int i){return 1.0/S[i].r-1.0/S[i].s;}
double GetB(const int i){return 1.0/S[i].s;}
double GetX(const int i1,const int i2){return (GetB(i1)-GetB(i2))/(GetA(i2)-GetA(i1));}
bool IsParallel(const int i)
{
	if(DEQ.Size()==0)return false;
	return fabs(GetA(DEQ.Back(0))-GetA(i))<EPS;
}
map<int,vector<int> >ANS;
bool IsSame(const double a,const double b){return fabs(a-b)<EPS;}
bool NeedPopBack(const int i)
{
	if(DEQ.Size()==0)return false;
	if(IsParallel(i))
	{
		if(IsSame(GetB(DEQ.Back(0)),GetB(i)))ANS[i].push_back(DEQ.Back(0));
		return GetB(DEQ.Back(0))>=GetB(i)-EPS;
	}
	if(DEQ.Size()==1)return false;
	if(IsSame(GetX(DEQ.Back(0),i),GetX(DEQ.Back(1),DEQ.Back(0))))ANS[i].push_back(DEQ.Back(0));
	return GetX(DEQ.Back(0),i)+EPS<GetX(DEQ.Back(1),DEQ.Back(0));
}
void Dfs(const int u,vector<int>&ans)
{
	ans.push_back(u);
	for(const int nxt:ANS[u])Dfs(nxt,ans);
	ANS[u].clear();
}
int main()
{
//	freopen("in.txt","r",stdin);
//	R/r+S/s
//	x/r+(1-x)/s
//	=1/s+x/r-x/s
//	=1/s+x(1/r-1/s)
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d%d",&S[i].s,&S[i].r);
		sort(S,S+N);
		DEQ.Clear();
		ANS.clear();
		for(int i=0;i<N;i++)
		{
			while(NeedPopBack(i))DEQ.PopBack();
			if(!IsParallel(i)||GetB(i)<GetB(DEQ.Back(0)))DEQ.PushBack(i);
		}
		while(DEQ.Size()>=2&&GetX(DEQ.Front(0),DEQ.Front(1))<0.0+EPS)DEQ.PopFront();
		while(DEQ.Size()>=2&&GetX(DEQ.Back(1),DEQ.Back(0))>1.0-EPS)DEQ.PopBack();
		vector<int>ans;
		for(int i=0;i<DEQ.Size();i++)Dfs(DEQ.Front(i),ans);
		sort(ans.begin(),ans.end());
		for(int i=0;i<(int)ans.size();i++)
		{
			if(i)putchar(' ');
			printf("%d",ans[i]+1);
		}
		puts("");
	}
	return 0;
}
