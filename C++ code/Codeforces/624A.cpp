#include<cstdio>
int main()
{
	for(int d,l,v1,v2;scanf("%d%d%d%d",&d,&l,&v1,&v2)==4;)
	{
		printf("%.9f\n",(l-d)/(double)(v1+v2));
	}
	return 0;
}
