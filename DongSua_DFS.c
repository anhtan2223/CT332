#include <stdio.h>
#include <stdlib.h>

#define maxX 10
#define maxY 6
#define maxZ 5
#define empty 0
#define goal 8
#define length 50

typedef struct{
    int x;
    int y;
    int z;
}State;

int pourXY(State now,State *result)
{
    if(now.x == 0 || now.y == maxY) return 0;
    result->x = now.x-(maxY-now.y)<0 ? 0 : now.x-(maxY-now.y);
    result->y = now.y+now.x>maxY ? maxY : now.x+now.y;
    result->z = now.z;
    return 1;
}
int pourXZ(State now,State *result)
{
    if(now.x == 0 || now.z == maxZ) return 0;
    result->x = now.x-(maxZ-now.z)<0 ? 0 : now.x-(maxZ-now.z);
    result->y = now.y;
    result->z = now.z+now.x>maxZ ? maxZ : now.x+now.z;
    return 1;
}
int pourYX(State now,State *result)
{
    if(now.y == 0 || now.x == maxX) return 0;
    result->x = now.x+now.y>maxX ? maxX : now.y+now.x;
    result->y = now.y-(maxX-now.x)<0 ? 0 : now.y-(maxX-now.x);
    result->z = now.z;
    return 1;
}
int pourYZ(State now,State *result)
{
    if(now.y == 0 || now.z == maxZ) return 0;
    result->x = now.x;
    result->y = now.y-(maxZ-now.z)<0 ? 0 : now.y-(maxZ-now.z);
    result->z = now.y+now.z>maxZ ? maxZ : now.y+now.z;
    return 1;
}
int pourZX(State now,State *result)
{
    if(now.z == 0 || now.x == maxX) return 0;
    result->x = now.z+now.x>maxX ? maxX : now.z+now.x;
    result->y = now.y;
    result->z = now.z-(maxX-now.x)<0 ? 0 : now.z-(maxX-now.x);
    return 1;
}
int pourZY(State now,State *result)
{
    if(now.y == 0 || now.z == maxZ) return 0;
    result->x = now.x;
    result->y = now.y+now.z>maxY ? maxY : now.y+now.z;
    result->z = now.z-(maxY-now.y) < 0 ? 0 : now.z-(maxY-now.y);
    return 1;
}
int call_operators(State now,State *result ,int option)
{
    switch (option)
    {
    case 0 :return pourXY(now,result);
    case 1 :return pourXZ(now,result);
    case 2 :return pourYX(now,result);
    case 3 :return pourYZ(now,result);
    case 4 :return pourZX(now,result);
    case 5 :return pourZY(now,result);
    default:printf("Error calls operator");
    return 0;
    }
}
void show(State arg)
{
    printf(" (x,y,z) = (%d,%d,%d) \n",arg.x,arg.y,arg.z);
}
const char* action[] = {"Pour Water From X to Y","Pour Water From X to Z"
                        ,"Pour Water From Y to X","Pour Water From Y to Z"
                        ,"Pour Water From Z to X","Pour Water From Z to Y"};

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
int isSame(State A,State B)
{
    return (A.x == B.x) && (A.y == B.y) && (A.z == B.z);
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
    start.x = 10;
    start.y = 0;
    start.z = 0;
    Node* Root = (Node*)malloc(sizeof(Node));
    Root->state = start;
    Root->Parent = NULL;
    Root->option = -1;
    
    Node* result = DFS_pourWater(Root);
    Stack Sr = getResult(result);
    printResult(Sr);
    
    return 0;
}
