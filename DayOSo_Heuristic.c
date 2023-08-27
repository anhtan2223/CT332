#include <stdio.h>
#include <stdlib.h>
#define rows 3
#define cols 3
#define empty 0

typedef struct {
    int state[rows][cols];
    int eRow,eCol;//all is index

}State;
void show(State S)
{
    printf("\n  State \n");
    int i,j;
    for(i=0;i<rows;i++)
    {
        for(j=0;j<cols;j++)
            printf("%2d ",S.state[i][j]);
        printf("\n");
    }
}
//Operator
int moveUp(State now,State *result)
{
    *result = now ;
    int row = now.eRow ;
    int col = now.eCol ;
    if(row > 0)
    {
        result->eRow = row-1;
        result->eCol = col;
        result->state[row][col] = now.state[row-1][col];
        result->state[row-1][col] = empty;
        return 1;
    }
    return 0;
}
int moveDown(State now,State *result)
{
    *result = now ;
    int row = now.eRow ;
    int col = now.eCol ;
    if(row < rows-1)
    {
        result->eRow = row+1;
        result->eCol = col;
        result->state[row][col] = now.state[row+1][col];
        result->state[row+1][col] = empty;
        return 1;
    }
    return 0;
}
int moveLeft(State now,State *result)
{
    *result = now ;
    int row = now.eRow ;
    int col = now.eCol ;
    if(col > 0)
    {
        result->eRow = row;
        result->eCol = col-1;
        result->state[row][col] = now.state[row][col-1];
        result->state[row][col-1] = empty;
        return 1;
    }
    return 0;
}
int moveRight(State now,State *result)
{
    *result = now ;
    int row = now.eRow ;
    int col = now.eCol ;
    if(col < cols - 1 )
    {
        result->eRow = row;
        result->eCol = col+1;
        result->state[row][col] = now.state[row][col+1];
        result->state[row][col+1] = empty;
        return 1;
    }
    return 0;
}
int call_operator(State now,State *result,int option)
{
    switch(option)
    {
        case 0 : return moveUp(now,result);
        case 1 : return moveDown(now,result);
        case 2 : return moveLeft(now,result);
        case 3 : return moveRight(now,result);
        default:
            printf("Option Eror !\n");
            return 0;
    }
}
#define max_option 4
const char* action[] = {"Move Up","Move Down"
                        ,"Move Left","MoveRight"};
//Call Operator ALL DONE
//Heuristic
int heurictic(State S,State goal) //OSai
{
    int i,j,count=0;
    for(i=0;i<rows;i++)
        for(j=0;j<cols;j++)
            if(S.state[i][j] != goal.state[i][j]) count++; 
    return count;
}
int abs(int a)
{
    return a>0?a:-a;
}
int heurictic2(State S,State goal)
{
    int i,j,x,y;
    int sum = 0 ;
    for(i=0;i<rows;i++)
        for(j=0;j<cols;j++)
            if(S.state[i][j] != empty)
                for(x=0;x<rows;x++)
                    for(y=0;y<cols;y++)
                        if(S.state[i][j] == goal.state[x][y])
                        {
                            sum += abs(i-x) + abs(j-y);
                            // printf("Sum : S(%d %d) G(%d %d) \n",i,j,x,y);
                            x = rows;
                            y = cols; //break Goal Loop
                        }
    return sum;
}
//Heuristic OKe 
//List and Node
#define length 50
typedef struct Node{
    struct Node* parent ;
    State state;
    int option;
    int heu;
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
int isSame(State A,State B)
{
    if(A.eCol != B.eCol || A.eRow != B.eRow) return 0;
    int i,j;
    for(i=0;i<rows;i++)
        for(j=0;j<cols;j++)
            if(A.state[i][j] != B.state[i][j]) return 0;
    return 1;
}
// Node* findState(State S,List L,int *index)
// {
//     int i;
//     for(i=0;i<L.size;i++)
//     {
//         if(isSame(S,L.List[i]->state))
//         {
//             *index = i;
//             return L.List[i];
//         }
//     }
//     *index = -1; //No Found Any State --> False
//     return NULL;
// }
int findState(State S,List L)
{
    int i;
    for(i=0;i<L.size;i++)
    {
        if(isSame(S,L.List[i]->state))
        {
            return 1;
        }   
    }
    return 0;
}
void sort_List(List *L)
{
    int i,j;
    for(i=0;i<L->size;i++)
        for(j=i+1;j<L->size;j++)
            if(L->List[i]->heu > L->List[j]->heu)
            {
                Node* temp = L->List[i];
                L->List[i] = L->List[j];
                L->List[j] = temp;
            }
}
int checkGoal(State S)
{
    State goal;
    goal.state[0][0] = 1;
    goal.state[0][1] = 2;
    goal.state[0][2] = 3;
    goal.state[1][0] = 8;
    goal.state[1][1] = 0;
    goal.state[1][2] = 4;
    goal.state[2][0] = 7;
    goal.state[2][1] = 6;
    goal.state[2][2] = 5;
    goal.eRow = 1;
    goal.eCol = 1;

    return isSame(S,goal);
}
//ALL Prepare Done
//Use Best First Search
Node* BFS(Node* start,State goal)
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
        for(i=0;i<max_option;i++)
        {
            if(call_operator(X->state,&result,i))
            {
                // int iOpen , iClose;
                if(findState(result,Open) || findState(result,Close))
                    continue;
                // show(result);
                Node* new = (Node*)malloc(sizeof(Node));
                new->state = result;
                new->parent = X;
                new->option = i;
                new->heu = heurictic(result,goal);
                // show(result);
                // printf("Heurictic : %d\n",new->heu);
                pushAt(&Open,new,Open.size);
                // printf("Open Size : %d\n\n",Open.size);
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
        printf("Action %d : %s ",result.size-1-i,result.size-1-i==0?"First State":action[result.List[i]->option]);
        show(result.List[i]->state);
    }
}
int main()
{
    State start ;
    start.state[0][0] = 2;
    start.state[0][1] = 8;
    start.state[0][2] = 3;
    start.state[1][0] = 1;
    start.state[1][1] = 6;
    start.state[1][2] = 4;
    start.state[2][0] = 7;
    start.state[2][1] = 0;
    start.state[2][2] = 5;
    start.eRow = 2;
    start.eCol = 1;

    State goal;
    goal.state[0][0] = 1;
    goal.state[0][1] = 2;
    goal.state[0][2] = 3;
    goal.state[1][0] = 8;
    goal.state[1][1] = 0;
    goal.state[1][2] = 4;
    goal.state[2][0] = 7;
    goal.state[2][1] = 6;
    goal.state[2][2] = 5;
    goal.eRow = 1;
    goal.eCol = 1;

    show(start);
    // show(goal);

    State result;
    // for(int i = 0;i < max_option ; i++)
    // {
    //     if(call_operator(start,&result,i))
    //     {
    //         printf("Action : %s is Succes ",action[i]);
    //         show(result);
    //         printf("Heuristic : %d\n",heurictic(result,goal));
    //     }
    //     else printf("Action : %s is Fail\n",action[i]);
    // }

    Node* root = (Node*) malloc(sizeof(Node));
    root->state  = start;
    root->parent = NULL;
    root->option = -1 ;
    root->heu    = heurictic(start,goal); 

    printf("\n\n BFS Start \n");
    Node* nodeResult = BFS(root,goal);
    printResult(nodeResult);

    //WayToGetGoal

    return 0;
}