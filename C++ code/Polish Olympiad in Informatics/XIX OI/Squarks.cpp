#include<cstdio>
#include<cassert>
#include<set>
#include<vector>
using namespace std;
int N;
multiset<int>S;
int GRID[299][300];
vector<vector<int> >ANS;
/*
\|0123456
-+-------
0|\OO    
1| \?    
2|  \    
3|   \   
4|    \  
5|     \ 
6|      \
*/
void Dfs(const int col)
{
	if(col==N)
	{
		vector<int>ans;
		const int m0=GRID[0][0]/2;
		ans.push_back(m0);
		for(int i=1;i<N;i++)ans.push_back(GRID[0][i]-m0);
		ANS.push_back(ans);
		return;
	}
	if(*S.begin()<=GRID[0][col-1])return;
	GRID[0][col]=*S.begin();
	for(int row=1;row<=col-2;row++)GRID[row][col]=GRID[row][col-1]+(GRID[0][col]-GRID[0][col-1]);
	GRID[col-1][col]=GRID[col-2][col]+(GRID[0][col-1]-GRID[0][col-2]);
	for(int row=0;row<=col-1;row++)if(S.find(GRID[row][col])==S.end())return;
	for(int row=0;row<=col-1;row++)S.erase(S.find(GRID[row][col]));
	Dfs(col+1);
	for(int row=0;row<=col-1;row++)S.insert(GRID[row][col]);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		S.clear();
		for(int i=0,v;i<N*(N-1)/2;i++)scanf("%d",&v),S.insert(v);
		GRID[0][1]=*S.begin(),S.erase(S.begin());
		GRID[0][2]=*S.begin(),S.erase(S.begin());
		vector<int>vals;
		for(set<int>::iterator it=S.begin();it!=S.end();it=S.upper_bound(*it))vals.push_back(*it);
		ANS.clear();
		for(int i=0;i<(int)vals.size();i++)
		{
			S.erase(S.find(GRID[1][2]=vals[i]));
			GRID[0][0]=GRID[0][1]+GRID[0][2]-GRID[1][2];
			if(GRID[0][0]<=0)break;
			if(GRID[0][0]%2==0)Dfs(3);
			S.insert(GRID[1][2]);
		}
		printf("%d\n",(int)ANS.size());
		for(int i=0;i<(int)ANS.size();i++)
		{
			for(int j=0;j<(int)ANS[i].size();j++)
			{
				if(j)putchar(' ');
				printf("%d",ANS[i][j]);
			}
			puts("");
		}
	}
	return 0;
}
