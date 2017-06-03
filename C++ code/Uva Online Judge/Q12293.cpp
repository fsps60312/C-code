#include<cstdio>
#include<cstdlib>
//(0,1):1(lose)
//(1,1):0(win)
//(2,1)=pick((1,1))=1
//(3,1)=pick((2,1))=0
//(4,1)=pick((2,1)(3,1))=2
//(5,1)=pick((3,1)(4,1))=1
//(6,1)=pick((3,1)(4,1)(5,1))=3
//(7,1)=pick((4,1)(5,1)(6,1))=0
int win[1000000],n,a;
bool iswin(int a)
{
	int Min=0,Max=n,mid;
	while(Min<Max)
	{
		mid=(Min+Max)/2;
		if(win[mid]<a) Min=mid+1;
		else Max=mid;
	}
	return win[Max]==a;
}
int main()
{
	win[0]=1;
	for(n=0;win[n]<1000000000;n++)
	{
		win[n+1]=win[n]*2+1;
	}
	n--;
	while(scanf("%d",&a)==1&&a)
	{
		if(iswin(a)) printf("Bob\n");
		else printf("Alice\n");
	}
	return 0;
}
