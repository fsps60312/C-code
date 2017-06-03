#include<cstdio>
//#include<cassert>
#include<string>
#include<vector>
using namespace std;
const int INF=2147483647;
void assert(const bool valid){if(valid)return;for(;;)putchar('E');}
int N;
vector<string>WORDS;
bool IsLower(const char c){return 'a'<=c&&c<='z';}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0,v;i<N;i++)
		{
			static char word[300001];
			assert(scanf("%s%d",word,&v)==2);
			for(int j=0;word[j];j++)assert(IsLower(word[j]));
		}
	}
	int a=0,b=0;a/=b;
	return 0;
}
