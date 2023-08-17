#include <stdio.h>
#include <stdlib.h>
#include <stack>

using namespace std;

typedef struct{
    int trangthaily[6]; //0 Up 1 Ngua
}State;
//Operator
int LatLy(int state)
{
    if(state > 1 || state < 0) return -1;
    return state = state == 0 ? 1 : 0;
}
int UpLy(State now,State* result,int start)
{
    int i;
    if(start+3 > 6 || start < 0 ) return 0;
    for(i=0;i<6;i++)
    {
        if(i<start+3 && i>= start) result->trangthaily[i] = LatLy(now.trangthaily[i]);
        else result->trangthaily[i] = now.trangthaily[i];
    }
    return 1;
}
int call_operator(State now,State *result,int option)
{
    switch(option)
    {
        case 0 : return UpLy(now,result,0);
        case 1 : return UpLy(now,result,1);
        case 2 : return UpLy(now,result,2);
        case 3 : return UpLy(now,result,3);
        default : 
        printf("Option Fail ! \n");
        return 0;
    }
}
void show(State result)
{
    int i;
    printf("Trang Thai Cac Ly \n");
    for(i=0;i<6;i++)
        printf(" %s ",result.trangthaily[i] == 1 ? "Ngua" : "Up");
    printf("\n");
}
const char* action[]= {"Lat Ly thu 1-2-3","Lat Ly thu 2-3-4"
                        ,"Lat Ly thu 3-4-5","Lat Ly thu 4-5-6"};

int checkGoal(State S) //Tat Ca Cac Ly Deu Up
{
    int i;
    for(i=0;i<6;i++)
    {
        if(S.trangthaily[i] == 1) return 0;
    }
    return 1;
}
typedef struct Node{
    int option;
    struct Node* Parent;
    State state;
}Node;

int isSame(State A,State B)
{
    int i;
    for(i=0;i<6;i++) if(A.trangthaily[i] != B.trangthaily[i]) return 0;
    return 1;
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
Node* DFS_pourWater(Node* Root)
{
    stack<Node*> Open,Close;
    Open.push(Root);
    while(!Open.empty())
    {
        Node* X = Open.top();
        if(checkGoal(X->state)) return X;
        else
        {
            Close.push(X);
            Open.pop();
            int i;
            State temp;
            for(i=0;i<4;i++)
            {
                if(call_operator(X->state,&temp,i))
                {
					if(findState(temp,Open) || findState(temp,Close) ) continue;
                    Node* T = (Node*)malloc(sizeof(Node));
                    T->Parent = X;
                    T->option = i;
                    T->state  = temp;
                    Open.push(T);
					// printf("sizeOpen: %lu\n",Open.size());
					// printf("sizeClose: %lu\n",Close.size());
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
    int i;
    for(i=0;i<6;i++) start.trangthaily[i] = i%2?1:0;
    
    Node* Root = (Node*)malloc(sizeof(Node));
    Root->state = start;
    Root->Parent = NULL;
    Root->option = -1;
    
    Node* result = DFS_pourWater(Root);
    stack<Node*> Sr = getResult(result);
    printResult(Sr);	
    return 0;
}
