#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
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
void ReadInt(int &v)
{
	char c=ReadChar();
	while(c<'0'||'9'<c)c=ReadChar();
	v=0;
	while('0'<=c&&c<='9')v=v*10+(c-'0'),c=ReadChar();
}
int N,M;
bool EDGE[3000][3000],DEL[3000];
int main()
{
//	freopen("in.txt","r",stdin);
	ReadInt(N),ReadInt(M);
	assert(N%3==0);
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)EDGE[i][j]=false;
	for(int i=0,a,b;i<M;i++)
	{
		ReadInt(a),ReadInt(b),--a,--b;
		EDGE[a][b]=EDGE[b][a]=true;
	}
	for(int i=0;i<N;i++)DEL[i]=false;
	for(int i=0;i<N;i++)if(!DEL[i])
	{
		for(int j=i+1;j<N;j++)if(!EDGE[i][j]&&!DEL[j])
		{
			DEL[i]=DEL[j]=true;
			break;
		}
	}
	vector<int>ans;
	for(int i=0;i<N&&(int)ans.size()<N/3;i++)if(!DEL[i])ans.push_back(i);
	for(int i=0;i<(int)ans.size();i++)
	{
		if(i)putchar(' ');
		printf("%d",ans[i]+1);
	}
	puts("");
	assert((int)ans.size()==N/3);
	return 0;
}
