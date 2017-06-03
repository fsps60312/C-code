#include<cstdio>
#include<cstdlib>
#define LL long long
int now,T;
char S[1000000];
bool isnum(char a){return a>='0'&&a<='9';}
LL num()
{
	LL ans=0;
	while(!isnum(S[now])) now++;
	while(isnum(S[now]))
	{
		ans*=10;
		ans+=S[now]-'0';
		now++;
	}
	return ans;
}
LL add()
{
	LL ans=num();
	while(S[now]=='+') ans+=num();
	return ans;
}
LL mul()
{
	LL ans=num();
	while(S[now]=='*') ans*=num();
	return ans;
}
LL Max()
{
	now=0;
	LL ans=add();
	while(S[now]=='*') ans*=add();
	return ans;
}
LL Min()
{
	now=0;
	LL ans=mul();
	while(S[now]=='+') ans+=mul();
	return ans;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",S);
		printf("The maximum and minimum are %lld and %lld.\n",Max(),Min());
	}
	return 0;
}
