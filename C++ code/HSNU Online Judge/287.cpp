#include<cstdio>
#include<vector>
using namespace std;
int N;
vector<int>S[2];
vector<vector<int> >ANS;
int main()
{
	while(scanf("%d",&N)==1)
	{
		S[0].clear(),S[0].push_back(0),S[0].push_back(N);
		ANS.clear();
		int d=0;
		for(;(int)S[d].size()<N+1;d^=1)
		{
			S[d^1].clear();
			vector<int>ans;
			for(int i=0;;i++)
			{
				S[d^1].push_back(S[d][i]);
				if(i+1==(int)S[d].size())break;
				if(S[d][i]+1<S[d][i+1])
				{
					const int mid=(S[d][i]+S[d][i+1])/2;
					for(int j=S[d][i];j<mid;j++)ans.push_back(j);
					S[d^1].push_back(mid);
				}
			}
			ANS.push_back(ans);
		}
		printf("%d\n",(int)ANS.size());
		for(const auto &ans:ANS)
		{
			printf("%d",(int)ans.size());
			for(const int v:ans)printf(" %d",v+1);
			puts("");
		}
		break;
	}
	return 0;
}
