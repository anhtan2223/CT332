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
int isSame(State A,State B)
{
	return (A.x == B.x) && (A.y == B.y) && (A.z == B.z);
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
    			if(call_operators(X->state,&result,i) && !findState(result,Open) && !findState(result,Close))
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
    start.x = 10;
    start.y = 0;
    start.z = 0;

    Node* root = (Node*)malloc(sizeof(Node));
    root->state = start;
    root->option = -1;
    root->Parent = NULL;
    
    Node* result = BFS_PourWater(root);
    printResultQ(result);
    return 0;
}
