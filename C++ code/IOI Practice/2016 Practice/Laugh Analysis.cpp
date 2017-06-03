#include"laugh.h"
#include<string>
#include<vector>
#include<algorithm>
using namespace std; 
template<class T>inline void getmax(T&a,const T&b){if(a<b)a=b;}
int	longest_laugh(string s)
{
	s.push_back('\0');
	rotate(s.begin(),s.end(),s.end()-1);
	vector<int>dp;
	dp.resize(s.size());
	dp[0]=0;
	int ans=0;
	for(int i=1;i<(int)s.size();i++)
	{
		if(s[i]=='a'||s[i]=='h')
		{
			if((s[i-1]=='a'&&s[i]=='h')||(s[i-1]=='h'&&s[i]=='a'))getmax(ans,dp[i]=dp[i-1]+1);
			else getmax(ans,dp[i]=1);
		}
		else dp[i]=0;
	}
	return ans;
}
//int main()
//{
//	printf("%d\n",longest_laugh("ahahrunawayahahsofasthah"));
//	return 0;
//}
