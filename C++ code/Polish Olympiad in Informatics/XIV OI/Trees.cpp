#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<set>
#include<map>
using namespace std;
//const LL INF=9223372036854775807LL;
template<class T>inline void getmin(T &a,const T &b){if(b<a)a=b;}
template<class T>inline void getmin(T &a,T &b,const T &c){getmin(a,c),getmin(b,c);}
struct QueryType
{
	int ID,X,UPON,DOWN;
	QueryType(){}
	QueryType(const int _ID,const int _X,const int _UPON,const int _DOWN):ID(_ID),X(_X),UPON(_UPON),DOWN(_DOWN){}
};
bool operator<(const QueryType &a,const QueryType &b){return a.X<b.X;}
struct SegTree
{
	multiset<int>S[200000];
	int MX[200000];
	int N;
	void Build(const int id,const int l,const int r)
	{
		MX[id]=0;
		if(l==r){S[id].clear(),S[id].insert(0);return;}
		const int mid=(l+r)/2;
		Build(id*2,l,mid),Build(id*2+1,mid+1,r);
	}
	void Build(const int _N){N=_N;Build(1,0,N-1);}
	void Insert(const int id,const int l,const int r,const int loc,const int val)
	{
		if(l==r)
		{
			assert(r==loc);
			S[id].insert(val);
			MX[id]=*S[id].rbegin();
			return;
		}
		const int mid=(l+r)/2;
		if(loc<=mid)Insert(id*2,l,mid,loc,val);
		else Insert(id*2+1,mid+1,r,loc,val);
	}
	void Insert(const int loc,const int val){Insert(1,0,N-1,loc,val);}
	void Erase(const int loc,const int val){assert(0);}
}SEG1,SEG2,SEG3;
int N,M,H[50000],ANS[50000];
vector<int>V;
void Discretize()
{
	V.clear();
	for(int i=0;i<N;i++)V.push_back(H[i]);
	sort(V.begin(),V.end()),V.resize(M=(int)(unique(V.begin(),V.end())-V.begin()));
	for(int i=0;i<N;i++)H[i]=(int)(lower_bound(V.begin(),V.end(),H[i])-V.begin());
}
int Dif(const int i1,const int i2){return abs(V[H[i1]]-V[H[i2]]);}
vector<QueryType>Q;
void Solve()
{
	for(int i=0;i<N;i++)ANS[i]=0;
	if(N==2)return;
	assert(N>=3);
	getmin(ANS[0],ANS[N-1],(Dif(N-1,1)+Dif(N-2,0))-(Dif(0,1)+Dif(N-2,N-1)));
	getmin(ANS[0],Dif(0,2)-Dif(1,2));
	getmin(ANS[N-1],Dif(N-3,N-1)-Dif(N-3,N-2));
	for(int i=2;i+1<N;i++)getmin(ANS[0],(Dif(i,1)+Dif(i-1,0)+Dif(0,i+1))-(Dif(0,1)+Dif(i-1,i)+Dif(i,i+1)));
	for(int i=1;i+1<N-1;i++)getmin(ANS[N-1],(Dif(i-1,N-1)+Dif(N-1,i+1)+Dif(N-2,i))-(Dif(i-1,i)+Dif(i,i+1)+Dif(N-2,N-1)));
	for(int i=2;i+1<N;i++)getmin(ANS[i-1],ANS[i],(Dif(i-2,i)+Dif(i-1,i+1))-(Dif(i-2,i-1)+Dif(i,i+1)));
	Q.clear();
	for(int i=1;i+1<N;i++)Q.push_back(QueryType(i,H[i],min(H[i-1],H[i+1]),max(H[i-1],H[i+1])));
	sort(Q.begin(),Q.end());
	SEG1.Build(M),SEG2.Build(M),SEG3.Build(M);
	multimap<int,int>m1,m2;
	for(int _qi=0;_qi<(int)Q.size();_qi++)
	{
		const QueryType &q=Q[_qi];
		while(!m1.empty()&&m1.begin()->first<=q.X)
		{
			const int i=m1.begin()->second;
			SEG2.Insert(Q[i]),m2.insert(make_pair(Q[i].UPON,i));
			SEG1.Erase(Q[i]),m1.erase(m1.begin());
		}
		while(!m2.empty()&&m2.begin()->first<=q.X)
		{
			const int i=m2.begin()->second;
			SEG3.Insert(Q[i]);
			SEG2.Erase(Q[i]),m2.erase(m2.begin());
		}
		if(q.X>=q.UPON)
		{
			if(SEG1.QueryCount(q.DOWN,M-1))getmin(ANS[q.ID],-((V[q.X]-V[q.DOWN])+(V[q.X]-V[q.UP])));
			getmin(ANS[q.ID],-((V[q.X]-SEG1.QueryMinX(q.UPON,q.DOWN))+(V[q.X]-V[q.UPON])));
			getmin(ANS[q.ID],-(V[q.X]-SEG1.QueryMinX(0,q.UPON)));
			getmin(ANS[q.ID],(V[q.DOWN]-SEG2.QueryMaxX(q.DOWN,M-1))-(V[q.X]-V[q.UPON]));
			if(SEG2.QueryCount(q.UPON,q.DOWN))getmin(ANS[q.ID],-(V[q.X]-V[q.UPON]));
			getmin(ANS[q.ID],-(V[q.X]-SEG2.QueryMinX(0,q.UPON)));
			//this line is innecessary
			//this line is innecessary
			//this line is innecessary
			assert(0);
		}
		else if(q.X>=q.DOWN)
		{
			if(SEG1.QueryCount(q.DOWN,M-1))getmin(ANS[q.ID],-(V[q.X]-V[q.DOWN]));
			getmin(ANS[q.ID],-(V[q.X]-SEG1.QueryMinX(q.UPON,q.DOWN)));
			//this line is impossible
			getmin(ANS[q.ID],V[q.DOWN]-SEG2.QueryMaxX(q.DOWN,M-1));
			//this line is innecessary
			//this line is impossible
			//this line is innecessary
			//this line is innecessary
			//this line is impossible
			assert(0);
		}
		else
		{
			if(SEG1.QueryCount(q.DOWN,M-1))getmin(ANS[q.ID],0);
			//this line is impossible
			//this line is impossible
			//this line is innecessary
			//this line is impossible
			//this line is impossible
			//this line is innecessary
			//this line is impossible
			//this line is impossible
			assert(0);
		}
		assert(0);
		m1.insert(make_pair(q.DOWN,_qi));
	}
	assert(0);
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&H[i]);
		Discretize();
		Solve();
		long long dif=0;
		for(int i=1;i<N;i++)dif+=Dif(i-1,i);
		for(int i=0;i<N;i++)printf("%lld\n",dif+ANS[i]);
	}
	return 0;
}
