#include<cstdio>
#include<cassert>
using namespace std;
int CH[26][2];
void ClearCH()
{
	for(int i=0;i<26;i++)CH[i][0]=CH[i][1]=-1;
}
void GetS(char *str,int &n)
{
	assert(scanf("%s",str)==1);
	n=-1;while(str[++n]);
}
int main()
{
	static char tmp[2][1000000];
	static int n[2];
	ClearCH();
	GetS(tmp[0],n[0]);
	for(int d=1;;d^=1)
	{
		GetS(tmp[d],n[d]);
		if(tmp[d][0]=='*'||tmp[d][0]=='$')
		{
			tmp[d][1]
			if(tmp[d][0]=='$')break;
			ClearCH();
			d^=1;
			GetS(tmp[d],n[d]);
		}
	}
	return 0;
}
