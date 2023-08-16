#include <stdio.h>

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

int main()
{
    State cur_state = {8,0,0} , result;
    printf("Trang Thai Ban Dau \n"); show(cur_state);
    int opt;
    for(opt=0;opt<6;opt++)
    {
        if(call_operators(cur_state,&result,opt))
        {
            printf("Hanh Dong %s Thanh Cong\n",action[opt]);
            show(result);
        } else
            printf("Hanh Dong %s Khong Thanh Cong\n",action[opt]);
    }
    return 0;
}