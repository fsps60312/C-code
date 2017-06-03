#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<set>
//#include<map>
using namespace std;
const int INF=2147483647;
//const LL INF=9223372036854775807LL;
template<class T>inline void getmin(T &a,const T &b){if(b<a)a=b;}
template<class T>inline void getmin(T &a,T &b,const T &c){getmin(a,c),getmin(b,c);}
template<class T>inline T max(const T &a,const T &b,const T &c){return max(max(a,b),c);}
struct QueryType
{
	int ID,X,UPON,DOWN;
	QueryType(){}
	QueryType(const int _ID,const int _X,const int _UPON,const int _DOWN):ID(_ID),X(_X),UPON(_UPON),DOWN(_DOWN){}
};
bool operator<(const QueryType &a,const QueryType &b)
{
	if(a.X!=b.X)return a.X<b.X;
	return a.ID<b.ID;
}
struct SegTree
{
	int N,SZ;
	bool IS_MX;
	multiset<int>S[200000];
	int D[200000];
	void Build(const int id,const int l,const int r)
	{
		D[id]=(IS_MX?-INF:INF);
		if(l==r){S[id].clear(),S[id].insert(D[id]);return;}
		const int mid=(l+r)/2;
		Build(id*2,l,mid),Build(id*2+1,mid+1,r);
	}
	void Build(const int _N,const bool _IS_MX){N=_N,SZ=0,IS_MX=_IS_MX;Build(1,0,N-1);}
	inline void Maintain(const int id)
	{
		D[id]=(IS_MX?max(D[id*2],D[id*2+1]):min(D[id*2],D[id*2+1]));
	}
	void Insert(const int id,const int l,const int r,const int loc,const int val)
	{
		if(l==r)
		{
			assert(r==loc);
			S[id].insert(val);
			D[id]=(IS_MX?*S[id].rbegin():*S[id].begin());
			return;
		}
		const int mid=(l+r)/2;
		if(loc<=mid)Insert(id*2,l,mid,loc,val);
		else Insert(id*2+1,mid+1,r,loc,val);
		Maintain(id);
	}
	void Erase(const int id,const int l,const int r,const int loc,const int val)
	{
		if(l==r)
		{
			assert(r==loc);
			multiset<int>::iterator it=S[id].find(val);
			assert(it!=S[id].end());
			S[id].erase(it);
			D[id]=(IS_MX?*S[id].rbegin():*S[id].begin());
			return;
		}
		const int mid=(l+r)/2;
		if(loc<=mid)Erase(id*2,l,mid,loc,val);
		else Erase(id*2+1,mid+1,r,loc,val);
		Maintain(id);
	}
	void Insert(const int loc,const int val){Insert(1,0,N-1,loc,val),++SZ;}
	void Erase(const int loc,const int val){Erase(1,0,N-1,loc,val),--SZ;}
	int Query(const int id,const int l,const int r,const int bl,const int br)const
	{
		if(r<bl||br<l)return IS_MX?-INF:INF;
		if(bl<=l&&r<=br)return D[id];
		const int mid=(l+r)/2;
		const int vl=Query(id*2,l,mid,bl,br),vr=Query(id*2+1,mid+1,r,bl,br);
		return IS_MX?max(vl,vr):min(vl,vr); 
	}
	int Query(const int bl,const int br)const{return Query(1,0,N-1,bl,br);}
};
vector<int>V;
struct LargeSegTree
{
	int W_UPON,W_DOWN;
	SegTree MIN_X,MIN_COST,MAX_X;
	void Build(const int N,const int _W_UPON,const int _W_DOWN)
	{
		MIN_X.Build(N,false);
		MIN_COST.Build(N,false);
		MAX_X.Build(N,false);
		W_UPON=_W_UPON;
		W_DOWN=_W_DOWN;
	}
	inline int GetCost(const QueryType &q)const{return (W_UPON*V[q.UPON]+W_DOWN*V[q.DOWN])-max(0,V[q.X]-V[q.UPON],V[q.DOWN]-V[q.X]);}
	inline int GetMinXValue(const QueryType &q)const{return V[q.X]+GetCost(q);}
	inline int GetMaxXValue(const QueryType &q)const{return -V[q.X]+GetCost(q);}
	void Insert(const QueryType &q)
	{
		MIN_X.Insert(q.X,GetMinXValue(q));
		MIN_COST.Insert(q.X,GetCost(q));
		MAX_X.Insert(q.X,GetMaxXValue(q));
	}
	void Erase(const QueryType &q)
	{
		MIN_X.Erase(q.X,GetMinXValue(q));
		MIN_COST.Erase(q.X,GetCost(q));
		MAX_X.Erase(q.X,GetMaxXValue(q));
	}
	int QueryMinX(const int bl,const int br)const{return MIN_X.Query(bl,br);}
	int QueryMinCost(const int bl,const int br)const{return MIN_COST.Query(bl,br);}
	int QueryMaxX(const int bl,const int br)const{return MAX_X.Query(bl,br);}
	int Size()const
	{
		const int ans=MIN_X.SZ;
		assert(ans==MIN_COST.SZ&&ans==MAX_X.SZ);
		return ans; 
	}
}SEG[3];
int N,M,H[50000],ANS[50000];
QueryType GetQueryType(const int i){assert(1<=i&&i<N-1);return QueryType(i,H[i],max(H[i-1],H[i+1]),min(H[i-1],H[i+1]));}
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
	if(N==2)return;
	assert(N>=3);
	getmin(ANS[0],ANS[N-1],(Dif(N-1,1)+Dif(N-2,0))-(Dif(0,1)+Dif(N-2,N-1)));
	getmin(ANS[0],ANS[1],Dif(0,2)-Dif(1,2));
	getmin(ANS[N-1],ANS[N-2],Dif(N-3,N-1)-Dif(N-3,N-2));
	for(int i=2;i+1<N;i++)getmin(ANS[0],ANS[i],(Dif(i,1)+Dif(i-1,0)+Dif(0,i+1))-(Dif(0,1)+Dif(i-1,i)+Dif(i,i+1)));
	for(int i=1;i+1<N-1;i++)getmin(ANS[N-1],ANS[i],(Dif(i-1,N-1)+Dif(N-1,i+1)+Dif(N-2,i))-(Dif(i-1,i)+Dif(i,i+1)+Dif(N-2,N-1)));
	for(int i=2;i+1<N;i++)getmin(ANS[i-1],ANS[i],(Dif(i-2,i)+Dif(i-1,i+1))-(Dif(i-2,i-1)+Dif(i,i+1)));
	SEG[0].Build(M,0,1);
	SEG[1].Build(M,0,0);
	SEG[2].Build(M,-1,0);
	multiset<pair<int,int> >m1,m2,m3;
	for(int _qi=0;_qi<(int)Q.size();_qi++)
	{
		assert((int)(m1.size()+m2.size()+m3.size())==_qi&&SEG[0].Size()+SEG[1].Size()+SEG[2].Size()==_qi);
		const QueryType &q=Q[_qi];
//		printf("id=%d\n",q.ID);
		while(!m1.empty()&&m1.begin()->first<=q.X)
		{
			const int i=m1.begin()->second;
			SEG[1].Insert(GetQueryType(i)),m2.insert(make_pair(max(H[i-1],H[i+1]),i));
			SEG[0].Erase(GetQueryType(i)),m1.erase(m1.begin());
		}
		while(!m2.empty()&&m2.begin()->first<=q.X)
		{
			const int i=m2.begin()->second;
			SEG[2].Insert(GetQueryType(i)),m3.insert(make_pair(i,i));
			SEG[1].Erase(GetQueryType(i)),m2.erase(m2.begin());
		}
		bool erased[2]={true,true};
		for(int d=0;d<2;d++)
		{
			if(d==0?(q.ID-1>0):(q.ID+1<N-1))
			{
				multiset<pair<int,int> >::iterator it;
				const int i=(d==0?q.ID-1:q.ID+1);
				it=m1.find(make_pair(min(H[i-1],H[i+1]),i));
				if(it!=m1.end()){SEG[0].Erase(GetQueryType(i)),m1.erase(it);goto found_index;}
				it=m2.find(make_pair(max(H[i-1],H[i+1]),i));
				if(it!=m2.end()){SEG[1].Erase(GetQueryType(i)),m2.erase(it);goto found_index;}
				it=m3.find(make_pair(i,i));
				if(it!=m3.end()){SEG[2].Erase(GetQueryType(i)),m3.erase(it);goto found_index;}
				erased[d]=false;
				found_index:;
			}
			else erased[d]=false;
		}
		const int cost=max(0,V[q.X]-V[q.UPON],V[q.DOWN]-V[q.X]);
		{
			const int min_x=SEG[0].QueryMinX(q.UPON,M-1);//min(x+down-cost)
			if(min_x!=INF)getmin(ANS[q.ID],-cost+min_x-V[q.X]-V[q.UPON]);
			const int min_c=SEG[0].QueryMinCost(q.DOWN,q.UPON);//min(down-cost)
			if(min_c!=INF)getmin(ANS[q.ID],-cost+min_c-V[q.X]);
			const int max_x=SEG[0].QueryMaxX(0,q.DOWN);//min(-x+down-cost)
			if(max_x!=INF)getmin(ANS[q.ID],-cost+max_x-V[q.X]+V[q.DOWN]);
		}
		{
			const int min_x=SEG[1].QueryMinX(q.UPON,M-1);//min(x-cost)
			if(min_x!=INF)getmin(ANS[q.ID],-cost+min_x-V[q.UPON]);
			const int min_c=SEG[1].QueryMinCost(q.DOWN,q.UPON);//min(-cost)
			if(min_c!=INF)getmin(ANS[q.ID],-cost+min_c);
			const int max_x=SEG[1].QueryMaxX(0,q.DOWN);//min(-x-cost)
			if(max_x!=INF)getmin(ANS[q.ID],-cost+max_x+V[q.DOWN]);
		}
		{
			const int min_x=SEG[2].QueryMinX(q.UPON,M-1);//min(x-upon-cost)
			if(min_x!=INF)getmin(ANS[q.ID],-cost+min_x+V[q.X]-V[q.UPON]);
			const int min_c=SEG[2].QueryMinCost(q.DOWN,q.UPON);//min(-upon-cost)
			if(min_c!=INF)getmin(ANS[q.ID],-cost+min_c+V[q.X]);
			const int max_x=SEG[2].QueryMaxX(0,q.DOWN);//min(-x-upon-cost)
			if(max_x!=INF)getmin(ANS[q.ID],-cost+max_x+V[q.X]+V[q.DOWN]);
		}
//		assert(0);
		SEG[0].Insert(q),m1.insert(make_pair(q.DOWN,q.ID));
		if(erased[0])SEG[0].Insert(GetQueryType(q.ID-1)),m1.insert(make_pair(min(H[q.ID-2],H[q.ID]),q.ID-1));
		if(erased[1])SEG[0].Insert(GetQueryType(q.ID+1)),m1.insert(make_pair(min(H[q.ID],H[q.ID+2]),q.ID+1));
	}
//	assert(0);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&H[i]);
		for(int i=0;i<N;i++)ANS[i]=0;
		{
			Discretize();
			Q.clear();
			for(int i=1;i+1<N;i++)Q.push_back(GetQueryType(i));
			sort(Q.begin(),Q.end()); 
			Solve();
		}
//		if(false)
		{
			for(int i=0;i<N;i++)H[i]=-V[H[i]];
			Discretize();
			Q.clear();
			for(int i=1;i+1<N;i++)Q.push_back(GetQueryType(i));
			for(int i=0;i<(int)Q.size();i++)Q[i].ID*=-1;
			sort(Q.begin(),Q.end());
			for(int i=0;i<(int)Q.size();i++)Q[i].ID*=-1;
			Solve();
		}
		long long dif=0;
		for(int i=1;i<N;i++)dif+=Dif(i-1,i);
		for(int i=0;i<N;i++)printf("%lld\n",dif+ANS[i]);
	}
	return 0;
}
