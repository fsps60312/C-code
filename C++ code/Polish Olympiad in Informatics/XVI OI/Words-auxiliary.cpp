#include<cstdio>
#include<cassert>
#include<string>
#include<vector>
using namespace std;
int main()
{
	freopen("out.txt","w",stdout);
	string s[2];
	s[0]="0";
	for(int i=0,d=0;i<18;i++,d^=1)
	{
		printf("f[%2d]=%s\n",i,s[d].c_str());
//		vector<int>v;
//		for(int j=1;j<(int)s[d].size();j++)if(s[d][j-1]=='1'&&s[d][j]=='1')v.push_back(j);
//		printf("v.size()=%d\n",(int)v.size());
//		if(true)
//		{
//			for(int j=(int)v.size()-1;j>=1;j--)printf("%d",v[j]-v[j-1]==5?1:0);puts("");
//		}
		s[d^1]="";
		for(int j=0;j<(int)s[d].size();j++)
		{
			if(s[d][j]=='0')s[d^1]+="1";
			else s[d^1]+="10";
		}
	}
	return 0;
}
