#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
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
int GetInt()
{
	char c=GetChar();
	while(c<'0'||'9'<c)c=GetChar();
	int v=0;
	while('0'<=c&&c<='9')v=v*10+(c-'0'),c=GetChar();
	return v;
}
struct Deq
{
	int S[400001],L,R;
	inline void Clear(){L=0,R=-1;}
	inline bool Empty()const{return R<L;}
	inline int Size()const{return R-L+1;}
	inline void PushBack(const int v){S[++R]=v;}
	inline void PopBack(){--R;}
	inline void PopFront(){++L;}
	inline int Front()const{return S[L];}
	inline int Back()const{return S[R];}
	inline int operator[](const int i){return S[L+i];}
}DEQ;
inline void getmin(int &a,const int b){if(b<a)a=b;}
int N,Z[400000],M;
char S[400000];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount=GetInt();
	while(testcount--)
	{
		N=-1;
		do
		{
			S[++N]=GetChar();
		}while('a'<=S[N]&&S[N]<='z');
		S[N*2-1]='\0';
		for(int i=N-1;i>=0;i--)
		{
			S[i*2]=S[i];
			if(i)S[i*2-1]='.';
		}
		M=N*2-1;
//		printf("S=%s\n",S);
		Z[0]=1;
		for(int i=1,mx=0;i<M;i++)
		{
			if(mx+Z[mx]-1>=i)Z[i]=min(mx+Z[mx]-i,Z[mx*2-i]);
			else Z[i]=1;
			while(i-Z[i]>=0&&i+Z[i]<N*2-1&&S[i-Z[i]]==S[i+Z[i]])++Z[i];
			if(i+Z[i]>=mx+Z[mx])mx=i;
		}
		static int dp[400000];
		dp[0]=0;
		for(int i=1;i<=M;i++)dp[i]=INF;
		DEQ.Clear();
		DEQ.PushBack(0);
		for(int i=1;i<=M;i++)
		{
			const int loc=(i-1)-Z[i-1]+1;
			int l=0,r=DEQ.Size();
			for(int mid;l<r;)
			{
				mid=(l+r)>>1;
				if(DEQ[mid]<loc)l=++mid;
				else r=mid;
			}
//			assert(r<DEQ.Size());
			const int val=dp[DEQ[r]];
			getmin(dp[i],val+1);
			if(i%2&&i<N*2-1)getmin(dp[i+1],val+1);
			while(!DEQ.Empty()&&dp[DEQ.Back()]>=dp[i])DEQ.PopBack();
			DEQ.PushBack(i);
		}
		printf("%d\n",dp[M]);
	}
	return 0;
}
