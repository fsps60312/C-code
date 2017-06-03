#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
using namespace std;
char S1[100001],S2[31];
int N1,N2;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%s%s",S1,S2)==2)
	{
		N1=-1;while(S1[++N1]);
		N2=-1;while(S2[++N2]);
		int now=-1,ans=0;
		for(int i=0;i<N1;i++)
		{
			bool matched=true;
			for(int j=0;j<N2;j++)if(S1[i+j]!=S2[j]){matched=false;break;}
			if(matched)
			{
				if(i>now)now=i+N2-1,ans++;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
