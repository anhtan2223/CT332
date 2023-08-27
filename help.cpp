#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define MAX_OPERATOR 4
#define Maxlength 500
#define ROWS 3
#define COLS 3
#define EMPTY 0

typedef struct
{
    int eightPuzzle[ROWS][COLS];
    int emptyRow;
    int emptyCol;
} State;

typedef struct Node
{
    State state;
    struct Node *parent;
    int no_function;
    int heuristic;
} Node;

int compareStates(State state1, State state2)
{
    if (state1.emptyRow != state2.emptyRow || state1.emptyCol != state2.emptyCol)
        return 0;
    int row, col;
    for (row = 0; row < ROWS; row++)
        for (col = 0; col < COLS; col++)
            if (state1.eightPuzzle[row][col] != state2.eightPuzzle[row][col])
                return 0;
    return 1;
}

Node *find_State(State state, vector<Node *> v, vector<Node *>::iterator *position)
{
    vector<Node *>::iterator it = v.begin();
    if (v.size() == 0)
        return NULL;
    while (it != v.end())
    {
        if (compareStates((*it)->state, state))
        {
            *position = it;
            return *it;
        }
        it = v.erase(it);
    }
    return NULL;
}

bool compareHeuristic(Node *a, Node *b)
{
    return a->heuristic > b->heuristic;
}

int goalcheck(State state, State goal)
{
    return compareStates(state, goal);
}

int upOperator(State state, State *result)
{
    *result = state;
    int empRowCurrent = state.emptyRow, empColCurrent = state.emptyCol;
    if (empRowCurrent > 0)
    {
        result->emptyRow = empRowCurrent - 1;
        result->emptyCol = empColCurrent;
        result->eightPuzzle[empRowCurrent][empColCurrent] = state.eightPuzzle[empRowCurrent - 1][empColCurrent];
        result->eightPuzzle[empRowCurrent - 1][empColCurrent] = EMPTY;
        return 1;
    }
    return 0;
}

int downOperator(State state, State *result)
{
    *result = state;
    int empRowCurrent = state.emptyRow, empColCurrent = state.emptyCol;
    if (empRowCurrent < 2)
    {
        result->emptyRow = empRowCurrent + 1;
        result->emptyCol = empColCurrent;
        result->eightPuzzle[empRowCurrent][empColCurrent] = state.eightPuzzle[empRowCurrent + 1][empColCurrent];
        result->eightPuzzle[empRowCurrent + 1][empColCurrent] = EMPTY;
        return 1;
    }
    return 0;
}

int leftOperator(State state, State *result)
{
    *result = state;
    int empRowCurrent = state.emptyRow, empColCurrent = state.emptyCol;
    if (empColCurrent > 0)
    {
        result->emptyRow = empRowCurrent;
        result->emptyCol = empColCurrent - 1;
        result->eightPuzzle[empRowCurrent][empColCurrent] = state.eightPuzzle[empRowCurrent][empColCurrent - 1];
        result->eightPuzzle[empRowCurrent][empColCurrent - 1] = EMPTY;
        return 1;
    }
    return 0;
}

int rightOperator(State state, State *result)
{
    *result = state;
    int empRowCurrent = state.emptyRow, empColCurrent = state.emptyCol;
    if (empColCurrent < 2)
    {
        result->emptyRow = empRowCurrent;
        result->emptyCol = empColCurrent + 1;
        result->eightPuzzle[empRowCurrent][empColCurrent] = state.eightPuzzle[empRowCurrent][empColCurrent + 1];
        result->eightPuzzle[empRowCurrent][empColCurrent + 1] = EMPTY;
        return 1;
    }
    return 0;
}

int call_operators(State state, State *result, int option)
{
    switch (option)
    {
    case 1:
        return upOperator(state, result);
    case 2:
        return downOperator(state, result);
    case 3:
        return leftOperator(state, result);
    case 4:
        return rightOperator(state, result);
    default:
        printf("Error Operators!");
        return 0;
    }
}

int heuristic(State state, State goal)
{
    int row, col, count = 0;
    for (row = 0; row < ROWS; row++)
        for (col = 0; col < COLS; col++)
            if (state.eightPuzzle[row][col] != goal.eightPuzzle[row][col])
                count++;
    return count;
}

