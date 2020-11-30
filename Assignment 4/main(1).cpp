////////////////////////////////////////////////////////////////////////////////
// SE271 - Assignment 4: Snake Arena
// Note: You will not submit this file
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "config.h"
#include "Environment.h"
#include "ConsoleCanvas.h"
#include "FileCanvas.h"

#include "MyPlayer.h"
#include "ProfessorPlayer.h"

using namespace snake_arena;

// Comment the following line to write the results into the file
#define USE_CONSOLE_CANVAS

// Example case 1:
// Play a single round with visualization
template<typename Player1, typename Player2>
void single_round_simultation() {
#ifdef USE_CONSOLE_CANVAS
    ConsoleCanvas canvas(50, 26);
    canvas.setDefaultSleepTime(50);
#else
    FileCanvas canvas("snake_results.txt");
#endif

	// The random seed "0" randomizes the fruit posisions for every round run
	Environment env(MAP_SIZE, N_FRUITS, L_SNAKES, MAX_TURNS, 4); 
	Player1 player1(MAP_SIZE);
	Player2 player2(MAP_SIZE);
	env.setPlayers(&player1, &player2);

    // Player the game!
	GameResult result = env.play(&canvas);

    // Print the game result
	switch (result) {
	case GameResult::Player1_Win:
		std::cout << "Player 1 Win! " << env.getTurns() << " turns" << std::endl;
		break;
	case GameResult::Player2_Win:
		std::cout << "Player 2 Win! " << env.getTurns() << " turns" << std::endl;
		break;
	default:
		std::cout << "Draw :) " << env.getTurns() << " turns" << std::endl;
		break;
	}
}

// Example case 2:
// Play multiple rounds without visualization
template<typename Player1, typename Player2>
void multiple_round_simultation() {
    const int N_ROUNDS = 100;
    int player1_win = 0;
    int player2_win = 0;

    for (int i = 1; i <= N_ROUNDS; ++i) {
        // With the random seed greater than 0, get the same fruit posisions
        Environment env(MAP_SIZE, N_FRUITS, L_SNAKES, MAX_TURNS, i);
        Player1 player1(MAP_SIZE);
        Player2 player2(MAP_SIZE);
        env.setPlayers(&player1, &player2);

		// Play a game round without printing it to the screen
        GameResult result = env.play();

		// Print the game result
        switch (result) {
        case GameResult::Player1_Win:
            std::cout << "Player 1 Win! " << env.getTurns() << " turns" << std::endl;
            ++player1_win;
            break;
        case GameResult::Player2_Win:
            std::cout << "Player 2 Win! " << env.getTurns() << " turns" << std::endl;
            ++player2_win;
            break;
        default:
            std::cout << "Draw :) " << env.getTurns() << " turns" << std::endl;
            break;
        }
    }

    std::cout << "Win rate: [Player 1] " << player1_win / (float)N_ROUNDS << std::endl;
    std::cout << "Win rate: [Player 2] " << player2_win / (float)N_ROUNDS << std::endl;
}

int main(void) {
    // Select one of the function call cases below for your testing purpose

    // Sample game 1
    single_round_simultation<MyPlayer, ProfNeverDie>();

    // Sample game 2
    //single_round_simultation<ProfFruitTaker, ProfNeverDie>();

    // Sample game 3
    //multiple_round_simultation<MyPlayer, ProfFruitTaker>();

    return 0;
}