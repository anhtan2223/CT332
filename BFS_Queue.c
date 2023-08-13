#include <stdio.h>
#include <mm_malloc.h>

#define fullX 9
#define fullY 4
#define goal  6
#define empty 0
#define length 30

typedef struct{
    int x;
    int y;
}State;

typedef struct Node{
    State state;
    struct Node* Parent;
    int option ;
}Node;
typedef struct{
    int front,rear;
    Node* List[length];
}Queue;
void makeNullQueue(Queue *Q)
{
    Q->front = -1;
    Q->rear  = -1;
}
int isEmpty(Queue Q)
{
    return (Q.front > Q.rear) || (Q.front == -1) ;
}
int isFull(Queue Q)
{
    return Q.rear == length-1;
}
int enQueue(Queue *Q,Node* node)
{
    if(!isFull(*Q))
    {
        Q->rear++;
        // if(Q->front == -1 ) Q->front++;
        Q->List[Q->rear] = node;
        return 1;
    }
    printf("Queue Full Cannot Enter New Elements\n");
    return 0;
}
int deQueue(Queue *Q)
{
    if(!isEmpty(*Q))
    {
        Q->front++;
        return 1;
    }
    printf("Queue Empty Cannot Delele any Node");
    return 0;
}
Node* Front(Queue Q)
{
    return Q.front ;
}
int SizeQueue(Queue Q)
{
    return isEmpty(Q)?0:Q.rear-Q.front;
}
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
    if(now.y == fullY || now.x == empty) return 0;
    else{
        result->x = now.x-(fullY-now.y)>0?now.x-(fullY-now.y)>0:0 ;
        result->y = now.y+now.x<fullY?now.y+now.x:fullY ;
    }
    return 1;
}
int pourYX(State now,State *result)
{
    if(now.y != empty && now.x != fullX)
    {
        result->x = now.x+now.y>fullX?fullX:now.x+now.y ;
        result->y = now.y-(fullX-now.x)<empty?empty:now.y-(fullX-now.x);
        return 1;
    }
    return 0;
}
int emptyX(State now,State *result)
{
    if(now.x != empty)
    {
        result->x = empty;
        result->y = now.y;
        return 1;
    }
    return 0;
}
int emptyY(State now,State *result)
{
    if(now.y == 0) return 0;
    result->x = now.x;
    result->y = empty;
    return 1;
}
int call_operator(State now,State *result,int option)
{
    switch(option)
    {
        case 0: return pourX(now,result);
        case 1: return pourY(now,result);
        case 2: return emptyX(now,result);
        case 3: return emptyY(now,result);
        case 4: return pourXY(now,result);
        case 5: return pourYX(now,result);
        default: printf("Option Choose not Available!");
        return 0;
    }
}
char* action[] = {"Pour full X","Pour full Y","Empty X","Empty Y","Pour X to Y","Pour Y to X"};

void show(State S)
{
    printf("Sate (X,Y) = (%d,%d) \n",S.x,S.y);
}
int main()
{
    State start,result;
    start.x = 1;
    start.y = 2;
    show(start);
    for(int i=0;i<6;i++)
    {
        if(call_operator(start,&result,i))
        {
            printf("Action %-15s : Sucsess \n",action[i]);
            show(result);
        }
        else printf("Action %-15s : Fail\n",action[i]);
    }
    return 0;
}