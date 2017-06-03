#include<cstdio>
#include<cassert>
//#include<algorithm>
using namespace std;
const int INF=2147483647;
template<class T>inline bool getmin(T&a,const T&b){return b<a?(a=b,true):false;}
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
bool Find(const char *str,const char *a)
{
	for(int i=0;str[i];i++)
	{
		for(int j=0;;j++)
		{
			if(!a[j]||a[j]=='\n')return true;
			if(str[i+j]!=a[j])break;
		}
	}
	return false;
}
bool Check(const char *str,const char *a,const char *b)
{
	return Find(str,a)&&Find(str,b);
}
int N,M;
char S[20000][1002];
int main()
{
//	freopen("in.txt","r",stdin);
	static char input[1000000];
	while(fgets(input,INF,stdin))
	{
		assert(sscanf(input,"%d%d",&N,&M)==2);
		for(int i=0;i<N;i++)fgets(S[i],INF,stdin);
		while(M--)
		{
			static char str1[1002],str2[1002];
			fgets(str1,INF,stdin);
			fgets(str2,INF,stdin);
//			printf("%s %s\n",str1,str2);
			int ans=0;
			for(int i=0;i<N;i++)if(Check(S[i],str1,str2))++ans;
			printf("%d\n",ans);
		}
	}
	return 0;
}
