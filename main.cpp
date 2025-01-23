#include <stdio.h>
#include <iostream>
#include <map>
using namespace std;

int N = 3;
int M = 3;

int main (){
    
    //grid where our agent will move
    int grid[N][M];

    //in the worst case, in a cell of the grid, our agent can do 4 moves
    // up, down, left, right
    int max_moves = 4;
    int num_cells = N*M;
    //int qtable[N][M];
    map<std::pair<pair<int, int>, int>, float> qtable;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            for(int k=0; k<max_moves; k++){

                // otherwise for all the other case, no constraints
                qtable[make_pair(make_pair(i,j), k)] = 0.0f;

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
                            qtable[make_pair(make_pair(i,j), k)] = -1.0f;
                        }
                    }
                    if(k == 0){
                        qtable[make_pair(make_pair(i,j), k)] = -1.0f;
                    }
                }
                if(j == 0){
                    if(k == 2){
                        qtable[make_pair(make_pair(i,j), k)] = -1.0f;
                    }
                    if(i == N-1){
                        if(k == 1){
                            qtable[make_pair(make_pair(i,j), k)] = -1.0f;
                        }
                    }
                }
                if(i == N-1){
                    if(k == 1){
                        qtable[make_pair(make_pair(i,j), k)] = -1.0f;
                    }
                    if(j == M-1){
                        if(k == 3){
                            qtable[make_pair(make_pair(i,j), k)] = -1.0f;
                        }
                    }
                }
                if(j == M-1){
                    if(k == 3){
                        qtable[make_pair(make_pair(i,j), k)] = -1.0f;
                    }
                    if(i == 0){
                        if(k == 0){
                            qtable[make_pair(make_pair(i,j), k)] = -1.0f;
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

    pair<int,int> current_p = make_pair(0,0);
    int max_reward;
    int max_reward_k;
    while(end!=true){
        max_reward = -1;
        for(int k=0; k<max_moves; k++){
            std::pair<std::pair<int, int>, int> key = {current_p, k};
            if (qtable.find(key) != qtable.end()) {
                float reward = qtable[key];
                if (reward > max_reward) {
                    max_reward = reward;
                    max_reward_k = k;
                }
            }
        }
    } 

    /*cout << "GRID" << endl;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cout << "| " << grid[i][j] << " | ";
        }
        cout << endl;
    }

    cout << "Q-TABLE" << endl;
    int i=0;
    for (const auto& [key, value] : qtable) {
        i++;
        if(max_moves/i==1 && max_moves%i==0){
            i=0;
            cout << "[" << value << "]" << endl;
        }else{
            cout << "[" << value << "]";
        }
    }*/

    return 0;
}