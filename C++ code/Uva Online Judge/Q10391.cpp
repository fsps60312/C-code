#include<cstdio>
#include<cstdlib>
#include<string>
#include<set>
using namespace std;
char tmp[1000000];
set<string> S;
int main()
{
	//freopen("in.txt","r",stdin);
	while(scanf("%s",tmp)==1)
	{
		string i=tmp;
		S.insert(i);
	}
	for(set<string>::iterator i=S.begin();i!=S.end();i++)
	{
		string j=*i;
		for(int k=1;k<j.size();k++)
		{
			if(S.find(j.substr(0,k))!=S.end()&&S.find(j.substr(k))!=S.end())
			{
				printf("%s\n",j.c_str());
				break;
			}
		}
	}
	return 0;
}
