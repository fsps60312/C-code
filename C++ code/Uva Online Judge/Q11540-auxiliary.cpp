#include<cstdio>
#include<vector>
using namespace std;
vector<int> p;
const int MOD=1000000007;
int main()
{
	freopen("out.txt","w",stdout);
	p.push_back(2),p.push_back(3);
	for(int i=2,j;i<1000000;i++)
	{
		p.push_back(p[i-1]);
		do
		{
			p[i]+=2;
			for(j=0;p[j]*p[j]<=p[i]&&p[i]%p[j];j++);
		}while(p[i]%p[j]==0);
		printf("%-6d:%d\n",i,p[i]);
	}
	for(int i=0;p[i]*p[i]<=MOD;i++)
	{
		if(MOD%p[i]==0)printf("%d divisible by %d\n",MOD,p[i]);
	}
	printf("finished\n");
	return 0;
}
