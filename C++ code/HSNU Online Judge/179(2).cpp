#include<cstdio>
#include<vector>
#include<map>
#include<cassert>
using namespace std;
const int INF=2147483647;
void getmax(int &a,const int b){if(b>a)a=b;}
int M,ANS[26][26];
int main()
{
//	freopen("in.txt","r",stdin);
	static int testcase;scanf("%d",&testcase);
	while(testcase--)
	{
		scanf("%d",&M);
		for(int i=0;i<26;i++)for(int j=0;j<26;j++)ANS[i][j]=-INF;
		for(int i=0;i<26;i++)ANS[i][i]=0;
		for(int i=0;i<M;i++)
		{
			static char name[11];scanf("%s",name);
			int len=-1;while(name[++len]);
			const int a=name[0]-'a',b=name[len-1]-'a';
			static int tmp[26];
			for(int j=0;j<26;j++)
			{
				if(ANS[j][a]==-INF)tmp[j]=-INF;
				else tmp[j]=ANS[j][a]+len;
			}
			for(int j=0;j<26;j++)getmax(ANS[j][b],tmp[j]);
		}
		int ans=-INF;
		for(int i=0;i<26;i++)getmax(ans,ANS[i][i]);
		printf("%d\n",ans==-INF?0:ans);
	}
	return 0;
}
