#include<cstdio>
using namespace std;
const int INF=2147483647;
inline void getmin(int &a,const int b){if(b<a)a=b;}
inline void getmax(int &a,const int b){if(b>a)a=b;}
int N,M,T[100000],J[100000],I[100000];
bool Solve(const int tick)
{
	static int counts_first[100000],counts_second[100000],counts_size;
	counts_size=0;
	if(true)
	{
		static int sot[100001],next[100000],nsz,vals[100000];
		nsz=0;
		for(int i=1;i<=M;i++)sot[i]=-1;
		for(int i=0;i<tick;i++)
		{
			vals[nsz]=I[i]+1;
			next[nsz]=sot[T[i]];
			sot[T[i]]=nsz;
			nsz++;
		}
		for(int i=1;i<=M;i++)
		{
			for(int cur=sot[i];cur!=-1;cur=next[cur])counts_first[counts_size]=i,counts_second[counts_size]=vals[cur],counts_size++;
		}
	}
	for(int i=1;i<counts_size;i++)if(counts_first[i]==counts_first[i-1]&&counts_second[i]!=counts_second[i-1])return false;
	static int mn[100001],mx[100001];
	for(int i=1;i<=N;i++)mn[i]=INF,mx[i]=-INF;
	for(int i=0;i<tick;i++)getmin(mn[J[i]],T[i]),getmax(mx[J[i]],T[i]);
	static int enter[100002],leave[100002];
	for(int i=1;i<=M+1;i++)enter[i]=leave[i]=0;
	for(int i=1;i<=N;i++)if(mn[i]!=INF)enter[mn[i]]++,leave[mx[i]+1]++;
	int certain=0,canleave=0,uncertain=0,leaved=0;
	for(int i=0,j=1;i<counts_size;i++)
	{
		const int cf=counts_first[i],cs=counts_second[i];
		for(;j<=cf;j++)
		{
			const int v=(enter[j]<uncertain?enter[j]:uncertain);
			uncertain-=v,certain+=v,enter[j]-=v;
			certain+=enter[j];
			certain-=leave[j],canleave+=leave[j];
		}
		while(certain+canleave+uncertain<cs)uncertain++;
		while(certain+canleave+uncertain>cs)
		{
			if(canleave)canleave--,leaved++;
			else
			{
				if(!uncertain)return false;
				uncertain--,leaved++;
			}
		}
	}
	return certain+uncertain+canleave+leaved<=N;
}
inline int readchar() {
    const int n = 1048576;
    static char buf[n];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, n, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline void ReadInt(int &v)
{
	const int zero='0',nine='9';
	int c=readchar();
	while(c<zero||c>nine)c=readchar();
	v=0;
	while(c>=zero&&c<=nine)v=v*10+(c-zero),c=readchar();
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;
	ReadInt(testcount);
	while(testcount--)
	{
		ReadInt(N),ReadInt(M);
		for(int i=0;i<M;i++)ReadInt(T[i]),ReadInt(J[i]),ReadInt(I[i]);
		int l=0,r=M;
		while(l<r)
		{
			const int mid=(l+r+1)/2;
			if(Solve(mid))l=mid;
			else r=mid-1;
		}
		printf("%d\n",r);
	}
	return 0;
}
