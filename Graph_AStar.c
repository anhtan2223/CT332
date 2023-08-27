#include <stdio.h>
#include <stdlib.h>

//Graph Part
#define max_vertex 5
typedef struct{
    int h;
    int neighbour[max_vertex];
}vertex;

typedef struct{
    int countV;
    vertex vList[max_vertex]; 
}Graph;

void initGraph(int count,Graph *G)
{
    G->countV = count;
    int i,j;
    for(i=0;i<max_vertex;i++)
        for(j=0;j<max_vertex;j++)
    {
        G->vList[i].h = 0;
        G->vList[i].neighbour[j] = 0;
    }
}
//State
const char name[] = {'A','B','C','D','G'};
typedef struct{
    int vertex;
}State;

void show(State S)
{
    printf("%c",name[S.vertex]);
}
int isSame(State A,State B)
{
    return A.vertex == B.vertex ;
}
//List and Something Else
#define length 50
typedef struct Node{
    struct Node* parent ;
    State state;
    int f;
    int h;
    int g;
}Node;
typedef struct{
    Node* List[length];
    int size;
}List;
void makeNullList(List *L)
{
    L->size = 0;
}
int isListEmpty(List L)
{
    return L.size == 0;
}
int isFullList(List L)
{
    return L.size == length;
}
Node* getAt(List *L,int index)
{
    if(L->size > index) return L->List[index];
    return NULL;
}
void pushAt(List* L,Node* node,int index)
{
    if(isFullList(*L)) printf("List FULL !! \n");
    else
    {
        if(index > L->size) index = L->size;
        if(index < 0)       index = 0;
        int place = L->size-1;
        while(place > index)
        {
            L->List[place] = L->List[place-1];
            place--;
        }
        L->List[index] = node;
        L->size++;
    }
}
void delAt(List *L,int index)
{
    int len = L->size ;
    if(isListEmpty(*L)) printf("List EMPTY");
    else if(index < 0 || index > L->size) printf("Postion Empty");
    else
    {
        int place;
        for(place = index ; place+1 < len ; place++)
            L->List[place] = L->List[place+1];
        L->size--;
    }
}
Node* findState(State S,List L,int *index)
{
    int i;
    for(i=0;i<L.size;i++)
    {
        if(isSame(S,L.List[i]->state))
        {
            *index = i;
            return L.List[i];
        }
    }
    *index = -1; //No Found Any State --> False
    return NULL;
}
void sort_List(List *L)
{
    int i,j;
    for(i=0;i<L->size;i++)
        for(j=i+1;j<L->size;j++)
            if(L->List[i]->f > L->List[j]->f)
            {
                Node* temp = L->List[i];
                L->List[i] = L->List[j];
                L->List[j] = temp;
            }
}
int checkGoal(State S)
{
    return S.vertex == 4 ;
}
//Run AStar
Node* BFS(Graph G,Node* start,State goal)
{
    List Open,Close;
    makeNullList(&Open);
    makeNullList(&Close);
    pushAt(&Open,start,Open.size);
    int count = 0;
    while(!isListEmpty(Open))
    {
        Node* X = getAt(&Open,0);
        delAt(&Open,0);
        pushAt(&Close,X,Close.size);
        if(checkGoal(X->state)) return X;
        int i;
        State result;
        for(i=0;i<max_vertex;i++)
        {
            if(G.vList[X->state.vertex].neighbour[i] > 0)
            {
                result.vertex = i ; 
                int iOpen , iClose;
                Node* nOpen  = findState(result,Open,&iOpen);
                Node* nClose = findState(result,Close,&iClose);
                Node* new = (Node*)malloc(sizeof(Node));
                new->state.vertex = i;
                new->parent = X;
                new->h = G.vList[i].h;
                new->g = X->g+G.vList[X->state.vertex].neighbour[i];
                new->f = new->g + new->h ; 
                // show(result);
                if( nOpen == NULL || nClose != NULL )
                {
                // printf("Heurictic (g,h) : (%d,%d)\n",new->g,new->h);
                pushAt(&Open,new,Open.size);
                // printf("Open Size : %d\n\n",Open.size);
                }
                else if(nOpen != NULL && nOpen->f > new->f)
                {
                    delAt(&Open,iOpen);
                    pushAt(&Open,new,iOpen);
                }
                else if(nClose != NULL && nClose->f > new->f)
                {
                    delAt(&Close,iClose);
                    pushAt(&Open,new,Open.size);
                }
            }
        }
        sort_List(&Open);
        // count++;
        // if(count == 3) break;
    }
    return NULL;
}
//
void printResult(Node* new)
{
    Node* temp = new;
    List result;
    makeNullList(&result);
    while(temp != NULL)
    {
        pushAt(&result,temp,result.size);
        temp = temp->parent;
    }
    int i;
    for(i=result.size-1;i>=0;i--)
    {
        show(result.List[i]->state);
        if(i!=0) printf("-->");
        else printf("\n");

    }
}


int main()
{
    freopen("data.txt","r",stdin);
    int i,j;
    Graph G;
    initGraph(max_vertex,&G);
    for(i=0;i<max_vertex;i++)
    {
        scanf("%d",&G.vList[i].h);
        for(j=0;j<max_vertex;j++)
        {
            scanf("%d",&G.vList[i].neighbour[j]);
        }
    }
    //Input Oke

    State goal;
    goal.vertex = 4;
    printf("\nA Star GOOO \n");

    Node* start = (Node*)malloc(sizeof(Node));
    start->parent   = NULL;
    start->state.vertex    = 0;
    start->g        = 0;
    start->h        = G.vList[0].h ;
    start->f        = start->g + start->h ;

    Node* nResult = BFS(G,start,goal);
    printResult(nResult);

    return 0;
}