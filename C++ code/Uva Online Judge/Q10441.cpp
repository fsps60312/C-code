#include<cstdio>
#include<vector>
#include<map>
#include<string>
using namespace std;
int T,N;
char LINE[21];
bool TO[26][26],ODD[26];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=0;i<26;i++)
		{
			for(int j=0;j<26;j++)TO[i][j]=false;
			CNT[i]=0;
		}
		int cnt=0;
		for(int i=0;i<N;i++)
		{
			scanf("%s",LINE);
			int &c1=FRONT[i]=LINE[0]-'a',c2=BACK[i]=-1;
			while(LINE[++c2]);c2=LINE[--c2]-'a';
			TO[c1][c2]^=true;
			ODD[c1]^=true;
			if(ODD[c1])cnt++;
			else cnt--;
			ODD[c2]^=true;
			if(ODD[c2])cnt++;
			else cnt--;
		}
		if(cnt==0)
	}
	return 0;
}
