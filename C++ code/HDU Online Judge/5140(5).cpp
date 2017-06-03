#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
const int INF=2147483647;
struct Staff
{
	int salary,level,age;
	bool operator<(const Staff &s)const{return level<s.level;}
}STAFF[100000];
struct Node
{
	Node *ch[2];
	LL sum;
	Node(const LL _sum):ch{NULL,NULL},sum(_sum){}
	Node(Node *o):ch{o->ch[0],o->ch[1]},sum(o->sum){}
}*S[100001];
Node *Build(const int l,const int r)
{
	Node *ans=new Node(0LL);
	if(l<r)
	{
		const int mid=(l+r)/2;
		ans->ch[0]=Build(l,mid),ans->ch[1]=Build(mid+1,r);
	}
	return ans;
}
Node *Add(Node *o,const int l,const int r,const int loc,const LL &val)
{
	Node *ans=new Node((o->sum)+val);
	if(l<r)
	{
		const int mid=(l+r)/2;
		if(loc<=mid)ans->ch[0]=Add(o->ch[0],l,mid,loc,val),ans->ch[1]=o->ch[1];
		else ans->ch[0]=o->ch[0],ans->ch[1]=Add(o->ch[1],mid+1,r,loc,val);
	}
	return ans;
}
LL Query(Node *o,const int l,const int r,const int bl,const int br)
{
	if(r<bl||br<l)return 0LL;
	if(bl<=l&&r<=br)return o->sum;
	const int mid=(l+r)/2;
	return Query(o->ch[0],l,mid,bl,br)+Query(o->ch[1],mid+1,r,bl,br);
}
vector<int>LRANGE,ARANGE;
int N,M;
void Unique(vector<int>&s){sort(s.begin(),s.end()),s.resize(unique(s.begin(),s.end())-s.begin());}
void Idize(const vector<int>&s,int &val){val=lower_bound(s.begin(),s.end(),val)-s.begin();}
void Discretize()
{
	vector<int>&lv=LRANGE,&av=ARANGE;
	lv.clear(),av.clear(),lv.push_back(-INF);
	for(int i=0;i<N;i++)lv.push_back(STAFF[i].level),av.push_back(STAFF[i].age);
	Unique(lv),Unique(av);
	for(int i=0;i<N;i++)Idize(lv,STAFF[i].level),Idize(av,STAFF[i].age);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)
		{
			Staff &s=STAFF[i];
			scanf("%d%d%d",&s.salary,&s.level,&s.age);
		}
		sort(STAFF,STAFF+N);
		Discretize(),M=ARANGE.size();
		S[0]=Build(0,M-1);
		for(int i=1,j=0;j<N;i++)
		{
			S[i]=S[i-1];
			for(;j<N&&STAFF[j].level==i;j++)S[i]=Add(S[i],0,M-1,STAFF[j].age,STAFF[j].salary);
			if(j==N)assert(i==(int)LRANGE.size()-1);
		}
		int querycount;scanf("%d",&querycount);
		const vector<int>&lv=LRANGE,&av=ARANGE;
		for(LL l1,l2,a1,a2,k=0LL;querycount--;)
		{
			scanf("%lld%lld%lld%lld",&l1,&l2,&a1,&a2);
			l1+=k,l2-=k,a1+=k,a2-=k;
			if(l1>l2)swap(l1,l2);
			if(a1>a2)swap(a1,a2);
			const int sL=(l1<=(LL)*lv.begin()?lv.begin()+1:lower_bound(lv.begin(),lv.end(),(int)l1))-lv.begin();
			const int sR=(l2>=(LL)*lv.rbegin()?lv.end():upper_bound(lv.begin(),lv.end(),(int)l2))-lv.begin()-1;
			const int aL=(a1<=(LL)*av.begin()?av.begin():lower_bound(av.begin(),av.end(),(int)a1))-av.begin();
			const int aR=(a2>=(LL)*av.rbegin()?av.end():upper_bound(av.begin(),av.end(),(int)a2))-av.begin()-1;
			printf("%lld\n",k=Query(S[sR],0,M-1,aL,aR)-Query(S[sL-1],0,M-1,aL,aR));
		}
	}
	return 0;
}
