#include <stdio.h>
#include <mm_malloc.h>

#define fullX 9
#define fullY 4
#define goal  6
#define empty 0
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
    return (Q.front == -1) ;
}
int isFull(Queue Q)
{
    // return Q.rear == length -1 ;
    return (Q.rear - Q.front +1)%length == 0;
    // Problem here
}
int enQueue(Queue *Q,Node* node)
{
    if(!isFull(*Q))
    {
        if(Q->front == -1 ) Q->front++;
        Q->rear = (Q->rear+1)%length;
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
        if(Q->front == Q->rear) makeNullQueue(Q);
        else Q->front = (Q->front+1)%length;
        return 1;
    }
    printf("Queue Empty Cannot Delele any Node");
    return 0;
}
Node* front(Queue Q)
{
    return Q.List[Q.front] ;
}
int sizeQueue(Queue Q)
{
    return isEmpty(Q)?0:Q.rear - Q.front +1;
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
int findState(State S,Queue Q)
{
	if(isEmpty(Q)) return 0;
	int i;
	for(i=Q.front;i<=Q.rear;i++)
		if( isSame(S,Q.List[i]->state) ) return 1;
	return 0;
}
Node* BFS_PourWater(Node* Root)
{
	Queue Open , Close;
    makeNullQueue(&Open);
    makeNullQueue(&Close);
    
    enQueue(&Open,Root);
    
    while(!isEmpty(Open))
    {
		Node* X = front(Open);
        deQueue(&Open);
        enQueue(&Close,X);
		if(X->state.x == goal) return X;
    	else
    	{
	    	int i;
			State result;
    		for(i=0;i<6;i++)
    			if(call_operator(X->state,&result,i) && !findState(result,Open) && !findState(result,Close))
    			{
    				Node* child   = (Node*)malloc(sizeof(Node));
    				child->state  = result;
    				child->Parent = X;
    				child->option = i;
    				enQueue(&Open,child);
//    				show(result);
				}
		}
	}
    return NULL;
}
void printResultQ(Node* result)
{
	 int i=0;
	Queue Qresult ;
	makeNullQueue(&Qresult);
    while(result != NULL)
    {
//    	show(result->state);
		enQueue(&Qresult,result);
    	result = result->Parent;
	}
	
	for(i = Qresult.rear ; i >= Qresult.front ; i--)
	{	
		printf("Action %d : %s \n",Qresult.rear-i,Qresult.rear-i==0?"First State":action[Qresult.List[i]->option]);
		show(Qresult.List[i]->state);
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
    printResultQ(result);
    return 0;
}
