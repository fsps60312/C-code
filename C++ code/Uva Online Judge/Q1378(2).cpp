#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int N,S[23],SG[23],I,J,K;
int getSG(int u)
{
	int &sg=SG[u];
	if(sg!=-1)return sg;
	if(u==N-1)return sg=0;
	vector<int> v;
	for(int j=u+1;j<N;j++)
	{
		for(int k=j;k<N;k++)
		{
			v.push_back(getSG(j)^getSG(k));
		}
	}
	sort(v.begin(),v.end());
	sg=0;
	for(int i=0;i<v.size();i++)
	{
		if(v[i]==sg)sg++;
		else if(v[i]>sg)break;
	}
	return sg;
}
int main()
{
	int kase=1;
	while(scanf("%d",&N)==1&&N)
	{
		for(int i=0;i<N;i++)
		{
			SG[i]=-1;
			scanf("%d",S+i);
		}
		int ans=0;
		for(int i=0;i<N;i++)if(S[i]&1)ans^=getSG(i);
		printf("Game %d:",kase++);
		if(!ans)printf(" -1 -1 -1\n");
		else
		{
			bool found=false;
			for(I=0;I<N&&!found;I++)
			{
				for(J=I+1;J<N&&!found;J++)
				{
					for(K=J;K<N;K++)
					{
						if((getSG(I)^getSG(J)^getSG(K))==ans)
						{
							printf(" %d %d %d\n",I,J,K);
							found=true;
							break;
						}
					}
				}
			}
			if(!found)printf("error\n");
		}
	}
	return 0;
}
