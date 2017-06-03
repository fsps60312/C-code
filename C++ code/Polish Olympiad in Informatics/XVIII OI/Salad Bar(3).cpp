#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;
inline void getmax(int &a,const int b){if(a<b)a=b;}
//void getmin(int &a,const int b){if(b<a)a=b;}
inline char ReadChar()
{
	static char buf[1<<20],*p=buf,*end=buf;
	if(p==end)
	{
		if((end=buf+fread(buf,1,1<<20,stdin))==buf)return EOF;
		p=buf;
	}
	return *p++;
}
struct SegTree
{
	int S[1000000*4];
	void Clear(const int N){for(int i=0;i<N*4;i++)S[i]=0;}
	int bl,br,val;
	inline void Modify(const int id,const int l,const int r,const int _bl,const int _br,const int _val)
	{
		bl=_bl,br=_br,val=_val;
		Modify(id,l,r);
	}
	void Modify(const int id,const int l,const int r)
	{
		if(bl<=l&&r<=br){getmax(S[id],val);return;}
		const int mid=(l+r)>>1;
		if(bl<=mid)Modify(id<<1,l,mid,bl,br,val);
		if(br>=mid+1)Modify((id<<1)+1,mid+1,r,bl,br,val);
	}
	inline int Query(int id,int l,int r,const int loc)
	{
		int ans=S[id];
		do
		{
			const int mid=(l+r)>>1;
			if(loc<=mid)id<<=1,r=mid;
			else ++(id<<=1),l=mid+1;
			getmax(ans,S[id]);
		}while(l<r);
		return ans;
	}
}SEG;
int N,SUM[1000001],R[1000001],L[1000001];
char S[1000001+1000];
inline void ReadInt(int &v)
{
	char c=ReadChar();
	while(c<'0'||'9'<c)c=ReadChar();
	v=0;
	while('0'<=c&&c<='9')v=v*10+(c-'0'),c=ReadChar();
}
int main()
{
//	freopen("in.txt","r",stdin);
	ReadInt(N);
//	printf("N=%d\n",N);
	{
		char *p=S,c=ReadChar();
//		printf("c=\"%c\"",c);
		while(c!='j'&&c!='p')c=ReadChar();
		for(*p=c;*p!=EOF;*(++p)=ReadChar());
	}
	SUM[0]=0;
	for(int i=0;i<N;i++)SUM[i+1]=SUM[i]+(S[i]=='p'?1:-1);
	static int stk[1000001];
	int last=-1;
	for(int i=N;i>=0;i--)
	{
		while(last!=-1&&SUM[i]<=SUM[stk[last]])--last;
		if(last==-1)R[i]=N;
		else R[i]=stk[last]-1;
		stk[++last]=i;
	}
	last=-1;
	for(int i=0;i<=N;i++)
	{
		while(last!=-1&&SUM[stk[last]]<=SUM[i])--last;
		if(last==-1)L[i]=0;
		else L[i]=stk[last]+1;
		stk[++last]=i;
	}
	static int cnt[1000001];
	for(int i=0;i<=N;i++)cnt[i]=0;
	for(int i=0;i<=N;i++)cnt[R[i]]++;
	for(int i=1;i<=N;i++)cnt[i]+=cnt[i-1];
	static int order[1000001];
	for(int i=N;i>=0;i--)order[--cnt[R[i]]]=i;
	int ans=0;
	SEG.Clear(N);
	for(int i=0,j=0;i<=N;i++)
	{
		const int id=order[i];
		for(;j<=R[id];j++)SEG.Modify(1,0,N,L[j],j,j);
		getmax(ans,SEG.Query(1,0,N,id)-id);
	}
	printf("%d\n",ans);
	return 0;
}
