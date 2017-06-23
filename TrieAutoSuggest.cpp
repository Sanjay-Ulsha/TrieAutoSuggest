#include<bits/stdc++.h>
#define	ALPHABET_SIZE	26
using namespace std;

char s[100];
int si=0;

typedef struct tnode TNode;
struct tnode
{
	bool isEOW;
	TNode *next[ALPHABET_SIZE];
};

TNode *createTrieNode()
{
    TNode *newNode = (TNode*)malloc(sizeof(TNode));
    newNode->isEOW = false;
    int i;
    for(i=0;i<26;i++)
        newNode->next[i] = NULL;
    return newNode;
}

bool insertWordInTrie(TNode *root, char *word)
{
  TNode *t=root;
  for(int i=0;word[i]!='\0';i++)
  {
   if(!(t->next[word[i]-'a']))
   {
     t->next[word[i]-'a']=createTrieNode();
     t=t->next[word[i]-'a'];
   }
   else
   {
     t=t->next[word[i]-'a'];
    
     if(!(i^(strlen(word)-1)) && t->isEOW)
      return false;
   } 
  }
  t->isEOW=true;
  return true;
}

bool search(TNode *root, char *word)
{
 TNode *t=root;
  for(int i=0;word[i]!='\0';i++)
  {
   if(t->next[word[i]-'a'])
   {
     t=t->next[word[i]-'a'];
    
     if(!(i^(strlen(word)-1)) && t->isEOW)
      return true;
   } 
  }
  return false;
}

bool leaf(TNode *root)
{
  return (root->isEOW);
}

bool freeNode(TNode *root)
{
  for(int i=0;i<ALPHABET_SIZE;i++)
    if(root->next[i])
      return false;
 
  return true;
}

bool deleteTrie(TNode *root, char *word,int l,int len)
{
  if(root)
  {
    if(!(l^len))
    {
      if(root->isEOW)
      {
        root->isEOW=false;
         
          if(freeNode(root))
           return true;
        return false;
      }
    }
    else
    {
      if( deleteTrie(root->next[word[l]-'a'],word,l+1,len) )
      {
        free(root->next[word[l]-'a']);
         root->next[word[l]-'a']=NULL;
        
        return (!leaf(root) && freeNode(root));
      }   
    }
  }
  return false;
}

void deleteWordFromTrie(TNode *root, char *word)
{
  if(strlen(word)>0)
    deleteTrie(root,word,0,strlen(word));
}

void printWordsInTrie(TNode* root,char *prefix)
{
  if(!root)
    return;
  if(root->isEOW)
    printf("%s%s\n",prefix,s);
   for(int i=0;i<ALPHABET_SIZE;i++)
   {
     if(root->next[i])
     {
       s[si]=(char)(i+'a');
        si++;
       s[si]='\0';
       printWordsInTrie(root->next[i],prefix);
       si--;
       s[si]='\0';
     }
   }
}

void autoSuggest(TNode *root,char *prefix)
{
	if(prefix[0]=='\0')
	{
	  cout<<"Please enter a prefix.";
	 return;
	}
	for(int i=0;prefix[i]!='\0';i++)
	{
	  if(root->next[prefix[i]-'a'])
	    root=root->next[prefix[i]-'a'];
	  else
	    { 
	    	cout<<"No words in Trie with given prefix.";
	    	return;
	    }
	}
    printWordsInTrie(root,prefix);	
}

int main()
{
	TNode *root=createTrieNode();
	char prefix[]="ca";
	
	insertWordInTrie(root,"sanju");
	insertWordInTrie(root,"sanjay");
	insertWordInTrie(root,"car");
	insertWordInTrie(root,"cherry");
	insertWordInTrie(root,"cart");
	
	//scanf("%s",prefix);
	
	//(search(root,"sanju")) ? cout<<"present " : cout<<"Nope ";
	//deleteWordFromTrie(root,"sanju");
	//(search(root,"sanju")) ? cout<<"present ": cout<<"Nope ";
	
	autoSuggest(root,prefix);
	
	return 0;
}
