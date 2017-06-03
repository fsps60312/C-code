#include<cstdio>
#include<Vector>
using namespace std;
int T,N,M,DEG[10000],VIS[10000];
vector<int>AD[10000];
struct Deq
{
	vector<int>bse;
	int l,r;
	Deq(){bse.resize(2);Clear();}
	int Sz(){return ((r-l+1)+bse.size())%bse.size();}
	void Clear(){l=0,r=-1;}
	int Idx(int i){return (i%Sz()+Sz())%Sz();}
	int Front(int idx=0){return bse[Idx(l+idx)];}
	int Back(int idx=0){return bse[Idx(r-idx)];}
	int &operator[](int idx){return bse[Idx(l+idx)];}
	void ExpandSz()
	{
		static vector<int>v;
		v.resize(bse.size()*2);
		static int sz;sz=Sz();
		for(int i=0;i<sz;i++)v[i]=(*this)[i];
		l=0,r=sz-1;
		bse=v;
	}
	void PushFront(int v)
	{
		if(Sz()+1==bse.size())ExpandSz();
		bse[l=Idx(l-1)]=v;
	}
	void PushBack(int v)
	{
		if(Sz()+1==bse.size())ExpandSz();
		bse[r=Idx(r+1)]=v;
	}
	Deq(int a,int b){bse.resize(2);Clear();PushBack(a);PushBack(b);}
	int A(int idx=0){return Front(idx);}
	int B(int idx=0){return Back(idx);}
	int To(int from){return from!=A()?A():B();}
	void Merge(Deq &d)
	{
		if(A()==d.A())for(int i=0;i<d.Sz();i++)PushFront(d.Front(i));
		if(B()==d.A())for(int i=0;i<d.Sz();i++)PushBack(d.Front(i));
		if(A()==d.B())for(int i=0;i<d.Sz();i++)PushFront(d.Back(i));
		if(B()==d.B())for(int i=0;i<d.Sz();i++)PushBack(d.Back(i));
	}
};
vector<Deq>EDGE;
int To(int u,int i){return EDGE[AD[u][i]].To(u);}
void MergeEdge(int u)
{
	int e=AD[u][0];
	int l=To(u,0);
	while(DEG[l]==2)
	{
		e=AD[l][0]!=e?AD[l][0]:AD[l][1];
		l=EDGE[e].To(l);
	}
	Deq ans=EDGE[e];
	int el=e,er;
	int r=EDGE[e].To(l);
	while(DEG[r]==2)
	{
		e=AD[r][0]!=e?AD[r][0]:AD[r][1];
		r=EDGE[e].To(r);
		ans.Merge(EDGE[e]);
		er=e;
	}
	int sz=EDGE.size();
	EDGE.push_back(ans);
	for(int i=0;i<AD[l].size();i++)if(AD[l][i]==el)
	{
		AD[l][i]=sz;
		break;
	}
	for(int i=0;i<AD[r].size();i++)if(AD[r][i]==er)
	{
		AD[r][i]=sz;
		break;
	}
}
bool Find33(int u,int &a,int &b)
{
	if(VIS[u])return false;
	VIS[u]=true;
	for(int i=0;i<AD[u].size();i++)
	{
		int j=To(u,i);
		if(DEG[u]==3&&DEG[j]==3)
		{
			a=u,b=j;
			return true;
		}
		if(Find33(),a,b)return true;
	}
	return false;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			scanf("%d%d",&N,&M);
			M+=N;
			for(int i=0;i<N;i++)
			{
				AD[i].clear();
				DEG[i]=0;
				VIS[i]=false;
			}
			EDGE.clear();
			for(int i=0,a,b;i<M;i++)
			{
				scanf("%d%d",&a,&b);
				a--,b--;
				DEG[a]++,DEG[b]++;
				static int sz;sz=EDGE.size();
				AD[a].push_back(sz);
				AD[b].push_back(sz);
				EDGE.push_back(Deq(a,b));
			}
			for(int i=0;i<N;i++)
			{
				if(DEG[i]==2)MergeEdge(i);
//				else root=i;
			}
//			assert(root!=-1);
		}
	}
	return 0;
}
