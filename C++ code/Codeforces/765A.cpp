#include<cstdio>
#include<cassert>
#include<map>
#include<string>
using namespace std;
string GetString()
{
	static char tmp[1000];
	scanf("%s",tmp);
	return tmp;
}
int N;
map<string,int>C;
string HOME;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		HOME=GetString();
		C.clear();
		for(int i=0;i<N;i++)
		{
			string s=GetString();
			++C[s.substr(0,3)];
			++C[s.substr(5,3)];
		}
		puts(C[HOME]%2==0?"home":"contest");
	}
	return 0;
}
