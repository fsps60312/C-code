#include<cstdio>
#include<cstdlib>
struct playertype
{
	int site;
	bool paused;
};
int dies[1001];
int shortcut[101];
int special[101];
int n;
playertype player[6];
int main()
{
	//freopen("in.txt","r",stdin);
	int dien=-1;
	while(scanf("%d",&dies[++dien])==1&&dies[dien]!=0);
	//printf("dien=%d\n",dien);
	int a,b;
	while(scanf("%d",&n)==1)
	{
		if(n==0) break;
		for(int i=0;i<101;i++)
		{
			shortcut[i]=-1;
			special[i]=0;
		}
		while(scanf("%d%d",&a,&b)==2&&!(a==0&&b==0)) shortcut[a]=b;
		while(scanf("%d",&a)==1&&a!=0)
		{
			if(a>0) special[a]=1;
			else special[-a]=-1;
		}
		for(int i=0;i<n;i++)
		{
			player[i].site=0;
			player[i].paused=false;
		}
		int order=0;
		int ans=-1;
		for(int i=0;i<dien;i++)
		{
			//printf("%d\t%d\n",player[0].site,player[1].site);system("pause");
			while(player[order%n].paused)
			{
				player[order%n].paused=false;
				order++;
			}
			player[order%n].site+=dies[i];
			int j=player[order%n].site;
			if(j==100)
			{
				ans=order%n+1;
				break;
			}
			else if(shortcut[j]!=-1) player[order%n].site=shortcut[j];
			else if(special[j]==1) continue;
			else if(special[j]==-1)
			{
				player[order%n].paused=true;
			}
			order++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
