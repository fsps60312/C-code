#include<cstdio>
int T,S,Q;
int main()
{
//	freopen("out.txt","w",stdout);
	while(scanf("%d%d%d",&T,&S,&Q)==3)
	{
		int ans=1,now=0;
		while(S<T)
		{
			S+=Q-1;
			now+=Q;
			if(now>S)ans++,now-=S;
//			printf("now=%d,S=%d\n",now,S);
		}
		printf("%d\n",ans);
		break;
	}
	return 0;
}
