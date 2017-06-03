#include<cstdio>
#include<map>
using namespace std;
int N,BONE[24];
char STR[1000000];
void getmax(int &a,int b){if(b>a)a=b;}
map<int,int> MAX;
int main()
{
	while(scanf("%d",&N)==1)
	{
		MAX.clear();
		for(int i=0;i<N;i++)
		{
			scanf("%s",STR);
			BONE[i]=0;
			for(int j=0;STR[j];j++)
			{
				BONE[i]^=1<<(STR[j]-'A');
			}
		}
		int ans=0;
		int hn=N/2;
		for(int i=0,v=0,cnt=0;i<(1<<hn);i++,v=0,cnt=0)
		{
			for(int j=0;j<hn;j++)if(i&(1<<j))v^=BONE[j],cnt++;
			if(MAX.find(v)==MAX.end())MAX[v]=cnt;
			else getmax(MAX[v],cnt);
		}
		int r=N-hn;
		for(int i=0,v=0,cnt=0;i<(1<<r);i++,v=0,cnt=0)
		{
			for(int j=hn;j<N;j++)if(i&(1<<j-hn))v^=BONE[j],cnt++;
			if(MAX.find(v)!=MAX.end())getmax(ans,MAX[v]+cnt);
		}
		printf("%d\n",ans);
	}
	return 0;
}
