#include<cstdio>
#include<cassert>
using namespace std;
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
int N,S[2000000],CNT[30000];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount=GetInt();
	while(testcount--)
	{
		N=GetInt();
		for(int i=0;i<30000;i++)CNT[i]=0;
		for(int i=0;i<N;i++)++CNT[GetInt()];
		for(int i=0,val=0;i<N;i++)
		{
			while(CNT[val]==0)++val;
			S[i]=val,--CNT[val];
		}
		long long ans=0;
		const int half=(N-1)/2;
		for(int i=0;i<half;i++)ans+=S[half]-S[i];
		for(int i=half+1;i<N;i++)ans+=S[i]-S[half];
		printf("%lld %d\n",ans,S[half]);
	}
	return 0;
}
