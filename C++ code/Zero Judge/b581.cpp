#include<bits/stdc++.h>
using namespace std;
char LINE[1000000];
int T,I;
bool Digit(char a){return a>='0'&&a<='9';}
bool Read(int &ans)
{
	while(LINE[I]&&!Digit(LINE[I]))I++;
	if(!LINE[I])return false;
	ans=0;
	int l=I-1;
	while(Digit(LINE[I]))
	{
		ans=ans*10+LINE[I]-'0';
		I++;
	}
	if(l>=0&&LINE[l]=='-')ans*=-1;
	return true;
}
int main()
{
	gets(LINE);
	sscanf(LINE,"%d",&T);
	while(T--)
	{
		gets(LINE);
		I=0;
		int tmp,ans=0;
		while(Read(tmp))ans+=tmp;
		printf("%d\n",ans);
	}
}
