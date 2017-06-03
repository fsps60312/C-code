#include<cstdio>
#include<cstdlib>
int n,m,kase=1,s[8],rs[8];
char leaf[1<<7+1],in[8];
int main()
{
	//freopen("in.txt","r",stdin);
	while(scanf("%d",&n)==1&&n)
	{
		//if(kase>1)printf("\n");
		for(int i=0;i<n;i++)
		{
			char c;
			while(scanf("%c",&c)==1&&c!='x');
			scanf("%d",&s[i]);
		}
		for(int i=0;i<n;i++)rs[s[i]-1]=i;
		//for(int i=0;i<n;i++)printf(" %d",rs[i]);printf("\n");
		scanf("%s",leaf);//printf("leaf=%s\n",leaf);
		scanf("%d",&m);//printf("a%d\n",m);
		printf("S-Tree #%d:\n",kase++);
		for(int i=0;i<m;i++)
		{
			scanf("%s",in);//printf("in=%s\n",in);
			int tmp[n];
			//printf("leaf=%s\n",leaf);
			for(int j=0;j<n;j++)tmp[rs[j]]=in[j]-'0';
			//for(int j=0;j<n;j++)printf("%d",tmp[j]);printf("\n");
			int a=0;
			for(int j=0;j<n;j++)if(tmp[n-1-j]==1)a+=(1<<j);
			//printf("a=%d\n",a);
			printf("%c",leaf[a]);
		}//printf("b\n");
		printf("\n\n");
	}
	return 0;
}
