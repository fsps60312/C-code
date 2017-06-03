#include<cstdio>
#include<cstdlib>
struct cubetype
{
	int s[12];
};
cubetype rotate(cubetype a)
{
	cubetype b;
	for(int i=1;i<=4;i++)
	{
		b.s[i-1]=a.s[i%4];
		b.s[i-1+4]=a.s[i%4+4];
		b.s[i-1+8]=a.s[i%4+8];
	}
	return b;
}
cubetype flip(cubetype a)
{
	cubetype b;
	int c[12]={2,5,10,6,1,9,11,3,0,4,8,7};
	for(int i=0;i<12;i++) b.s[i]=a.s[c[i]];
	return b;
}
void showgroups(cubetype a)
{
	bool vis[12];
	for(int i=0;i<12;i++) vis[i]=false;
	for(int i=0;i<12;i++)
	{
		if(!vis[i])
		{
			int j=i;
			while(!vis[j])
			{
				vis[j]=true;
				printf(" %d",j);
				j=a.s[j];
			}
			printf("\n");
		}
	}
}
int main()
{
	cubetype origin;
	for(int i=0;i<12;i++) origin.s[i]=i;
	printf("no\n");
	showgroups(origin);
	printf("r\n");
	showgroups(rotate(origin));
	printf("rr\n");
	showgroups(rotate(rotate(origin)));
	printf("rrr\n");
	showgroups(rotate(rotate(rotate(origin))));
	printf("f\n");
	showgroups(flip(origin));
	printf("fr\n");
	showgroups(rotate(flip(origin)));
	printf("frr\n");
	showgroups(rotate(rotate(flip(origin))));
	printf("frrr\n");
	showgroups(rotate(rotate(rotate(flip(origin)))));
	printf("ff\n");
	showgroups(flip(flip(origin)));
	printf("ffr\n");
	showgroups(rotate(flip(flip(origin))));
	printf("ffrr\n");
	showgroups(rotate(rotate(flip(flip(origin)))));
	printf("ffrrr\n");
	showgroups(rotate(rotate(rotate(flip(flip(origin))))));
	printf("fff\n");
	showgroups(flip(flip(flip(origin))));
	printf("fffr\n");
	showgroups(rotate(flip(flip(flip(origin)))));
	printf("fffrr\n");
	showgroups(rotate(rotate(flip(flip(flip(origin))))));
	printf("fffrrr\n");
	showgroups(rotate(rotate(rotate(flip(flip(flip(origin)))))));
	printf("rf\n");
	showgroups(flip(rotate(origin)));
	printf("rfr\n");
	showgroups(rotate(flip(rotate(origin))));
	printf("rfrr\n");
	showgroups(rotate(rotate(flip(rotate(origin)))));
	printf("rfrrr\n");
	showgroups(rotate(rotate(rotate(flip(rotate(origin))))));
	printf("rrrf\n");
	showgroups(flip(rotate(rotate(rotate(origin)))));
	printf("rrrfr\n");
	showgroups(rotate(flip(rotate(rotate(rotate(origin))))));
	printf("rrrfrr\n");
	showgroups(rotate(rotate(flip(rotate(rotate(rotate(origin)))))));
	printf("rrrfrrr\n");
	showgroups(rotate(rotate(rotate(flip(rotate(rotate(rotate(origin))))))));
	return 0;
}
