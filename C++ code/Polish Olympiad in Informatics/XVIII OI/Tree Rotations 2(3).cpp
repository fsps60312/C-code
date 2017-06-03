#include<cstdio>
#include<cassert>
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
	int S[1000001],N,LOWBIT[1000001];
	void Clear(const int _N){N=_N;for(int i=1;i<=N;i++)S[i]=0,LOWBIT[i]=i&(-i);}
	inline void Add(int i,const int v){while(i<=N)S[i]+=v,i+=LOWBIT[i];}
	inline int Query(int i)const{int ans=0;while(i)ans+=S[i],i-=LOWBIT[i];return ans;}
}BIT;
int CH[2000000][2],VAL[2000000],SZ[2000000],NSZ;
int BuildTree()
{
	static int stk[2000000],state[2000000];
	int ssz=-1;
	++ssz,stk[ssz]=++NSZ,state[ssz]=0;
	int ret_val;
	while(ssz>=0)
	{
		const int ans=stk[ssz];
		int &st=state[ssz];
//		printf("ans=%d,st=%d\n",ans,st);
		switch(st)
		{
			case 0:
			{
				VAL[ans]=GetInt();
				if(VAL[ans])SZ[ans]=1,ret_val=ans,--ssz;
				else
				{
					++ssz,stk[ssz]=++NSZ,state[ssz]=0;
					++st;
				}
			}break;
			case 1:
			{
				SZ[ans]=SZ[CH[ans][0]=ret_val];
				++ssz,stk[ssz]=++NSZ,state[ssz]=0;
				++st;
			}break;
			case 2:
			{
				SZ[ans]+=SZ[CH[ans][1]=ret_val];
				ret_val=ans;
				--ssz;
			}break;
			default:assert(0);break;
		}
	}
	return ret_val;
}
LL ANS;
int S[2000000],SSZ;
inline void Swap(int &a,int &b){static int c;c=a,a=b,b=c;}
inline LL min(const LL a,const LL b){return a<b?a:b;}
void Solve(const int _o)
{
	static int stk[2000000],state[2000000],L[2000000],R[2000000];
	int ssz=-1;
	++ssz,stk[ssz]=_o,state[ssz]=0;
	while(ssz>=0)
	{
		const int o=stk[ssz];
		int &st=state[ssz];
		switch(st)
		{
			case 0:
			{
				if(SZ[o]==1)S[++SSZ]=VAL[o],BIT.Add(VAL[o],1),--ssz;
				else
				{
					if(SZ[CH[o][0]]>SZ[CH[o][1]])Swap(CH[o][0],CH[o][1]);
					L[o]=SSZ+1;
					++st;
					++ssz,stk[ssz]=CH[o][0],state[ssz]=0;
				}
			}break;
			case 1:
			{
				const int r=R[o]=SSZ;
				for(int i=L[o];i<=r;i++)BIT.Add(S[i],-1);
				++st;
				++ssz,stk[ssz]=CH[o][1],state[ssz]=0;
			}break;
			case 2:
			{
				LL ta=0LL;
				const int r=R[o];
				for(int i=L[o];i<=r;i++)ta+=BIT.Query(S[i]);
				ANS+=min(ta,(LL)SZ[CH[o][0]]*SZ[CH[o][1]]-ta);
				for(int i=L[o];i<=r;i++)BIT.Add(S[i],1);
				--ssz;
			}break;
			default:assert(0);break;
		}
	}
}
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	BIT.Clear(N);
	NSZ=SSZ=-1;
	Solve(BuildTree());
	printf("%lld\n",ANS);
	return 0;
}
