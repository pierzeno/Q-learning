# Q-Learning Grid Navigation Program

## Description

This program implements a simple Q-learning agent that learns to navigate a generic grid (on default the grid is a 3x3, but you can change some parameter on the code in order to change the dimensions of the grid [here](#changing-grid-dimensions)). The goal of the agent is to start at the top-left corner of the grid (position `(0, 0)`) and reach the bottom-right corner (position `(N-1, M-1)`), where the agent receives a reward.

The program uses Q-learning to decide on the best actions (up, down, left, right) at each step to maximize the accumulated reward. The Q-table is updated after each move, based on the agent's experiences.

## Key Features

- **Grid Representation**: The grid is a NxM matrix where the agent starts at `(0, 0)` and the goal is at `(N-1, M-1)`.
- **Q-Learning**: The agent learns optimal moves using the Q-learning algorithm with a discount factor (`DF`) and learning rate (`LR`).
- **Interactive Menu**: The program provides an interactive menu to:
  - View the current grid.
  - View the Q-table that stores the agent's learned values.
  - Run a single episode of learning, where the agent tries to reach the goal.
  - Reset the Q-table to restart learning.

## Requirements

- C++11 or later compiler.
- No external dependencies are required.

## Compilation

To compile the program, use the following command:

```bash
g++ -o qlearning_program main.cpp
```

This This will generate an executable named ```qlearning_program```.

## Usage

Run the program:

```bash
./qlearning_program
```

The program will present a menu with the following options:
1. **View Grid**: Display the current grid, where `0` represents an empty cell and `1` represents the goal.
2. **View Table**: Display the Q-table, which contains the learned action values for each grid cell.
3. **Run Episode**: Run a learning episode where the agent moves in the grid using Q-learning. The goal is to reach the bottom-right corner.
4. **Reset Q-Table**: Reset the Q-table to its initial state and start the learning process again.
5. **Exit**: Exit the program.

## Program Flow

1. **Initialization** : The grid is initialized with all zeros, except the goal position at `(N-1, M-1)` where the reward is set to `1`.
2. **Learning Process**: The agent starts at `(0, 0)` and explores the grid using Q-learning. The Q-table is updated at each step to reflect the best learned actions.
3. **Exploration**: The agent tries various actions (up, down, left, right) and learns from its experiences, improving its policy over time.
4. **Goal Reached**: When the agent reaches the goal, the episode ends, and the Q-table has learned the optimal path.

## Changing Grid Dimensions

To change the grid dimensions, you need to modify the values of `N` and `M` in the source code main.cpp these values define the number of rows and columns in the grid, respectively. Here’s how you can change them:
1. Open the `main.cpp` file.
2. Change the value associated to the number of rows `N` and numbers of columns `M`, from `3`, default value, to whatever you want.
   ```cpp
   #define N 3 //default value
   #define M 3 //default value
    ```

## License

This project is open source and available under the MIT License.