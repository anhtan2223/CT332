#include <stdio.h>
#include <stdlib.h>


#define length 50
typedef struct{
	int tusi; 	//Bo A
	int qui;	//Bo B
	char vitri;	//Co 2 bo A va bo B
}State;


typedef struct Node{
    int option;
    struct Node* Parent;
    State state;
}Node;

typedef struct {
    int top; //top meaning location where pop item
    Node* List[length];
}Stack;

void makenullStack(Stack *S)
{
    S->top = -1;
}
int isEmpty(Stack S)
{
    return S.top == -1;
}
int isFull(Stack S)
{
    return S.top == length-1;
}
void push(Node* N,Stack* S)
{
    if(!isFull(*S))
    {
        S->top++;
        S->List[S->top] = N;
    }
        
    else printf("Error Stack Full \n");
}

void pop(Stack* S)
{
    if(!isEmpty(*S))
        S->top--;
    else printf("Stack Empty");
}

Node* top(Stack *S)
{
    if(!isEmpty(*S))
    {
        return S->List[S->top];
    }
    return NULL;
}
//MakeNull Empty Full Pop Top Push


//Operator
int chuyen1TuSi(State now , State *result)
{
	if(now.tusi != 0)
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
	if(now.qui != 0)
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
	if(now.tusi > 1)
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
	if(now.qui > 1)
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
	if(now.qui != 0 && now.tusi!=0)
	{
		int i =  now.vitri=='A'?-1:1;
		result->tusi = now.tusi + i ;
		result->qui  = now.qui  + i ;
		result->vitri =  now.vitri=='A'?'B':'A';
		return 1;
	}
	return 0;
}
int show(State now)
{
	printf("State (TuSi,Qui) = (%d,%d) - thuyen dang o %c\n",now.tusi,now.qui,now.vitri);
}
int call_operators(State now,State *result,int option)
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
char *action[] = {"Chuyen 1 Tu Si","Chuyen 1 Qui","Chuyen 2 Tu Si"
				 ,"Chuyen 2 Qui" , "Chuyen 1 Tu Si va 1 Qui"};
int isSame(State A,State B)
{
    return (A.tusi == B.tusi) && (A.qui == B.qui);
}
int findState(State state,Stack stack)
{
    if(isEmpty(stack)) return 0;
    int i;
    for(i=0;i<=stack.top;i++)
    {
        if(isSame(state,stack.List[i]->state)) return 1;
    }
    return 0;
}
Node* DFS(Node* Root)
{
    Stack Open,Close;
    makenullStack(&Open);
    makenullStack(&Close);
    push(Root,&Open);
    
    while(!isEmpty(Open))
    {
        Node* X = top(&Open);
        if(X->state.tusi == 0 && X->state.qui == 0) return X;
        else
        {
            push(X,&Close);
            pop(&Open);
            int i;
            State temp;
            for(i=0;i<5;i++)
            {
                if(call_operators(X->state,&temp,i) && !findState(temp,Open) && !findState(temp,Close) )
                {
                    Node* T = (Node*)malloc(sizeof(Node));
                    T->Parent = X;
                    T->option = i;
                    T->state  = temp;
                    push(T,&Open);
                    // Show(temp);
                }
            }
        }
    }
    return NULL;
}
Stack getResult(Node* result)
{
    Stack S;
    Node* temp = result;
    makenullStack(&S);
    while(temp != NULL)
    {
        push(temp,&S);
        temp = temp->Parent;
    }
    return S;
}
void printResult(Stack Sr)
{
    // printf("Action 0 : Frist State \n");
    // Node* temp = top(&S);
    int it = Sr.top;
    while(!isEmpty(Sr))
    {
        printf("Action %d : %s \n",it-Sr.top,it-Sr.top==0?"First State":action[top(&Sr)->option]);
        show(top(&Sr)->state);
        pop(&Sr);
    }
}
int main()
{
    State start,temp;
    start.qui = 3;
    start.tusi = 3;
    Node* Root = (Node*)malloc(sizeof(Node));
    Root->state = start;
    Root->Parent = NULL;
    Root->option = -1;
    
//    Node* result = DFS(Root);
//    Stack Sr = getResult(result);
//    printResult(Sr);
	int i;
	for(i=0;i<5;i++)
	{
		if(call_operators(start,&start,i))
		{
			printf("Action : %s Succes \n",action[i]);
			show(start);
		}
		else printf("Action : %s Fail \n",action[i]);
	}
    
    return 0;
}
