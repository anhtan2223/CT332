#include <stdio.h>
#include <stdlib.h>
#define tankcapacity_X 9
#define tankcapacity_Y 4
#define empty 0
#define goal 6
#define Maxlength 100

//Hang chuoi de in ra cac hanh dong
const char* action[] = {
    "First State", "pour Water Full X", "pour Water Full Y", "pour Water Empty X",
        "pour Water Empty Y", "pour Water X to Y", "pour Water Y to X"
};

//Khai bao cau truc trang thai
typedef struct {
    int x;
    int y;
}State;

//Khoi tao trang thai binh X = 0 va binh Y = 0 (Trang thai bat dau)
void makeNullState(State *state) {
    state->x = 0;
    state->y=0;
}

//In
void print_State(State state) {
    printf("\n  X: %d  --- Y: %d", state.x, state.y);
}
// Kiem tra muc tieu
int goalcheck(State state) {
    return (state.x == goal || state.y == goal);
}

// Lam day binh X
int pourWaterFullX(State cur_state, State *result) {
    if(cur_state.x < tankcapacity_X) {
        result->x = tankcapacity_X;
        result->y = tankcapacity_Y;
        return 1;
    }
    return 0;
}

// Lam day binh Y
int pourWaterFullY(State cur_state, State *result) {
    if(cur_state.y < tankcapacity_Y) {
        result->y = tankcapacity_Y;
        result->x = tankcapacity_X;
        return 1;
    }
    return 0;
}

// Lam rong binh X
int pourWaterEmptyX(State cur_state, State *result) {
    if(cur_state.x > 0 ) {
        result->x = empty;
        result -> y = cur_state.y;
        return 1;
    }
    return 0;
}

// Lam rong binh Y
int pourWaterEmptyY(State cur_state, State *result) {
    if(cur_state.y > 0 ) {
        result->y = 0;
        result->x = cur_state.x;
        return 1;
    }
    return 0;
}


// Chuyen nuoc tu X sang Y
int pourWaterXY(State cuz_state, State*result) {
    if(cuz_state.x > 0 && cuz_state.y < tankcapacity_Y){
//        result->x = max(cuz_state.x - (tankcapacity_Y - cuz_state.y), empty);
//        result ->y = min(cuz_state.x + cuz_state.y, tankcapacity_Y);
        
        
//        Max
        if(cuz_state.x - (tankcapacity_Y - cuz_state.y) > empty) {
            result -> x =cuz_state.x - (tankcapacity_Y - cuz_state.y);
        }else {
            result-> x = empty;
        }
        
//        Min
        if(cuz_state.x + cuz_state.y < tankcapacity_Y) {
            result -> y =cuz_state.x + cuz_state.y;
        }else {
            result->y= tankcapacity_Y;
        }
        return 1;
    }
    return 0;
}

// Chuyen nuoc tu Y sang X
int pourWaterYX(State cuz_state, State*result) {
    if(cuz_state.y > 0 && cuz_state.x < tankcapacity_X){
//        result->y = max(cuz_state.y - (tankcapacity_X - cuz_state.x), empty);
//        result ->x = min(cuz_state.y + cuz_state.x, tankcapacity_X);
        
//        Max
        if(cuz_state.y - (tankcapacity_X - cuz_state.x) > empty) {
            result->y =cuz_state.y - (tankcapacity_X - cuz_state.x);
        }else {
            result->y = empty;
        }
        
//        Min
        if(cuz_state.y + cuz_state.x < tankcapacity_X) {
            result->x = cuz_state.y + cuz_state.x;
        }else {
            result->x = tankcapacity_X;
        }
        return 1;
    }
    return 0;
}
//Goi cac hanh dong
int call_operator(State cuz_state, State*result, int option) {
    //    option = 0;
    switch(option){
        case 1: return pourWaterFullX(cuz_state, result);
        case 2: return pourWaterFullY(cuz_state, result);
        case 3: return pourWaterEmptyX(cuz_state, result);
        case 4: return pourWaterEmptyY(cuz_state, result);
        case 5: return pourWaterXY(cuz_state, result);
        case 6: return pourWaterYX(cuz_state, result);
        default : printf("Loi!");
            return 0;
    }
}
    


