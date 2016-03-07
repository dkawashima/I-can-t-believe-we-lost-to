#include "player.h"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    gameBoard = new Board();
    playerSide = side;
	 
    if (side == BLACK){
		cerr << "our player is black" << endl;;
        oppSide = WHITE;
    } else {
		cerr << "our player is white" << endl;;
        oppSide = BLACK;
    }
    /* 
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     * FIrst Commit.
     */
}

/*
 * Destructor for the player.
 */
Player::~Player() {
    delete gameBoard;
}


void Player::setBoard(Board* board){
    gameBoard = board;
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /* 
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */ 
    gameBoard->doMove(opponentsMove, oppSide);
    Board * copyBoard;
    Board * copyBoard2;
    vector<Move *> availableOppMoves;
    //int score = gameBoard->getScore(playerSide, oppSide);
    int currScoreIn = 9999;
    int currScoreOut = -9999;
    int tempScore;
    unsigned int moveIndex = 0;

    if (gameBoard->hasMoves(playerSide) == true){
		vector<Move *> availableMoves = gameBoard->getLegalMoves(playerSide);
		cerr << "Size: " << availableMoves.size() << endl;
        for (unsigned int i = 0; i < availableMoves.size(); i++) {
            cerr << "Move " << i <<  ": " << availableMoves[i]->getX() << ", " << availableMoves[i]->getY() << endl;
            cerr << "i: " << i << endl;
            copyBoard = gameBoard->copy();
			copyBoard->doMove(availableMoves[i], playerSide);
            if (copyBoard->hasMoves(oppSide) == true){
                availableOppMoves = copyBoard->getLegalMoves(oppSide);
            
                for (unsigned int j = 0; j < availableOppMoves.size(); j++){
                    cerr << "j: " << j << endl;
                    copyBoard2 = copyBoard->copy();
                    copyBoard2->doMove(availableOppMoves[j], oppSide);
                    tempScore = copyBoard2->getScore(playerSide, oppSide);
                    if (tempScore < currScoreIn){
                        currScoreIn = tempScore;
                        cerr << "New mini: " << currScoreIn << endl;
                    }
                }

                if (currScoreIn > currScoreOut){
                    currScoreOut = currScoreIn;
                    moveIndex = i;
                }
                currScoreIn = 9999;
            } else {
                tempScore = copyBoard->getScore(playerSide, oppSide);
                if (tempScore > 0){
                    gameBoard->doMove(availableMoves[i], playerSide);
                    return availableMoves[i];
                }
            }
		}
            gameBoard->doMove(availableMoves[moveIndex], playerSide);
            return availableMoves[moveIndex];
    }
    return NULL;
}

