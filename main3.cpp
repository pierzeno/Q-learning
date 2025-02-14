#include <stdio.h>
#include <iostream>
#include <random>
#include <map>
#include <iomanip>
using namespace std;

#define N 3
#define M 3
#define MAX_MOVES 4
#define DF 0.9 //Discount Factor
#define LR 0.5 //Learning Rate

//-------------------DEFITION OF THE VARIABLE USED-------------------//
//grid where our agent will move
int grid[N][M];

//in the worst case, in a cell of the grid, our agent can do 4 moves
// up, down, left, right
//int max_moves = 4;
int num_cells = N*M;

random_device rd;  //generator random number
mt19937 gen(rd());
uniform_int_distribution<int> dist(0, 1);

float qtable[N][M][MAX_MOVES];
//------------------------------------------------------------------//

//-------------------DEFITION OF FUNCTIONS-------------------//
void initialize(){
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
}

void printGrid(){
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cout << "| " << setw(3) << grid[i][j] << " | ";
        }
        cout << endl;
    }
}

void printQTable(){
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cout << "Cell (" << i << "," << j << "): ";
            for(int k=0; k<MAX_MOVES; k++){
                cout << "| " << setw(3) << qtable[i][j][k] << " | ";
            }
            cout << endl;
        }
    }
}

void runEpisode(){
    // choose the value for discount factor (=beta) and learning rate (=alfa)
    // Q-LEARING: Q(st,at) = (1-LR)*Q(st,at) + LR*(rt+1 + DF*max(Q(st+1,a)))

    //Starting from (0,0) We try to reach the goal (that is at position (N-1,M-1))
    bool end = false;
    int current_x = 0;
    int current_y = 0;
    float max_r;
    float current_k;
    int action_k;
    int next_x = current_x;
    int next_y = current_y;
    float learning;

    int contatore = 0;
    int k_equal_action_req;

    int constraint_of_bettina = 0;
    while(end!=true && constraint_of_bettina < 50){
        contatore++;
        cout << "(" << current_x << "," << current_y << ") ";
        //for(int k=0; k<MAX_MOVES; k++){
        int k=0;
        bool flag_moves = false;
        
        max_r = -1;
        action_k = -1; /////////////////ATTENTION MAYBEEEEEEE HEEEEREEEEEEEEEEEEE ----------------
        while (k < MAX_MOVES) {
            current_k = qtable[current_x][current_y][k];
            if (current_k > max_r) {
                max_r = current_k;
                action_k = k; 
            } else if (current_k == max_r) {
                if (action_k == -1) {
                    action_k = k;
                } else {
                    action_k = (dist(gen) == 0) ? k : action_k; //choose randomly between action_k and k
                }
            }
            k++;
        }

        switch (action_k) {
            case 0: next_x = current_x - 1; cout << "up" << endl; break; // Up
            case 1: next_x = current_x + 1; cout << "Down" << endl; break; // Down
            case 2: next_y = current_y - 1; cout << "Left" << endl; break; // Left
            case 3: next_y = current_y + 1; cout << "Right" << endl; break; // Right
        }
        
        float max_v = -1.0f;
        for (int z = 0; z < MAX_MOVES; z++) {
            if (qtable[next_x][next_y][z] > max_v) {
                max_v = qtable[next_x][next_y][z];
            }
        }
        cout << "max_v" << max_v << endl;
        learning = (1-LR)*qtable[current_x][current_y][action_k]+LR*(grid[next_x][next_y]+DF*max_v);
        qtable[current_x][current_y][action_k] = learning ;

        if(next_x == N-1 && next_y == M-1){
            end = true;
            cout << "Episode completed" << endl;
        }else{
            current_x = next_x;
            current_y = next_y;
        }
        constraint_of_bettina++;
    }
}

//----------------------------------------------------------//

int main (){

    initialize();

    int choice;
    do {
        cout << "\nMENU:\n";
        cout << "1. View Grid\n";
        cout << "2. View Q-Table\n";
        cout << "3. Run Episode\n";
        cout << "4. Reset Q-Table\n";
        cout << "5. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: printGrid(); break;
            case 2: printQTable(); break;
            case 3: runEpisode(); break;
            case 4: initialize(); cout << "Q-Table reset!" << endl; break;
            case 5: cout << "Exiting..." << endl; break;
            default: cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 5);
    
    return 0;
}