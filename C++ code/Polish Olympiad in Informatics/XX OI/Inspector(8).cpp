#include<cstdio>
#include<algorithm>
using namespace std;
const int INF=2147483647;
inline void getmin(int &a,const int b){if(b<a)a=b;}
inline void getmax(int &a,const int b){if(b>a)a=b;}
int N,M,T[100000],J[100000],I[100000];
bool Solve(const int tick)
{
	static int order[100000];
	if(true)
	{
		static int sot[100001],next[100000],nsz,vals[100000];
		nsz=0;
		for(int i=1;i<=M;i++)sot[i]=-1;
		for(int i=0;i<tick;i++)
		{
			vals[nsz]=i;
			next[nsz]=sot[T[i]];
			sot[T[i]]=nsz;
			nsz++;
		}
		for(int i=1,j=0;i<=M;i++)
		{
			for(int cur=sot[i];cur!=-1;cur=next[cur])order[j++]=vals[cur];
		}
	}
	for(int i=1;i<tick;i++)
	{
		if(T[order[i]]==T[order[i-1]]&&I[order[i]]!=I[order[i-1]])return false;
	}
	static int mn[100001],mx[100001];
	for(int i=1;i<=N;i++)mn[i]=INF,mx[i]=-INF;
	for(int i=0;i<tick;i++)getmin(mn[J[i]],T[i]),getmax(mx[J[i]],T[i]);
	static int enter[100002],leave[100002];
	for(int i=1;i<=M+1;i++)enter[i]=leave[i]=0;
	for(int i=1;i<=N;i++)if(mn[i]!=INF)enter[mn[i]]++,leave[mx[i]+1]++;
	int certain=0,canleave=0,uncertain=0,leaved=0;
	for(int i=0,j=1;i<tick;i++)
	{
		const int cf=T[order[i]],cs=I[order[i]]+1;
		for(;j<=cf;j++)
		{
			const int v=min(enter[j],uncertain);
			uncertain-=v,certain+=v,enter[j]-=v;
			certain+=enter[j];
			certain-=leave[j],canleave+=leave[j];
		}
		if(certain+canleave+uncertain<cs)uncertain+=cs-(certain+canleave+uncertain);
		if(certain+canleave+uncertain>cs)
		{
			int dis=certain+canleave+uncertain-cs;
			if(canleave)
			{
				const int v=min(dis,canleave);
				canleave-=v,leaved+=v;
				dis-=v;
			}
			if(dis)
			{
				if(uncertain<dis)return false;
				uncertain-=dis,leaved+=dis;
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
