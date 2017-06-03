#include<cstdio>
#include<cstdlib>
int T,tmp[3],ans;
char S[1001];
int main()
{
	scanf("%d",&T);
	for(int kase=1;kase<=T;kase++)
	{
		printf("Case %d: ",kase);
		scanf("%s",S);
		tmp[0]=tmp[1]=tmp[2]=0;
		for(int i=0;S[i];i++)
		{
			tmp[(S[i]-'0')%3]++;
		}
		//(tmp[1]+tmp[2]*2)%3
		ans=(tmp[1]+tmp[2]*2)%3;
		if(!tmp[ans]) printf("T\n");
		else
		{
			tmp[ans]--;
			if(tmp[0]%2==0) printf("S\n");
			else printf("T\n");
		}
	}
	return 0;
}
