#include<cstdio>
#include<cassert>
using namespace std;
const int INF=2147483647;
char A[1002],B[1002];
int CNT[26],ANS[26];
int main()
{
	for(;;)
	{
		if(!fgets(A,INF,stdin))break;
		assert(fgets(B,INF,stdin));
		for(int i=0;i<26;i++)CNT[i]=ANS[i]=0;
		for(int i=0;A[i]&&A[i]!='\n';i++)assert(A[i]>='a'&&A[i]<='z'),CNT[A[i]-'a']++;
		for(int i=0;B[i]&&B[i]!='\n';i++)
		{
			assert(B[i]>='a'&&B[i]<='z');
			const int c=B[i]-'a';
			if(CNT[c])CNT[c]--,ANS[c]++;
		}
		for(int i=0;i<26;i++)for(int j=0;j<ANS[i];j++)putchar('a'+i);
		puts("");
	}
	return 0;
}
