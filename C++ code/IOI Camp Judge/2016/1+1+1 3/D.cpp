#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
struct StringMatcher
{
	vector<char>str;
	vector<int>fail;
	void BuildFail(const char *_str)
	{
		str.clear();
		for(int i=0;_str[i];i++)str.push_back(_str[i]);
		fail.clear();
		fail.push_back(0),fail.push_back(0);
		for(int i=1;i<(int)str.size();i++)
		{
			int f=fail[i];
			while(f&&str[f]!=str[i])f=fail[f];
			if(str[f]==str[i])f++;
			fail.push_back(f);
		}
	}
	
};
int N;
char S[100001];
bool Valid(const int len)
{
	
}
int main()
{
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%s",&N,S);
	}
	return 0;
}
