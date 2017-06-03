#include<cstdio>
#include<cassert>
#include<vector>
#include<set>
using namespace std;
typedef long long LL;
LL Solve()
{
	vector<LL>ans;
	set<LL>s;
	s.insert(1LL);
	while((int)ans.size()<1500)
	{
		const LL u=*s.begin();s.erase(s.begin());
		s.insert(u*2LL),s.insert(u*3LL),s.insert(u*5LL);
		ans.push_back(u);
	}
	return ans[1500-1];
}
int main()
{
	printf("The 1500'th ugly number is %lld.\n",Solve());
	return 0;
}
