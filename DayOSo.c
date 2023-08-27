#include <stdio.h>
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
    show(goal);

    State result;
    for(int i = 0;i < max_option ; i++)
    {
        if(call_operator(start,&result,i))
        {
            printf("Action : %s is Succes",action[i]);
            show(result);
        }
        else printf("Action : %s is Fail\n",action[i]);
    }

    return 0;
}