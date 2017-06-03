#include<cstdio>
#include<cassert>
#include<cstdlib>
#include<string>
using namespace std;
string InputFileName(const int id)
{
	static char ans[1000];
	sprintf(ans,"test data/%02d",id);
	return ans;
}
string AnswerFileName(const int id)
{
	static char ans[1000];
	sprintf(ans,"test data/%02d.a",id);
	return ans;
}
#include<ctime>
int main()
{
	for(int id=1;id<=67;id++)
	{
		clock_t time=clock(); 
		system(("2014B.exe<\""+InputFileName(id)+"\" > out.txt").c_str());
		printf("Case #%02d run time = %.3f s\n",id,(double)(clock()-time)/CLOCKS_PER_SEC);
		system(("check.exe \""+InputFileName(id)+"\" \"out.txt\" \""+AnswerFileName(id)+"\"").c_str());
	}
	return 0;
}
