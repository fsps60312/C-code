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
inline bool IsUpper(const char c){return 'A'<=c&&c<='Z';}
inline bool IsNumber(const char c){return '0'<=c&&c<='9';}
inline int GetInt()
{
	char c=GetChar();
	while(!IsNumber(c))
	{
		if(c==EOF)return -1;
		c=GetChar();
	}
	int v=0;
	while(IsNumber(c))v=v*10+(c-'0'),c=GetChar();
	return v;
}
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	while((N=GetInt())!=-1)
	{
		while(N--)
		{
			static int kase=0;
			printf("Case %d: ",++kase);
			char a=GetChar();
			while(!IsUpper(a))a=GetChar();
			while(IsUpper(a))
			{
				char b=GetChar();
				if(IsNumber(b))
				{
					int v=0;
					while(IsNumber(b))v=v*10+(b-'0'),b=GetChar();
					while(v--)putchar(a);
					a=b;
				}
				else
				{
					putchar(a);
					a=b;
				}
			}
			puts("");
		}
	}
	return 0;
}
