#include<cstdio>
#include<cassert>
#include<string>
using namespace std;
int N;
char S[100001];
bool IsNumber(const char c){return '0'<=c&&c<='9';}
bool IsNumber(const int l,const int r)
{
	if(l==r)return false;
	if(l+1==r)return IsNumber(S[l]);
	if(!IsNumber(S[l])||S[l]=='0')return false;
	for(int i=l+1;i<r;i++)if(!IsNumber(S[i]))return false;
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%s",S)==1)
	{
		N=-1;while(S[++N]);
		S[N]=',';
		for(int i=0;i<N;i++)if(S[i]==';')S[i]=',';
		string a,b;
		for(int i=0;i<=N;)
		{
			int j=i;
			while(S[j]!=',')++j;
			S[j]='\0';
			(IsNumber(i,j)?a:b)+=","+(string)(S+i);
			i=j+1;
		}
		if(a.empty())puts("-");
		else puts(("\""+(string)(a.c_str()+1)+"\"").c_str());
		if(b.empty())puts("-");
		else puts(("\""+(string)(b.c_str()+1)+"\"").c_str());
	}
	return 0;
}
