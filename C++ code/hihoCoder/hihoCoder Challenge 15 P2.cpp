#include<cstdio>
#include<vector>
#include<map>
#include<cassert>
using namespace std;
const int INF=2147483647;
int N;
vector<int>A[300],B[300];
struct Ope
{
	int a,b;
	Ope(){}
	Ope(int a,int b):a(a),b(b){}
};
vector<Ope>OPE1,OPE2;
int S[300];
bool VIS[300];
void GetOPE(vector<int>&v1,vector<int>&v2,vector<Ope>&ope)
{
	int n=v1.size();
	map<int,int>idx;
	for(int i=0;i<n;i++)idx[v2[i]]=i;
	for(int i=0;i<n;i++)S[i]=idx[v1[i]],VIS[i]=false;
	ope.clear();
	for(int i=0;i<n;i++)
	{
		if(VIS[i])continue;
		VIS[i]=true;
		if(S[i]==i)continue;
		vector<int>v;
		v.push_back(i);
		for(int u=S[i];u!=i;u=S[u])v.push_back(u),VIS[u]=true;
		for(int i=v.size()-1;i>0;i--)
//		for(int i=1;i<v.size();i++)
		ope.push_back(Ope(v[i-1],v[i]));
	}
}
void Swap(int &a,int &b){int c=a;a=b,b=c;}
void Perform1()
{
	for(int i=0;i<OPE1.size();i++)
	{
		for(int j=0;j<N;j++)Swap(A[j][OPE1[i].a],A[j][OPE1[i].b]);
	}
}
void Undo1()
{
	for(int i=OPE1.size()-1;i>=0;i--)
	{
		for(int j=0;j<N;j++)Swap(A[j][OPE1[i].a],A[j][OPE1[i].b]);
	}
}
void Perform2()
{
	for(int i=0;i<OPE2.size();i++)
	{
		for(int j=0;j<N;j++)Swap(A[OPE2[i].a][j],A[OPE2[i].b][j]);
	}
}
void Undo2()
{
	for(int i=OPE2.size()-1;i>=0;i--)
	{
		for(int j=0;j<N;j++)Swap(A[OPE2[i].a][j],A[OPE2[i].b][j]);
	}
}
bool Legal()
{
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			if(A[i][j]!=B[i][j])return false;
		}
	}
	return true;
}
int main()
{
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		A[i].resize(N);
		for(int j=0;j<N;j++)scanf("%d",&A[i][j]);
	}
	for(int i=0;i<N;i++)
	{
		B[i].resize(N);
		for(int j=0;j<N;j++)scanf("%d",&B[i][j]);
	}
	int ans=INF;
	for(int r=0;r<N;r++)
	{
		GetOPE(A[r],B[0],OPE1);
//		printf("r=%d: ",r);for(int i=0;i<OPE1.size();i++)printf("(%d,%d)",OPE1[i].a,OPE1[i].b);puts("");
		Perform1();
		assert(A[r]==B[0]);
		vector<int>a,b;
		for(int i=0;i<N;i++)a.push_back(A[i][0]),b.push_back(B[i][0]);
		GetOPE(a,b,OPE2);
		Perform2();
		if(Legal())ans=min(ans,(int)OPE1.size()+(int)OPE2.size());
		Undo2(),Undo1();
	}
	if(ans==INF)ans=-1;
	printf("%d\n",ans);
	return 0;
}
