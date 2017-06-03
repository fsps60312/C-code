#include<cstdio>
#include<algorithm>
using namespace std;
int N,M;
char S[200001],T[26],P[26];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&M);
	scanf("%s",S);
	for(int i=0;i<26;i++)T[i]=i,P[i]=i;//transfer a to b,a is at b
	for(int i=0;i<M;i++)
	{
		static char astr[2],bstr[2];
		scanf("%s%s",astr,bstr);
//		printf("%s %s\n",astr,bstr);
		int a=astr[0]-'a',b=bstr[0]-'a';
//		int a_loc=P[b],b_loc=P[a];
//		int a_to=T[P[a]],b_to=T[P[b]];
		swap(T[P[a]],T[P[b]]);
		swap(P[a],P[b]);
//		for(int i=0;i<26;i++)printf(" %d",P[i]);puts("");
//		for(int i=0;i<N;i++)putchar('a'+T[S[i]-'a']);puts("");
	}
	for(int i=0;i<N;i++)putchar('a'+T[S[i]-'a']);puts("");
	return 0;
}
