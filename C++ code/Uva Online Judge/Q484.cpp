#include<cstdio>
#include<cstdlib>
#include<map>
#include<vector>
using namespace std; 
int n;
map<int,int> ans;
vector<int> order;
int main()
{
	//freopen("in.txt","r",stdin);
	ans.clear();
	order.clear();
	while(scanf("%d",&n)==1)
	{
		if(ans.find(n)==ans.end())
		{
			ans[n]=1;
			order.push_back(n);
		}
		else ans[n]++;
	}
	for(int i=0;i<order.size();i++) printf("%d %d\n",order[i],ans[order[i]]);
	return 0;
}
