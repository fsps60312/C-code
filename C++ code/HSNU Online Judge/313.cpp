#include<cstdio>
#include<cassert>
#include<vector>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
unsigned int MyRand()
{
	static unsigned int seed=20151230;
	seed*=0xdefaced,seed+=163019;
	return seed+=seed>>20;
}
int N,S[100000];
struct Node
{
	Node *ch[2];
	int i,sum,sz;
	unsigned int pri;
	Node(const int _i):ch{NULL,NULL},i(_i),sum(S[_i]),sz(1),pri(MyRand()){}
	Node(Node* &o):ch{o->ch[0],o->ch[1]},i(o->i),sum(o->sum),sz(o->sz),pri(o->pri){}
}*ROOT[100001];
int Sum(Node* &o){return o?o->sum:0;}
int Sz(Node* &o){return o?o->sz:0;}
void Maintain(Node* &o){o->sum=Sum(o->ch[0])+S[o->i]+Sum(o->ch[1]),o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);}
Node *Merge(Node *a,Node *b)
{
	if(!a||!b)return a?a:b;
	if(a->pri>b->pri)
	{
		Node *ans=new Node(a);
		ans->ch[1]=Merge(a->ch[1],b);
		Maintain(ans);
		return ans;
	}
	else
	{
		Node *ans=new Node(b);
		ans->ch[0]=Merge(a,b->ch[0]);
		Maintain(ans);
		return ans;
	}
}
bool OnLeft(const int i1,const int i2){return S[i1]!=S[i2]?S[i1]<S[i2]:i1<i2;}
void Split(Node *o,Node* &a,Node* &b,const int i)
{
	if(!o){a=b=NULL;return;}
//	printf("(%d,%d)",i,o->i);
	if(OnLeft(i,o->i))b=new Node(o),Split(o->ch[0],a,b->ch[0],i),Maintain(b);
	else a=new Node(o),Split(o->ch[1],a->ch[1],b,i),Maintain(a);
}
int Query(Node* &o,const int i,const bool is_sum)
{
	if(!o)return 0;
	const int left_val=(is_sum?Sum(o->ch[0])+S[o->i]:Sz(o->ch[0])+1);
	if((o->i)==i)return left_val;
	else if(OnLeft(i,o->i))return Query(o->ch[0],i,is_sum);
	else return left_val+Query(o->ch[1],i,is_sum);
}
void Extract(Node* &o,vector<int>&ans)
{
	if(!o)return;
	Extract(o->ch[0],ans);
	ans.push_back(o->i);
	Extract(o->ch[1],ans);
}
void Print(Node* &o)
{
	vector<int>ans;
	Extract(o,ans);
	for(const auto v:ans)printf(" %d",v);puts("");
}
vector<int>ORDER;
int main()
{
//	freopen("in.txt","r",stdin);
	static int casecount;scanf(1,"%d",&casecount);
	while(casecount--)
	{
		static int querycount;scanf(2,"%d%d",&N,&querycount);
		for(int i=0;i<N;i++)scanf(1,"%d",&S[i]);
		ROOT[0]=NULL;
		for(int i=0;i<N;i++)
		{
			static Node *a,*b;
			Split(ROOT[i],a,b,i);//puts("");
//			printf("l,sz=%d,sum=%d:",Sz(a),Sum(a)),Print(a),puts("");
//			printf("r,sz=%d,sum=%d:",Sz(b),Sum(b)),Print(b),puts("");
			ROOT[i+1]=Merge(a,Merge(new Node(i),b));
		}
		for(int i=0,sum=0;i<=N;sum+=S[i++])assert(Sum(ROOT[i])==sum),assert(Sz(ROOT[i])==i);//,printf("%d:",i),Print(ROOT[i]);
		ORDER.clear();
		Extract(ROOT[N],ORDER);
		assert((int)ORDER.size()==N);
		for(int i=1;i<N;i++)assert(OnLeft(ORDER[i-1],ORDER[i]));
//		printf("sum=%d, %d\n",Sum(ROOT[N]),Sum(ROOT[N]->ch[1]));
//		for(int i=0;i<N;i++)printf("(%d,%d)sum=%d,ori=%d\n",ORDER[i],S[ORDER[i]],Query(ROOT[N],ORDER[i],true),S[i]);
		vector<int>result;
		while(querycount--)
		{
			static int l,r,s;scanf(3,"%d%d%d",&l,&r,&s);
			int lans=-1,rans=N-1;
			while(lans<rans)
			{
				const int mid=(lans+rans+1)/2;
				const int mid_val=Query(ROOT[r],ORDER[mid],true)-Query(ROOT[l-1],ORDER[mid],true);
//				printf("(%d,%d,%d):%d\n",lans,mid,rans,mid_val);
				if(mid_val<=s)lans=mid;
				else rans=mid-1;
			}
			if(rans==-1)result.push_back(0);
			else result.push_back(Query(ROOT[r],ORDER[rans],false)-Query(ROOT[l-1],ORDER[rans],false));
		}
		int ans=0;
		for(int i=0;i<(int)result.size();i++)ans^=result[i]+i+1;//,printf("ans=%d\n",result[i]);
		printf("%d\n",ans);
	}
	return 0;
}
