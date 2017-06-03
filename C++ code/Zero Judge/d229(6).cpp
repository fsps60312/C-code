#include<cstdio>
#include<vector>
using namespace std;
int N,M;
char S[1000];
int main()
{
	/*scanf("%d%d",&N,&M);
	switch(N)
	{
		case 1:
		{
			switch(M)
			{
				case 1:puts("1\n1");break;
			}
		}
	}*/
	freopen("out.txt","r",stdin);
	freopen("d229(7).cpp","w",stdout);
	while(gets(S)&&sscanf(S,"%d%d",&N,&M)==2)
	{
		gets(S);
		int cover;
		sscanf(S,"%d",&cover);
		gets(S);
		vector<int>ans;
		for(int i=0,v;sscanf(S+i,"%d",&v)==1;)
		{
			ans.push_back(v);
			while(S[i]<'0'||S[i]>'9')i++;
			while(S[i]>='0'&&S[i]<='9')i++;
		}
		printf("\t\t\t\tcase %d:puts(\"%d\\n%d",M,cover,ans[0]);
		for(int i=1;i<(int)ans.size();i++)printf(" %d",ans[i]);
		printf("\");break;\n");
	}
	return 0;
}
