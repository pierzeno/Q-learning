 learning = (1-LR)*qtable[current_x][current_y][action_k]+LR*(grid[next_x][next_y]+DF*max_v);
        qtable[current_x][current_y][action_k] = learning ;