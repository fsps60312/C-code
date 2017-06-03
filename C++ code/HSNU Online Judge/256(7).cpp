#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
void getmax(LL &a,const LL b){if(b>a)a=b;}
int B,N,D,M;
int X[100000][3];
struct Deq
{
	int s[100000],l,r;
	void clear(){l=0,r=-1;}
	void push_back(const int v){s[++r]=v;}
	int pop_front(){return s[l++];}
	int back(){return s[r];}
	int front(){return s[l];}
	bool empty(){return r<l;}
	int size(){return r-l+1;}
}DEQ;
bool Cmp1(const int a,const int b){return X[a][0]<X[b][0];}
LL Solve1()
{
	vector<int>idx;
	for(int i=0;i<N;i++)idx.push_back(i);
	sort(idx.begin(),idx.end(),Cmp1);
	DEQ.clear();
	LL ans=0LL;
	for(const auto i:idx)
	{
		while(!DEQ.empty()&&X[DEQ.front()][0]<X[i][0]-D)DEQ.pop_front();
		ans+=DEQ.size();
		DEQ.push_back(i);
	}
	return ans;
}
struct Seg
{
	int s[600000];
	void Build(const int id,const int l,const int r)
	{
		s[id]=0;
		if(l==r)return;
		const int mid=(l+r)/2;
		Build(id*2,l,mid),Build(id*2+1,mid+1,r);
	}
	void Add(const int id,const int l,const int r,const int bl,const int br,const int v)
	{
		if(l>br||r<bl)return;
		if(bl<=l&&r<=br){s[id]+=v;return;}
		const int mid=(l+r)/2;
		Add(id*2,l,mid,bl,br,v),Add(id*2+1,mid+1,r,bl,br,v);
	}
	int Query(const int id,const int l,const int r,const int loc)
	{
		if(l==r)return s[id];
		const int mid=(l+r)/2;
		if(loc<=mid)return s[id]+Query(id*2,l,mid,loc);
		else return s[id]+Query(id*2+1,mid+1,r,loc);
	}
}SEG;
bool Cmp2(const int a,const int b)
{
	const int va=X[a][0]+X[a][1],vb=X[b][0]+X[b][1];
	return va!=vb?va<vb:X[a][2]<X[b][2];
}
LL Solve2()
{
	vector<int>idx;
	for(int i=0;i<N;i++)idx.push_back(i);
	sort(idx.begin(),idx.end(),Cmp2);
	SEG.Build(1,1,M*2-1);
	LL ans=0LL;
	DEQ.clear();
	for(const auto i:idx)
	{
		while(!DEQ.empty()&&(X[i][0]+X[i][1])-(X[DEQ.front()][0]+X[DEQ.front()][1])>D)
		{
			const int v=DEQ.pop_front();
			const int mid=M+X[v][0]-X[v][1];
			SEG.Add(1,1,M*2-1,mid-D,mid+D,-1);
		}
		const int mid=M+X[i][0]-X[i][1];
		int ta=ans;
		ans+=SEG.Query(1,1,M*2-1,mid);
		SEG.Add(1,1,M*2-1,mid-D,mid+D,1);
		DEQ.push_back(i);
	}
	return ans;
}
int GetValue(const int h,const int i){assert(X[i][2]<=h&&D>=h-X[i][2]);return X[i][0]+X[i][1]+D-(h-X[i][2]);}
int rGetValue(const int h,const int i){assert(X[i][2]<=h&&D>=h-X[i][2]);return X[i][0]+X[i][1]-(D-(h-X[i][2]));}
int H;
bool rCmp2(const int a,const int b)
{
	const int va=X[a][0]+X[a][1],vb=X[b][0]+X[b][1];
	return va!=vb?va>vb:X[a][2]>X[b][2];
}
vector<int>REMOVE[75*2-1];
void GoUp(const int h,LL &ans,vector<int>&idx)
{
	sort(idx.begin(),idx.end(),Cmp2);
	SEG.Build(1,1,M*2-1);
	for(int i=0;i<M*2-1;i++)REMOVE[i].clear();
	int now=0;
	for(auto i:idx)
	{
		while(now<=X[i][0]+X[i][1])
		{
			for(auto v:REMOVE[now])
			{
				const int d=D-(h-X[v][2]);
				assert(d>=0);
				const int mid=M+X[v][0]-X[v][1];
				SEG.Add(1,1,M*2-1,mid-d,mid+d,-1);
			}
			REMOVE[now++].clear();
		}
		const int d=D-(h-X[i][2]);
		assert(d>=0);
		const int mid=M+X[i][0]-X[i][1];
		if(X[i][2]==h)ans+=SEG.Query(1,1,M*2-1,mid);
		const int tmp=GetValue(h,i)+1;
		if(tmp<M*2-1)REMOVE[tmp].push_back(i);
		SEG.Add(1,1,M*2-1,mid-d,mid+d,1);
	}
}
void GoDown(const int h,LL &ans,vector<int>idx)
{
	sort(idx.begin(),idx.end(),rCmp2);
	SEG.Build(1,1,M*2-1);
	for(int i=0;i<M*2-1;i++)REMOVE[i].clear();
	int now=M*2-2;
	for(auto i:idx)
	{
		while(now>=X[i][0]+X[i][1])
		{
			for(auto v:REMOVE[now])
			{
				const int d=D-(h-X[v][2]);
				assert(d>=0);
				const int mid=M+X[v][0]-X[v][1];
				SEG.Add(1,1,M*2-1,mid-d,mid+d,-1);
			}
			REMOVE[now--].clear();
		}
		const int d=D-(h-X[i][2]);
		assert(d>=0);
		const int mid=M+X[i][0]-X[i][1];
		if(X[i][2]==h)ans+=SEG.Query(1,1,M*2-1,mid);
		else
		{
			const int tmp=rGetValue(h,i)-1;
			if(tmp>=0)REMOVE[tmp].push_back(i);
			SEG.Add(1,1,M*2-1,mid-d,mid+d,1);
		}
	}
}
LL Solve3()
{
	LL ans=0LL;
	for(int &h=H=0;h<M;h++)
	{
		vector<int>idx;
		for(int i=0;i<N;i++)if(X[i][2]<=h&&h-X[i][2]<=D)idx.push_back(i);
		GoUp(h,ans,idx);
		GoDown(h,ans,idx);
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d%d",&B,&N,&D,&M)==4)
	{
		for(int i=0;i<N;i++)for(int j=0;j<B;j++)scanf("%d",&X[i][j]),X[i][j]--;
		if(B==1)printf("%lld\n",Solve1());
		else if(B==2)printf("%lld\n",Solve2());
		else if(B==3)printf("%lld\n",Solve3());
		else assert(0);
		break;
	}
	return 0;
}
