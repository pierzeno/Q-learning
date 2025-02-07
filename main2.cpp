#include <stdio.h>
#include <iostream>
#include <random>
#include <map>
#include <iomanip>
using namespace std;

int N = 3;
int M = 3;
int MAX_MOVES = 4;

/*float max_reward(int next_x, int next_y, float (&qtable)[N][M][MAX_MOVES]){
    float max_v = -1;
    float tmp;
    for(int k=0; k<MAX_MOVES; k++){
            tmp = qtable[next_x][next_y][k];
            if(tmp > max_v){
                max_v = tmp;
            }
        }
    return max_v;
}*/

int main (){
    
    //grid where our agent will move
    int grid[N][M];

    //in the worst case, in a cell of the grid, our agent can do 4 moves
    // up, down, left, right
    //int max_moves = 4;
    int num_cells = N*M;

    random_device rd;  //generatore numeri casuali
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 1);
    //int qtable[N][M];
    //map<std::pair<pair<int, int>, int>, float> qtable;
    float qtable[N][M][MAX_MOVES];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            for(int k=0; k<MAX_MOVES; k++){

                // otherwise for all the other case, no constraints
                //qtable[make_pair(make_pair(i,j), k)] = 0.0f;
                qtable[i][j][k] = 0.0f;
                //4 moves: // up, down, left, right
                //k: 0 up, 1 down, 2 left, 3 right
                //We have to add some limitations for the cells in which agent can't do some moves

                //(0,X) not: up
                //(0,0) not: up, left
                //-------------------
                //(X,0) not: left
                //(N-1,0) not: left, down
                //-------------------
                //(N-1,X) not: down
                //(N-1,M-1) not: down rigth
                //-------------------
                //(X,M-1) not: rigth
                //(0,M-1) not: rigth up
                if(i == 0){
                    if (j == 0){
                        if(k == 2){
                            qtable[i][j][k] = -1.0f;
                        }
                    }
                    if(k == 0){
                        qtable[i][j][k] = -1.0f;
                    }
                }
                if(j == 0){
                    if(k == 2){
                        qtable[i][j][k] = -1.0f;
                    }
                    if(i == N-1){
                        if(k == 1){
                            qtable[i][j][k] = -1.0f;
                        }
                    }
                }
                if(i == N-1){
                    if(k == 1){
                        qtable[i][j][k] = -1.0f;
                    }
                    if(j == M-1){
                        if(k == 3){
                            qtable[i][j][k] = -1.0f;
                        }
                    }
                }
                if(j == M-1){
                    if(k == 3){
                        qtable[i][j][k] = -1.0f;
                    }
                    if(i == 0){
                        if(k == 0){
                            qtable[i][j][k] = -1.0f;
                        }
                    }
                }
            }
        }
    }

    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            grid[i][j] = 0 ;
        }
    }

    // we start to reach the goal from position field[0][0]
    // goal is in position field[N-1][M-1], so we set 1 as payoff in [N-1][M-1]

    grid[N-1][M-1] = 1 ;

    // choose the value for discount factor (=beta) and learning rate (=alfa)
    // Q-LEARING: Q(st,at) = (1-alfa)*Q(st,at) + alfa*(rt+1 + beta*max(Q(st+1,a)))
    float beta = 0.9;
    float alfa = 0.5;

    //Starting from (0,0) We try to reach the goal (that is at position (N-1,M-1))
    bool end = false;
    int current_x = 0;
    int current_y = 0;
    int max_r;
    float current_k;
    int action_k;
    int next_x = current_x;
    int next_y = current_y;
    float learning;

    //-----------------------------------
    cout << "INITIAL" << endl;
    cout << "GRID" << endl;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cout << "| " << setw(3) << grid[i][j] << " | ";
        }
        cout << endl;
    }

    cout << "Q-TABLE" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            for(int k=0; k<MAX_MOVES; k++){
                cout << "| " << setw(3) << qtable[i][j][k] << " | ";
            }
            cout << endl;
        }
    }
    //-----------------------------------
    int contatore = 0;
    int k_equal_action_req;
    while(end!=true){
        contatore++;
        cout << "(" << current_x << "," << current_y << ")" << endl;
        //for(int k=0; k<MAX_MOVES; k++){
        int k=0;
        bool flag_moves = false;
        /*max_r = -1;
        while(k<MAX_MOVES){
        //while(flag_moves!=true){
            //k: 0 up, 1 down, 2 left, 3 right
            current_k = qtable[current_x][current_y][k];
            if(current_k >= max_r){
                max_r = current_k;
                //if(k==0 && qtable[tmp_next_x--][current_y][k]!=-1 && tmp_next_x-- >= 0 && tmp_next_x-- <= 3){ //up
                if(k==0){ //up
                    action_k=k;
                    next_x--;
                    //flag_moves = true;
                }
                if(k==1){ //down
                    action_k=k;
                    next_x++;
                    //flag_moves = true;
                }
                if(k==2){ //left
                    action_k=k;
                    next_y--;
                    //flag_moves = true;
                }
                if(k==3){ //right
                    action_k=k;
                    next_y++;
                    cout << "next_y = " << next_y << endl;
                    //flag_moves = true;
                }
            }
            k++;
        }*/
        max_r = -1;
        action_k = -1;
        while (k < MAX_MOVES) {
            current_k = qtable[current_x][current_y][k];
            if (current_k == max_r) {
                action_k = (dist(gen) == 0) ? k : action_k; //choose randomly between action_k and k
            } else if (current_k > max_r) {
                max_r = current_k;
                action_k = k; 
            }
            k++;
        }

        switch (action_k) {
            case 0: next_x = current_x - 1; break; // Up
            case 1: next_x = current_x + 1; break; // Down
            case 2: next_y = current_y - 1; break; // Left
            case 3: next_y = current_y + 1; cout << "next_y = " << next_y << endl; break; // Right
        }
        //}
        float max_v = -1.0f;
        for (int z = 0; z < MAX_MOVES; z++) {
            if (qtable[next_x][next_y][z] > max_v) {
                max_v = qtable[next_x][next_y][z];
            }
        }
        learning = (1-alfa)*qtable[current_x][current_y][action_k]+alfa*(grid[next_x][next_y]+beta*max_v);
        qtable[current_x][current_y][action_k] = learning ;

        if(next_x == N-1 && next_y == M-1){
            end = true;
        }else{
            current_x = next_x;
            current_y = next_y;
        }
        cout << "end = " << end << endl;
    }
    //-----------------------------------
    cout << "INITIAL" << endl;
    cout << "GRID" << endl;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cout << "| " << setw(3) << grid[i][j] << " | ";
        }
        cout << endl;
    }

    cout << "Q-TABLE" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            for(int k=0; k<MAX_MOVES; k++){
                cout << "| " << setw(3) << qtable[i][j][k] << " | ";
            }
            cout << endl;
        }
    }
    //-----------------------------------
    return 0;
}