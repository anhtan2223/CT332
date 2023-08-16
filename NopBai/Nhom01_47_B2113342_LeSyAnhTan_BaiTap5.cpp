#include <stdio.h>
#include <mm_malloc.h>
#include <queue>
#include <stack>
using namespace std;

#define fullX 9
#define fullY 4
#define goal  6
#define Empty 0
#define length 50

typedef struct{
    int x;
    int y;
}State;

typedef struct Node{
    State state;
    struct Node* Parent;
    int option ;
}Node;
int pourX(State now,State *result)
{
    if(now.x != fullX)
    {
        result->x = fullX;
        result->y = now.y;
        return 1;
    }
    return 0;
}
int pourY(State now,State *result)
{
    if(now.y==fullY) return 0;
    else
    {
        result->x = now.x;
        result->y = fullY;
    }
    return 1;
}
int pourXY(State now,State *result)
{
    if(now.y == fullY || now.x == Empty) return 0;
    else{
        result->x = now.x-(fullY-now.y)>0?now.x-(fullY-now.y)>0:0 ;
        result->y = now.y+now.x<fullY?now.y+now.x:fullY ;
    }
    return 1;
}
int pourYX(State now,State *result)
{
    if(now.y != Empty && now.x != fullX)
    {
        result->x = now.x+now.y>fullX?fullX:now.x+now.y ;
        result->y = now.y-(fullX-now.x)<Empty?Empty:now.y-(fullX-now.x);
        return 1;
    }
    return 0;
}
int emptyX(State now,State *result)
{
    if(now.x != Empty)
    {
        result->x = Empty;
        result->y = now.y;
        return 1;
    }
    return 0;
}
int emptyY(State now,State *result)
{
    if(now.y == 0) return 0;
    result->x = now.x;
    result->y = Empty;
    return 1;
}
int call_operator(State now,State *result,int option)
{
    switch(option)
    {
        case 0: return pourX(now,result);
        case 1: return pourY(now,result);
        case 2: return pourXY(now,result);
        case 3: return pourYX(now,result);
        case 4: return emptyX(now,result);
        case 5: return emptyY(now,result);
        
        default: printf("Option Choose not Available!");
        return 0;
    }
}
const char* action[] = {"Pour Water Full X","Pour Water Full Y"
                        ,"Pour Water From X to Y","Pour Water From Y to X"
                        ,"Pour Water Empty X","Pour Water Empty Y"};
void show(State S)
{
    printf("State (X,Y) = (%d,%d) \n",S.x,S.y);
}
int isSame(State A,State B)
{
	return (A.x == B.x) && (A.y == B.y);
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
        if(X->state.x == goal) return X;
        else
        {
            Close.push(X);
            Open.pop();
            int i;
            State temp;
            for(i=0;i<6;i++)
            {
                if(call_operator(X->state,&temp,i) && !findState(temp,Open) && !findState(temp,Close) )
                {
                    Node* T = (Node*)malloc(sizeof(Node));
                    T->Parent = X;
                    T->option = i;
                    T->state  = temp;
                    Open.push(T);
                    // Show(temp);
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
    // printf("Action 0 : Frist State \n");
    // Node* temp = top(&S);
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
    start.x = 0;
    start.y = 0;

    Node* root = (Node*)malloc(sizeof(Node));
    root->state = start;
    root->option = -1;
    root->Parent = NULL;
    
    Node* result = BFS_PourWater(root);
    stack<Node*> Sr = getResult(result);
    printResult(Sr);
    return 0;
}
