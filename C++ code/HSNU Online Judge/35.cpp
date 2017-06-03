#include<bits/stdc++.h>
using namespace std;
char S[6][6],NOW[6];
bool VIS[6];
int CNT[6];
bool Dfs(int dep)
{
	if(dep==6)
	{
		for(int i=0,cnt=0;i<6;i++,cnt=0)
		{
			for(int j=0;j<6;j++)if(NOW[j]==S[i][j])cnt++;
			if(cnt!=CNT[i])return false;
//			printf("i=%d,cnt=%d\n",i,cnt);
		}
		return true;
	}
	for(int i=0;i<6;i++)
	{
		if(VIS[i])continue;
		VIS[i]=true;
		NOW[dep]='1'+i;
		if(Dfs(dep+1))return true;
		VIS[i]=false;
	}
	return false;
}
int main()
{
	for(int i=0;i<6;i++)
	{
		VIS[i]=false;
		for(int j=0;j<6;j++)
		{
			char &v=S[i][j];
			do
			{
				scanf("%c",&v);
			}while(v<'1'||v>'6');
		}
		scanf("%d",&CNT[i]);
	}
	Dfs(0);
	for(int i=0;i<6;i++)printf("%c%c",NOW[i],i==5?'\n':' ');
	return 0;
}
