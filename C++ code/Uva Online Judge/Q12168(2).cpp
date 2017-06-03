#include<cstdio>
#include<vector>
using namespace std;
int T,V,ADM[500][500];
struct Voter
{
	int a,b;
	Voter(){}
	Voter(int a,int b):a(a),b(b){}
};
vector<Voter>C,D;
int main()
{
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			static int c,d;
			scanf("%d%d%d",&c,&d,&V);
			C.clear(),D.clear();
			for(int i=0;i<V;i++)
			{
				static char s1[5],s2[5];
				scanf("%s%s",s1,s2);
				static int a,b;
				sscanf(s1+1,"%d",&a);
				sscanf(s2+1,"%d",&b);
				(s1[0]=='C'?C:D).push_back(Voter(a,b));
			}
			for(int i=0;i<C.size();i++)for(int j=0;j<D.size();j++)ADM[i][j]=0;
			for(int i=0;i<C.size();i++)
			{
				for(int j=0;j<D.size();j++)
				{
					if(C[i].a==D[j].b||C[i].b==D[j].a)
				}
			}
		}
	}
	return 0;
}
