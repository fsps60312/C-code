#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int N,S[23],SG[23],J,K;
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
		for(;ans<N;ans++)
		{
			if(getSG(ans))
			{
				bool found=false;
				for(J=ans+1;J<N&&!found;J++)
				{
					for(K=J;K<N;K++)
					{
						if(!(getSG(J)^getSG(K)))
						{
							found=true;
							break;
						}
					}
				}
				if(!found)printf("error\n");
				break;
			}
		}
		printf("Game %d:",kase++);
		if(ans==N)printf(" -1 -1 -1\n");
		else printf(" %d %d %d\n",ans,J,K);
	}
	return 0;
}
