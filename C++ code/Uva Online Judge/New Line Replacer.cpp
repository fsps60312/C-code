#include<cstdio>
#include<vector>
using namespace std;
int main()
{
	freopen("new.txt","r",stdin);
	vector<char>tmp;
	char c;while(scanf("%c",&c)==1)tmp.push_back(c=='\r'?'\n':c);
	freopen("new.txt","w",stdout);
	for(int i=0;i<(int)tmp.size();i++)putchar(tmp[i]);
}
