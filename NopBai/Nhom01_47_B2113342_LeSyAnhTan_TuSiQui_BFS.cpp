#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <stack>
using namespace std;

using namespace std;
#define length 50

typedef struct{
	int tusi; 	//Bo A
	int qui;	//Bo A
	char vitri;	//Co 2 bo A va bo B
}State;

//Operator
int chuyen1TuSi(State now , State *result)
{
	if((now.vitri == 'A')?(now.tusi>=1):(now.tusi<=2))
	{
		int i =  now.vitri=='A'?-1:1;
		result->tusi = now.tusi + i ;
		result->qui  = now.qui;
		result->vitri =  now.vitri=='A'?'B':'A';
		return 1;	
	}
	return 0;
}
int chuyen1Qui(State now , State *result)
{
	if(now.vitri=='A'?now.qui>=1:now.qui<=2)
	{
		int i =  now.vitri=='A'?-1:1;
		result->tusi = now.tusi;
		result->qui  = now.qui+i;
		result->vitri =  now.vitri=='A'?'B':'A';
		return 1;	
	}
	return 0;
}
int chuyen2TuSi(State now,State *result)
{
	if(now.vitri=='A'?now.tusi>=2:now.tusi<=1)
	{
		int i =  now.vitri=='A'?-1:1;
		result->tusi = now.tusi + i*2 ;
		result->qui  = now.qui;
		result->vitri =  now.vitri=='A'?'B':'A';
		return 1;
	}
	return 0;
}
int chuyen2Qui(State now,State *result)
{
	if(now.vitri=='A'?now.qui>=2:now.qui<=1)
	{
		int i =  now.vitri=='A'?-1:1;
		result->tusi = now.tusi ;
		result->qui  = now.qui + i*2;
		result->vitri =  now.vitri=='A'?'B':'A';
		return 1;
	}
	return 0;
}
int chuyenTuSiQui(State now,State *result)
{
	if(now.vitri=='A'?(now.qui>=1&&now.tusi>=1):(now.tusi<=2&&now.qui<=2))
	{
		int i =  now.vitri=='A'?-1:1;
		result->tusi = now.tusi + i ;
		result->qui  = now.qui  + i ;
		result->vitri =  now.vitri=='A'?'B':'A';
		return 1;
	}
	return 0;
}
void show(State now)
{
	printf("State (TuSi,Qui) = (%d,%d) - thuyen dang o %c\n",now.tusi,now.qui,now.vitri);
}
int call_operator(State now,State *result,int option)
{
	switch(option)
	{
		case 0 : return chuyen1TuSi(now,result);
		case 1 : return chuyen1Qui(now,result);
		case 2 : return chuyen2TuSi(now,result);
		case 3 : return chuyen2Qui(now,result);
		case 4 : return chuyenTuSiQui(now,result);
		default : printf("Option Fail !\n"); return 0;
	}
}
const char* action[] = {"Chuyen 1 Tu Si","Chuyen 1 Qui",
				  "Chuyen 2 Tu Si","Chuyen 2 Qui",
				  "Chuyen 1 Tu Si va 1 Qui"};

int isLive(State S)
{
	if(S.qui>S.tusi && S.tusi!=0) return 0;
	if(3-S.qui>3-S.tusi && 3-S.tusi!=0) return 0;
	return 1;
}
int checkGoal(State S)
{
	return S.qui==0 && S.tusi==0 && S.vitri=='B';
}
typedef struct Node{
    int option;
    struct Node* Parent;
    State state;
}Node;

int isSame(State A,State B)
{
    return (A.tusi == B.tusi) && (A.qui == B.qui) && (A.vitri == B.vitri);
}
int findState(State state,queue<Node*> S)
{
    if(S.empty()) return 0;
    int i;
    while(!S.empty())
    {
        if(isSame(state,S.front()->state)) return 1;
        S.pop();
    }
    return 0;
}
Node* BFS_PourWater(Node* Root)
{
	queue<Node*> Open , Close;
    Open.push(Root);
    
    while(!Open.empty())
    {
        Node* X = Open.front();
        if(checkGoal(X->state)) return X;
        else
        {
            Close.push(X);
            Open.pop();
            int i;
            State temp;
            for(i=0;i<5;i++)
            {
                if(call_operator(X->state,&temp,i) && !findState(temp,Open) && !findState(temp,Close) && isLive(temp))
                {
                    Node* T = (Node*)malloc(sizeof(Node));
                    T->Parent = X;
                    T->option = i;
                    T->state  = temp;
                    Open.push(T);
                }
            }
        }
    }
}
stack<Node*> getResult(Node* result)
{
    stack<Node*> S;
    Node* temp = result;
    while(temp != NULL)
    {
        S.push(temp);
        temp = temp->Parent;
    }
    return S;
}
void printResult(stack<Node*> Sr)
{
    int it = 0;
    while(!Sr.empty())
    {
        printf("Action %d : %s \n",it,it==0?"First State":action[Sr.top()->option]);
        show(Sr.top()->state);
        Sr.pop();
        it++;
    }
}
int main()
{
	State start;
	start.tusi  = 3;
	start.qui   = 3;
	start.vitri = 'A';
	State now = start;
	int i;
	Node* Root = (Node*)malloc(sizeof(Node));
    Root->state = start;
    Root->Parent = NULL;
    Root->option = -1;
    
    Node* result = BFS_PourWater(Root);
    stack<Node*> Sr = getResult(result);
    printResult(Sr);	
}



