#include<bits/stdc++.h>
using namespace std;
int N,M,K;
struct Node
{
	vector<Node*>ch;
	int code,sz,ans;
}*ROOT[81];
void Build(Node* &o,const set<int>&s)
{
	
}
int main()
{
	while(scanf("%d%d%d",&N,&M,&K)==3)
	{
		int limit=1;
		for(int i=0;i<N;i++)limit*=M;
		set<int>s;
		for(int i=0;i<limit;i++)s.push_back(i);
		for(int rt=0;rt<limit;rt++)
		{
			Node* &root=ROOT[rt]=NULL;
			Build(root,rt,s);
		}
	}
	return 0;
}
