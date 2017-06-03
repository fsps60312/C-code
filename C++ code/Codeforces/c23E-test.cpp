#include<cstdio>
#include<vector>
//#include<ctime>
using namespace std;
int main()
{
	vector<int>*s=new vector<int>();
	puts("pass");
	for(int i=0;i<10000000;i++)s->push_back(i);
	for(int i=0,j=0;i<10000000;i++)
	{
		j+=(*s)[i];
		if(i%100000==0)printf("j=%d\n",j);
	}
	puts("pass");
}
