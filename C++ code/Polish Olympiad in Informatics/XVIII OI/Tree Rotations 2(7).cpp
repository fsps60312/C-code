#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
#include<set>
using namespace std;
typedef long long LL;
inline char GetChar()
{
//	return getchar();
//	puts("getchar");
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
//	puts("getint");
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
	inline void Add(int i){while(i<=N)++S[i],i+=i&(-i);}
	inline void Remove(int i){while(i<=N)--S[i],i+=i&(-i);}
	inline int Query(int i)const{int ans=0;while(i)ans+=S[i],i-=i&(-i);return ans;}
}BIT;
LL ANS;
int S[2000000],SSZ;
bool VIS[1000001];
struct Node
{
	Node *lch,*rch;
	int v;
	LL sz;
	Node():v(GetInt())
	{
		if(v)
		{
			sz=1;
			assert(!VIS[v]);
			VIS[v]=true;
		}
		else
		{
			lch=new Node();
			rch=new Node();
			sz=lch->sz+rch->sz;
		}
		ANS+=sz;
	}
	void Solve1(int type)
	{
		if(sz==1){S[++SSZ]=v;if(type==1)BIT.Add(v);return;}
		if(lch->sz>rch->sz)swap(lch,rch);
		const int l=SSZ;
		lch->Solve1(-1);
		const int r=SSZ;
		rch->Solve1(1);
		LL ta=0LL;
		for(int i=l+1;i<=r;++i)ta+=BIT.Query(S[i]);
		ANS+=min(ta,((lch->sz)*(rch->sz))-ta);
		if(type==1)
		{
			for(int i=l+1;i<=r;++i)BIT.Add(S[i]);
		}
		else if(type==-1)
		{
			for(int i=r+1;i<=SSZ;++i)BIT.Remove(S[i]);
		}
	}
	void Solve2(vector<int>&s0)
	{
//		puts("pass");
		assert(s0.empty());
		if(sz==1){s0.push_back(v);return;}
		if(lch->sz>rch->sz)swap(lch,rch);
		vector<int>s1,s2;
		lch->Solve2(s1),rch->Solve2(s2);
		LL ta=0LL;
		for(int i=0;i<(int)s1.size();++i)ta+=(upper_bound(s2.begin(),s2.end(),s1[i])-s2.begin());
		ANS+=min(ta,((lch->sz)*(rch->sz))-ta);
		for(int i=0,j=0;i<(int)s1.size()||j<(int)s2.size();)
		{
			if(j==(int)s2.size()||(i<(int)s1.size()&&s1[i]<s2[j]))s0.push_back(s1[i]),++i;
			else s0.push_back(s2[j]),++j;
		}
		assert(s0.size()==s1.size()+s2.size());
		assert(0<s0[0]);
		for(int i=1;i<(int)s0.size();++i)assert(s0[i-1]<=s0[i]);
	}
};
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	N=GetInt();
	for(int i=1;i<=N;i++)VIS[i]=false;
//	assert(N<=5000);
	ANS=0LL;
	Node *root=new Node();
	vector<int>s;
	if(ANS<=50*N)ANS=0LL,root->Solve2(s);
	else ANS=0LL,BIT.Clear(N),SSZ=-1,root->Solve1(0);
	printf("%lld\n",ANS);
//	assert(SSZ+1==N);
	return 0;
}
