#include <stdio.h>
#include <stdlib.h>

#define maxX 9
#define maxY 4
#define empty 0
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
        result->x = max(now.x - (maxY-now.y) , empty);
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
        result->y = max(now.y-(maxX -  now.x),empty);
        return 1;
    }
    return 0;
}
int nullX(State now,State *result)
{
    if(now.x > 0)
    {
        result->x= empty;
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
        result->y = empty;
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
void Show(State arg)
{
    printf(" (x,y) = (%d,%d) \n",arg.x,arg.y);
}
const char* action[] = {"Pour Water Full X","Pour Water Full Y"
                        ,"Pour Water From X to Y","Pour Water From Y to X"
                        ,"Pour Water Empty X","Pour Water Empty Y"};
Node* DFS_pourWater(Node* Root)
{
    Stack Open,Close;
    makenullStack(&Open);
    makenullStack(&Close);
    push(Root,&Open);
    
    while(!isEmpty(Open))
    {
        Node* X = top(&Open);
        if(X->state.x == goal) return X;
        else
        {
            push(X,&Close);
            pop(&Open);
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
void printResutl(Stack Sr)
{
    // printf("Action 0 : Frist State \n");
    // Node* temp = top(&S);
    int it = Sr.top;
    while(!isEmpty(Sr))
    {
        printf("Action %d : %s \n",it-Sr.top,it-Sr.top==0?"Frist State":action[top(&Sr)->option]);
        Show(top(&Sr)->state);
        pop(&Sr);
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
    Stack Sr = getResult(result);
    printResutl(Sr);
    
    return 0;
}