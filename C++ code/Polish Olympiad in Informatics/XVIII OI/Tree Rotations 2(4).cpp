#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
inline char GetChar()
{
	static char buf[1<<20],*p=buf,*end=buf;
	if(p==end)
	{
		if((end=buf+fread(buf,1,1<<20,stdin))==buf)return EOF;
		p=buf;
	}
	return *p++;
}
inline int GetInt()
{
	char c=GetChar();
	while(c<'0'||'9'<c)c=GetChar();
	int v=0;
	while('0'<=c&&c<='9')v=v*10+(c-'0'),c=GetChar();
	return v;
}
struct Bit
{
	int S[1000001],N;
	void Clear(const int _N){N=_N;for(int i=1;i<=N;i++)S[i]=0;}
	inline void Add(int i,const int v){while(i<=N)S[i]+=v,i+=i&(-i);}
	inline int Query(int i)const{int ans=0;while(i)ans+=S[i],i-=i&(-i);return ans;}
}BIT;
struct Node
{
	Node *ch[2];
	int v;
	LL sz;
}Node_POOL[2000000],*NEW;
inline Node *NewNode(const int _v)
{
	NEW->sz=(NEW->v=_v)?1LL:0LL;
	NEW->ch[0]=NEW->ch[1]=NULL;
	return NEW++;
}
Node *BuildTree()
{
	const int v=GetInt();
	Node *ans=NewNode(v);
	if(v==0)
	{
		ans->ch[0]=BuildTree();
		ans->ch[1]=BuildTree();
		ans->sz=ans->ch[0]->sz+ans->ch[1]->sz;
	}
	return ans;
}
LL ANS;
void Solve(Node *o,vector<int>&s)
{
	if(!o->ch[0]){s.push_back(o->v);BIT.Add(o->v,1);return;}
	if(o->ch[0]->sz>o->ch[1]->sz)swap(o->ch[0],o->ch[1]);
	const int l=s.size();
	Solve(o->ch[0],s);
	const int r=s.size();
	for(int i=l;i<r;i++)BIT.Add(s[i],-1);
	Solve(o->ch[1],s);
	LL ta=0LL;
	for(int i=l;i<r;i++)ta+=BIT.Query(s[i]);
	ANS+=min(ta,((o->ch[0]->sz)*(o->ch[1]->sz))-ta);
	for(int i=l;i<r;i++)BIT.Add(s[i],1);
}
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	NEW=Node_POOL;
	scanf("%d",&N);
	BIT.Clear(N);
	Node *root=BuildTree();
	vector<int>s;
	Solve(root,s);
	printf("%lld\n",ANS);
	assert((int)s.size()==N);
	return 0;
}