Node *best_first_search(State state, State goal)
{
    vector<Node *> Open_BFS(Maxlength);
    Open_BFS.clear();
    vector<Node *> Close_BFS(Maxlength);
    Close_BFS.clear();
    Node *root = (Node *)malloc(sizeof(Node));
    root->state = state;
    root->parent = NULL;
    root->no_function = 0;
    root->heuristic = heuristic(root->state, goal);
    Open_BFS.push_back(root);
    while (!Open_BFS.empty())
    {
        Node *node = Open_BFS.back();
        Open_BFS.pop_back();
        Close_BFS.push_back(node);
        if (goalcheck(node->state, goal))
        {
            cout << "Goal\n";
            return node;
        }
        int opt;
        for (opt = 1; opt <= MAX_OPERATOR; opt++)
        {
            State newstate;
            newstate = node->state;
            if (call_operators(node->state, &newstate, opt))
            {
                Node *newNode = (Node *)malloc(sizeof(Node));
                newNode->state = newstate;
                newNode->parent = node;
                newNode->no_function = opt;
                newNode->heuristic = heuristic(newstate, goal);
                vector<Node *>::iterator pos_Open, pos_Close;
                Node *nodeFoundOpen = find_State(newstate, Open_BFS, &pos_Open);
                Node *nodeFoundClose = find_State(newstate, Close_BFS, &pos_Close);
                if (nodeFoundOpen == NULL && nodeFoundClose == NULL)
                    Open_BFS.push_back(newNode);
                else if (nodeFoundOpen != NULL && nodeFoundOpen->heuristic > newNode->heuristic)
                {
                    Open_BFS.erase(pos_Open);
                    Open_BFS.push_back(newNode);
                }
                else if (nodeFoundClose != NULL && nodeFoundClose->heuristic > newNode->heuristic)
                {
                    Close_BFS.erase(pos_Close);
                    Open_BFS.push_back(newNode);
                }
            }
        }
        sort(Open_BFS.begin(), Open_BFS.end(), compareHeuristic);
    }
    return NULL;
}

const char *action[] = {"First state", "Move cell EMPTY to UP", "Move cell EMPTY to DOWN",
                        "Move cell EMPTY to LEFT", "Move cell EMPTY to RIGHT"};

void print_State(State state)
{
    int row, col;
    printf("\n---------\n");
    for (row = 0; row < ROWS; row++)
    {
        for (col = 0; col < COLS; col++)
            printf("|%d", state.eightPuzzle[row][col]);
        printf("|\n");
    }
    printf("---------\n");
}

void print_WaysToGetGoal(Node *node)
{
    vector<Node *> vectorPrint;
    while (node->parent != NULL)
    {
        vectorPrint.push_back(node);
        node = node->parent;
    }
    vectorPrint.push_back(node);
    int no_action = 0, i;
    for (i = vectorPrint.size()-1; i >= 0; i--)
    {
        printf("\nAction %d: %s", no_action, action[vectorPrint.at(i)->no_function]);
        print_State(vectorPrint.at(i)->state);
        no_action++;
    }
}

int main()
{
    State state;
    state.emptyRow = 1;
    state.emptyCol = 1;
    state.eightPuzzle[0][0] = 3;
    state.eightPuzzle[0][1] = 4;
    state.eightPuzzle[0][2] = 5;
    state.eightPuzzle[1][0] = 1;
    state.eightPuzzle[1][1] = 0;
    state.eightPuzzle[1][2] = 2;
    state.eightPuzzle[2][0] = 6;
    state.eightPuzzle[2][1] = 7;
    state.eightPuzzle[2][2] = 8;

    State goal;
    goal.emptyRow = 0;
    goal.emptyCol = 0;
    goal.eightPuzzle[0][0] = 0;
    goal.eightPuzzle[0][1] = 1;
    goal.eightPuzzle[0][2] = 2;
    goal.eightPuzzle[1][0] = 3;
    goal.eightPuzzle[1][1] = 4;
    goal.eightPuzzle[1][2] = 5;
    goal.eightPuzzle[2][0] = 6;
    goal.eightPuzzle[2][1] = 7;
    goal.eightPuzzle[2][2] = 8;

    printf("\nCheck\n");

    Node *p = best_first_search(state, goal);
    print_WaysToGetGoal(p);
    return 0;
}