//Code chính Bai2:
    
//Khai bao cau truc nut
typedef struct Node {
    State state;
    struct Node* Parent; //(0,4) se lam cha cua (9,4)
    int no_function;
}Node;

//Khai bao cau truc Stack
typedef struct {
    Node* Elements[Maxlength];
    int Top_idx;
}Stack;

//Dua 1 phan tu len ngan xep
void push(Node* x, Stack* stack) {
//    if(full_Stack(*stack)) {
//        printf("Loi! Ngan xep da day.");
//    }
    
    if(stack->Top_idx == 0) {
        printf("Loi! Ngan xep da day.");
    }
    else {
        stack->Top_idx -=1;
        stack->Elements[stack->Top_idx] = x;
    }
}

//Khoi tao ngan xep rong
void makeNull_Stack(Stack*stack) {
    stack->Top_idx = Maxlength;
}

//Kiem tra ngan xep co rong khong?
int empty_Stack(Stack stack) {
    return stack.Top_idx == Maxlength;
}

//Kiem tra ngan xep co day khong?
int full_Stack(Stack stack) {
    return stack.Top_idx == 0;
}

//Tra ve phan tu tren dinh ngan xep
Node*top(Stack stack) {
    if(!empty_Stack(stack)) {
        return stack.Elements[stack.Top_idx];
    }
    return NULL;
}

//Xoa phan tu tai dinh ngan xep
void pop(Stack *stack) {
    if(!empty_Stack(*stack))
        stack->Top_idx +=1;
    else printf("Loi! Ngan xep dang rong.");
}

int compareStates(State stateA, State stateB) {
    return stateA.x==stateB.x && stateA.y==stateB.y;
}
//Tim trang thai trong Stack
int find_State(State state, Stack openStack) {
    while(!empty_Stack(openStack)) {
        if(compareStates(top(openStack) -> state,state))
            return 1;
        pop(&openStack);
    }
    return 0;
}


//Thuat toan duyet theo chieu sau
Node* DFS_Algorithm(State state) {
//    Khai bao 2 ngan xep Open va Close
    Stack Open_DFS;
    Stack Close_DFS;
    makeNull_Stack(&Open_DFS);
    makeNull_Stack(&Close_DFS);
    
//    Tao nut trang thai cha
    Node*root = (Node*) malloc(sizeof(Node));
    root->state = state;
    root->Parent = NULL;
    root->no_function = 0;
    push(root, &Open_DFS);
    while(!empty_Stack(Open_DFS)) {
//        Lay 1 dinh trong ngan xep
        Node* node = top(Open_DFS);
        pop(&Open_DFS);
        push(node, &Close_DFS);
//        Kiem tra xem dinh lay duoc co phai goal?
        if(goalcheck(node->state))
            return node;
        int opt;
//        Goi cac phep toan trang thai
        for(opt = 1; opt<=6; opt++) {
            State newstate;
            makeNullState(&newstate);
            if(call_operator(node->state, &newstate, opt)) {
                if(find_State(newstate, Close_DFS))
                    continue;
                Node* newNode = (Node*) malloc(sizeof(Node));
                newNode->state = newstate;
                newNode->Parent= node;
                newNode->no_function=opt;
                push(newNode, &Open_DFS);
            }
        }
    }
    return NULL;
}

//In ket qua chuyen nuoc de dat goal
void print_WaysToGetGoal(Node* node) {
    Stack stackPrint;
    makeNull_Stack(&stackPrint);
    //
    Node* temp = node;
    while(temp != NULL) {
        push(temp, &stackPrint);
        temp = temp->Parent;
        printf("Test \n");
    }
    // push(temp, &stackPrint); 
    
    int no_action = 0;
    while(!empty_Stack(stackPrint)) {
        printf("\nAction %d: %s", no_action, action[top(stackPrint)->no_function]);
        print_State(top(stackPrint)->state);
        pop(&stackPrint);
        no_action++;
    }
    printf("%d \n",stackPrint.Top_idx);

}



int main(int argc, const char * argv[]) {
    State cuz_state = {0,0};
    Node* p = DFS_Algorithm(cuz_state);
    printf("%d",p->state.x);
    print_WaysToGetGoal(p);

    return 0;
}
