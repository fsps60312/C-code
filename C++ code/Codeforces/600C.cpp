#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
char S[200001];
int CNT[26];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%s",S)==1)
	{
		for(int i=0;i<26;i++)CNT[i]=0;
		for(int i=0;S[i];i++)++CNT[S[i]-'a'];
		vector<int>v;
		for(int i=0;i<26;i++)if(CNT[i]&1)v.push_back(i);
		for(int l=0,r=(int)v.size()-1;l<r;++l,--r)++CNT[v[l]],--CNT[v[r]];
		char mid='\0';
		for(int i=0;i<26;i++)
		{
			for(int j=0;j<CNT[i]/2;j++)putchar((char)('a'+i));
			if(CNT[i]&1)mid=(char)('a'+i);
		}
		if(mid!='\0')putchar(mid);
		for(int i=25;i>=0;i--)
		{
			for(int j=0;j<CNT[i]/2;j++)putchar((char)('a'+i));
		}
		puts("");
	}
	return 0;
}
