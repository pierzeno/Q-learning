#include <stdio.h>
#include <iostream>
#include <map>
#include <iomanip>
using namespace std;

int N = 3;
int M = 3;
int MAX_MOVES = 4;

float max_reward(int next_x, int next_y){
    float max_v = -1;
    float tmp;
    for(int k=0; k<MAX_MOVES; k++){
            tmp = qtable[next_x][next_y][k];
            if(tmp > max_v){
                max_v = tmp;
            }
        }
    return max_v;
}

int main (){
    
    //grid where our agent will move
    int grid[N][M];

    //in the worst case, in a cell of the grid, our agent can do 4 moves
    // up, down, left, right
    //int max_moves = 4;
    int num_cells = N*M;
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
    int max_r = -1;
    float current_k;
    int action_k;
    int next_x = current_x;
    int next_y = current_y;
    float learning;
    while(end != true){
        for(int k=0; k<MAX_MOVES; k++){
            current_k = qtable[current_x][current_y][k];
            //k: 0 up, 1 down, 2 left, 3 right
            if(current_k > max_r){
                if(k==0){ //up
                    action_k=k;
                    next_x++;
                }
                if(k==1){ //down
                    action_k=k;
                    next_x--;
                }
                if(k==2){ //left
                    action_k=k;
                    next_y--;
                }
                if(k==3){ //right
                    action_k=k;
                    next_y++;
                }
            }
        }
        learning = (1-alfa)*qtable[current_x][current_y][action_k]+alfa*(grid[next_x][next_y]+beta*max_reward(next_x,next_y));
    
    }
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

    return 0;
}