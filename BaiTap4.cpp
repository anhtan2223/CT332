#include <stdio.h>
#include <stdlib.h>
#include <stack>

using namespace std;
#define maxX 9
#define maxY 4
#define Empty 0
#define goal 6
#define length 50

typedef struct{
    int x;
    int y;
}State;

typedef struct Node{
    int option;
    struct Node* Parent;
    State state;
}Node;

//MakeNull Empty Full Pop Top Push

int max(int a,int b)
{
    return a>b?a:b;
}
int min(int a,int b)
{
    return a<b?a:b;
}

int pourX(State now,State *result)
{
    if(now.x < maxX)
    {
        result->x = maxX;
        result->y = now.y;
        return 1;
    }
    return 0;
}

int pourY(State now , State *result)
{
    if(now.y < maxY)
    {
        result->x = now.x;
        result->y = maxY;
        return 1;
    }
    return 0;
}
int pourXY(State now,State *result)
{
    if(now.x > 0 && now.y < maxY)
    {
        result->x = max(now.x - (maxY-now.y) , Empty);
        result->y = min(maxY, now.y+now.x);
        return 1;
    }
    return 0;
}
int pourYX(State now,State *result)
{
    if(now.x < maxX && now.y >0)
    {
        result->x = min(maxX,now.x+now.y);
        result->y = max(now.y-(maxX -  now.x),Empty);
        return 1;
    }
    return 0;
}
int nullX(State now,State *result)
{
    if(now.x > 0)
    {
        result->x= Empty;
        result->y= now.y;
        return 1;
    }
    return 0;
}
int nullY(State now , State *result)
{
    if(now.y > 0)
    {
        result->x = now.x;
        result->y = Empty;
        return 1;
    }
    return 0;
}
int call_operators(State now,State *result ,int option)
{
    switch (option)
    {
    case 0 :return pourX(now,result);
    case 1 :return pourY(now,result);
    case 2 :return pourXY(now,result);
    case 3 :return pourYX(now,result);
    case 4 :return nullX(now,result);
    case 5 :return nullY(now,result);
    default:printf("Error calls operator");
    return 0;
    }
}
int isSame(State A,State B)
{
    return (A.x == B.x) && (A.y == B.y);
}
int findState(State state,stack<Node*> S)
{
    if(S.empty()) return 0;
    int i;
    while(!S.empty())
    {
        if(isSame(state,S.top()->state)) return 1;
        S.pop();
    }
    return 0;
}
void Show(State arg)
{
    printf(" (x,y) = (%d,%d) \n",arg.x,arg.y);
}
const char* action[] = {"Pour Water Full X","Pour Water Full Y"
                        ,"Pour Water From X to Y","Pour Water From Y to X"
                        ,"Pour Water Empty X","Pour Water Empty Y"};
Node* DFS_pourWater(Node* Root)
{
    stack<Node*> Open,Close;
    Open.push(Root);
    
    while(!Open.empty())
    {
        Node* X = Open.top();
        if(X->state.x == goal) return X;
        else
        {
            Close.push(X);
            Open.pop();
            int i;
            State temp;
            for(i=0;i<6;i++)
            {
                if(call_operators(X->state,&temp,i) && !findState(temp,Open) && !findState(temp,Close) )
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
    return NULL;
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
        Show(Sr.top()->state);
        Sr.pop();
        it++;
    }
}
int main()
{
    State start,temp;
    start.x = 0;
    start.y = 0;
    Node* Root = (Node*)malloc(sizeof(Node));
    Root->state = start;
    Root->Parent = NULL;
    Root->option = -1;
    
    Node* result = DFS_pourWater(Root);
    stack<Node*> Sr = getResult(result);
    printResult(Sr);
    
    return 0;
}
