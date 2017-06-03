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
struct Bit
{
	int s[297][297][297],n,mid;
	void clear(const int _m){n=(mid=_m)*2+1;for(int i=0;i<n*n*n;i++)s[i/n/n][i/n%n][i%n]=0;}
	int lowbit(const int i){return i&(-i);}
	void Add3D(const int a,const int b,int c,const int v){while(c<n)s[a][b][c]+=v,c+=lowbit(c+1);}
	void Add2D(const int a,int b,const int c,const int v){while(b<n)Add3D(a,b,c,v),b+=lowbit(b+1);}
	void Add1D(int a,const int b,const int c,const int v){while(a<n)Add2D(a,b,c,v),a+=lowbit(a+1);}
	int Query3D(const int a,const int b,int c){int ans=0;while(c>=0)ans+=s[a][b][c],c-=lowbit(c+1);return ans;}
	int Query2D(const int a,int b,const int c){int ans=0;while(b>=0)ans+=Query3D(a,b,c),b-=lowbit(b+1);return ans;}
	int Query1D(int a,const int b,const int c){int ans=0;while(a>=0)ans+=Query2D(a,b,c),a-=lowbit(a+1);return ans;}
	int F1(const int i){return mid+X[i][0]+X[i][1]-X[i][2];}
	int F2(const int i){return mid+X[i][0]-X[i][1]+X[i][2];}
	int F3(const int i){return mid+X[i][0]-X[i][1]-X[i][2];}
	void CheckValidity(const int i){assert(F1(i)>=0&&F1(i)<n&&F2(i)>=0&&F2(i)<n&&F3(i)>=0&&F3(i)<n);}
	void Add(const int i,const int v){CheckValidity(i);Add1D(F1(i),F2(i),F3(i),v);}
	int Query(const int i)
	{
		CheckValidity(i);
		int a1=max(0,F1(i)-D),b1=max(0,F2(i)-D),c1=max(0,F3(i)-D),a2=min(n-1,F1(i)+D),b2=min(n-1,F2(i)+D),c2=min(n-1,F3(i)+D);
		return Query1D(a2,b2,c2)-Query1D(a1-1,b2,c2)-Query1D(a2,b1-1,c2)-Query1D(a2,b2,c1-1)
		       +Query1D(a2,b1-1,c1-1)+Query1D(a1-1,b2,c1-1)+Query1D(a1-1,b1-1,c2)-Query1D(a1-1,b1-1,c1-1);
	}
}BIT;
int GetSum(const int a){return X[a][0]+X[a][1]+X[a][2];}
bool Cmp3(const int a,const int b){return GetSum(a)<GetSum(b);}
LL Solve3()
{
	vector<int>idx;
	for(int i=0;i<N;i++)idx.push_back(i);
	sort(idx.begin(),idx.end(),Cmp3);
	BIT.clear(M*2-2);
	DEQ.clear();
	LL ans=0LL;
	for(auto i:idx)
	{
		while(!DEQ.empty()&&GetSum(i)-GetSum(DEQ.front())>D)BIT.Add(DEQ.pop_front(),-1);
		ans+=BIT.Query(i);
		DEQ.push_back(i);
		BIT.Add(i,1);
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
