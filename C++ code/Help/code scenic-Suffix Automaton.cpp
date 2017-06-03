#include<cstdio>
#include<cassert>
using namespace std;
struct Node
{
	Node *green,*edge[26];
	int max_len;
	Node(const int _max_len):green(NULL),max_len(_max_len){for(int i=0;i<26;i++)edge[i]=NULL;}
}*ROOT,*LAST;
void Extend(const int c)
{
	Node *cursor=LAST;LAST=new Node((LAST->max_len)+1);
	for(;cursor&&!cursor->edge[c];cursor=cursor->green)cursor->edge[c]=LAST;//添加LAST的所有黑色字串 
	if(!cursor)LAST->green=ROOT;//其實圖上沒有畫綠色邊的點，代表著它的綠色邊是直接指向代表空串的根結點的 
	else
	{
		Node *potential_green=cursor->edge[c];//找出最長的綠色字串(為了要讓LAST代表所有後綴，要決定綠色邊連到哪)，在圖上會走到哪個節點 
		if((potential_green->max_len)==(cursor->max_len+1))LAST->green=potential_green;//剛剛好potential_green代表的字串全部都是LAST的後綴，可以直接將LAST的綠色字串添加完成 
		else
		{
			assert((potential_green->max_len)>(cursor->max_len+1));//potential_green有些字串不是LAST的後綴
			Node *seperated_node=new Node((cursor->max_len)+1);//從potential_green分離出想要的節點，恰好代表LAST的所有綠色字串 
			for(;cursor&&cursor->edge[c]==potential_green;cursor=cursor->green)cursor->edge[c]=seperated_node;//添加seperated_node的所有黑色字串，同時可能毀掉部分potential_green的代表字串集合 
			for(int i=0;i<26;i++)seperated_node->edge[i]=potential_green->edge[i];//讓seperated_node接管原本potential_green黑色邊的功能 
			seperated_node->green=potential_green->green;//添加seperated_node的所有綠色字串 
			potential_green->green=seperated_node;//利用綠色邊修復potential_green的代表字串集合 
			LAST->green=seperated_node;//添加LAST的所有綠色字串 
		}
	}
}
char S[10000001],A[10000001];
int N;
int main()
{
	scanf("%d%s",&N,S);
	ROOT=LAST=new Node(0);//SAM的根結點代表空串，max_len當然是0 
	for(int i=0;S[i];i++)Extend(S[i]-'a');
	while(N--)
	{
		scanf("%s",A);
		Node *cursor=ROOT;
		bool ans=true;
		for(int i=0;A[i];i++)
		{
			cursor=cursor->edge[A[i]-'a'];
			if(!cursor){ans=false;break;}//圖上沒有路可以走了，非S的子字串 
		}
		puts(ans?"Yes":"No");
	}
	return 0;
}
