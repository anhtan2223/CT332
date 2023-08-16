#include <stdio.h>

#define maxX 9
#define maxY 4
#define empty 0
#define goal 6

typedef struct{
    int x;
    int y;
}State;
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
void Show(State arg)
{
    printf(" (x,y) = (%d,%d) \n",arg.x,arg.y);
}
const char* action[] = {"Pour Water Full X","Pour Water Full Y"
                        ,"Pour Water From X to Y","Pour Water From Y to X"
                        ,"Pour Water Empty X","Pour Water Empty Y"};
int main()
{
    State cur_state = {5,4} , result;
    printf("Trang Thai Ban Dau \n"); Show(cur_state);
    int opt;
    for(opt=0;opt<6;opt++)
    {
        if(call_operators(cur_state,&result,opt))
        {
            printf("Hanh Dong %s Thanh Cong\n",action[opt]);
            Show(result);
        } else
            printf("Hanh Dong %s Khong Thanh Cong\n",action[opt]);
    }
    return 0;
}