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
	static char input_buffer[300100];
	int testcount;fgets(input_buffer,INF,stdin);assert(sscanf(input_buffer,"%d",&testcount)==1);
	while(testcount--)
	{
		fgets(input_buffer,INF,stdin);assert(sscanf(input_buffer,"%d",&N)==1);
		for(int i=0,v;i<N;i++)
		{
			static char word[300001];
			fgets(input_buffer,INF,stdin);
			if(sscanf(input_buffer,"%s%d",word,&v)!=2)assert(sscanf(input_buffer,"%d",&v)==1);
			for(int j=0;word[j];j++)assert(IsLower(word[j]));
		}
	}
	assert(scanf("%d",&testcount)==-1);
	int a=0,b=0;a/=b;
	return 0;
}
