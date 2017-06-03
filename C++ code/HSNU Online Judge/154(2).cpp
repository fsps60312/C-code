#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
struct Segment
{
	int l,r,ans,id;
	Segment(){}
	Segment(const int _l,const int _r,const int _i):l(_l),r(_r),id(_i){}
	bool operator<(const Segment &s)const{return l!=s.l?l<s.l:r<s.r;}
};
int N,M,Q,S[80000];
int DISTRIBUTE[80001],CNT[80000],MXNOW,ANS[100000];
void Add(const int v){DISTRIBUTE[CNT[v]]--,DISTRIBUTE[++CNT[v]]++,getmax(MXNOW,CNT[v]);}
void Sub(const int v){if(!--DISTRIBUTE[CNT[v]]&&CNT[v]==MXNOW)MXNOW--;DISTRIBUTE[--CNT[v]]++;}
void Solve(const vector<Segment>&s)
{
//	for(int i=0;i<N;i++)printf("%d ",S[i]);puts("");
	for(int i=0;i<M;i++)CNT[i]=0;
	for(int i=0;i<=N;i++)DISTRIBUTE[i]=0;
	DISTRIBUTE[0]=M;
	MXNOW=0;
	int l=0,r=-1;
	for(const Segment &seg:s)
	{
		while(r<seg.r)Add(S[++r]);
		while(r>seg.r)Sub(S[r--]);
		while(l<seg.l)Sub(S[l++]);
//		printf("(%d,%d)%d\n",l,r,MXNOW);
		ANS[seg.id]=MXNOW;
	}
}
vector<Segment>SEG[283];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&Q);
	vector<int>tmp;
	for(int i=0;i<N;i++)scanf("%d",&S[i]),tmp.push_back(S[i]);
	sort(tmp.begin(),tmp.end());tmp.resize(unique(tmp.begin(),tmp.end())-tmp.begin());
	M=tmp.size();
	for(int i=0;i<N;i++)S[i]=lower_bound(tmp.begin(),tmp.end(),S[i])-tmp.begin();
	int sq=sqrt(N);
	for(int i=0;i<=(N-1)/sq;i++)SEG[i].clear();
	for(int i=0;i<Q;i++)
	{
		static int a,b;
		scanf("%d%d",&a,&b),a--,b--;
		SEG[b/sq].push_back(Segment(a,b,i));
	}
	for(int i=0;i<=(N-1)/sq;i++)
	{
		sort(SEG[i].begin(),SEG[i].end());
		Solve(SEG[i]);
	}
	for(int i=0;i<Q;i++)printf("%d\n",ANS[i]);
	return 0;
}
