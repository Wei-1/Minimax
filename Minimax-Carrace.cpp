#pragma GCC optimize "Ofast,omit-frame-pointer,inline"

#include <iostream>
#include <string>
#include <functional>
#include <algorithm>
#include <memory>
#include <chrono>
#include <cstring>
#include <vector>
#include <math.h>
using namespace std;
// Minimax

int UNIT_SIZE = 2;
int MOVE_SIZE = 10;

int GLOBAL_COUNT = 0;

struct Move {
    /* MOVE PARAMETERS */
    int speed;
    Move() {}
    Move(int newspeed) {
        speed = newspeed;
    }
};

inline void printMove(const Move& move) {
    /* OUTPUT LOGIC */
    cout << "OUT: " << move.speed << endl;
}

struct Unit {
    /* UNIT PARAMETERS */
    int position;
    Move* move;
    Unit() {}
    Unit(int x): position(x) {}
    void update(int pos) {
        position = pos;
    }
    void moveBy(int time) {
        /* SIMULATION LOGIC */
        position += move->speed * time;
    }
    void endMove() {
        /* END ROUND LOGIC */
    }
    void apply(Move* newmove) {
        move = newmove;
    }
};

inline int findInteract(const Unit& a, const Unit& b) {
    /* ENCOUNTER LOGIC */
    return INT32_MAX;
}

inline void interact(Unit* a, Unit* b) {
    /* INTERACTION LOGIC */
}

struct State {
    Unit units[2];
    State(/* SOME INPUT */) {
        for(int i = 0; i < UNIT_SIZE; ++i)
            units[i] = Unit(0);
    }
    State(const State& state) {
        for(int i = 0; i < UNIT_SIZE; ++i)
            units[i] = state.units[i];
    }
    void update(int* positions) {
        units[0].update(positions[0]);
        units[1].update(positions[1]);
    }
    void apply(Move* move, int playerid) {
        units[playerid].apply(move);
    }
    void play() { // array of states
        float timeLeft = 1;
        while(timeLeft > 0) {
            float earliest = timeLeft;
            Unit* a = nullptr;
            Unit* b = nullptr;
            for(int i = 0; i < UNIT_SIZE - 1; ++i) {
                for(int j = i + 1; j < UNIT_SIZE; ++j) {
                    float t = findInteract(units[i], units[j]);
                    if(t < earliest) {
                        earliest = t;
                        a = &units[i];
                        b = &units[j];
                    }
                }
            }
            timeLeft -= earliest;
            if(earliest > 0)
                for(int i = 0; i < UNIT_SIZE; ++i)
                    units[i].moveBy(earliest);
            if(a != nullptr && b != nullptr)
                interact(a, b);
        }
        for(int i = 0; i < 4; ++i)
            units[i].endMove();
    }
};

inline void printState(const State& state) {
    // cerr << state.units[0].position << " " << state.units[1].position << endl;
}

inline float evaluate(const State& state) {
    /* EVALUATION LOGIC */
    return state.units[0].position - state.units[1].position;
}

inline vector<Move> myMoves(const State& state) {
    vector<Move> moves(MOVE_SIZE);
    /* My State Possible Moves */
    for(int i = 0; i < MOVE_SIZE; ++i)
        moves[i] = Move(i);
    return moves;
}
inline vector<Move> enMoves(const State& state) {
    vector<Move> moves(MOVE_SIZE);
    /* My State Possible Moves */
    for(int i = 0; i < MOVE_SIZE; ++i)
        moves[i] = Move(i);
    return moves;
}

float minimax(const State& state, float alpha, float beta, int level, bool myturn) {
    if(level) {
        if(myturn) {
            float v = -10000000000.0;
            vector<Move> moves = myMoves(state);
            for(int i = 0; i < moves.size(); ++i) {
                State testState(state);
                testState.apply(&moves[i], 0);
                float tmpv = minimax(testState, alpha, beta, level - 1, false);
                if(tmpv > v) v = tmpv;
                if(v > alpha) alpha = v;
                if(beta <= alpha) break;
            }
            return v;
        } else {
            float v = 10000000000.0;
            vector<Move> moves = enMoves(state);
            for(int i = 0; i < moves.size(); ++i) {
                State testState(state);
                testState.apply(&moves[i], 1);
                testState.play();
                float tmpv = minimax(testState, alpha, beta, level - 1, true);
                if(tmpv < v) v = tmpv;
                if(v < beta) beta = v;
                if(beta <= alpha) break;
            }
            return v;
        }
    } else {
        GLOBAL_COUNT++;
        return evaluate(state);
    }
}

int main() {
    int round = 0;
    // Initial Input
    State state;//(/* SOME INPUT */);
    while(round < 2) {
        round++;
        // Round Input
        int positions[2] {0, 0};
        state.update(positions);
        // Action Generation
        vector<Move> moves = myMoves(state);
        // Minimax
        Move bestmove = NULL;
        float bestscore = -10000000000.0;
        for(int i = 0; i < MOVE_SIZE; ++i) {
            State testState(state);
            testState.apply(&moves[i], 0);
            float score = minimax(testState, bestscore, 10000000000.0, 3, false);
            if(score > bestscore) {
                bestscore = score;
                bestmove = moves[i];
            }
        }
        printMove(bestmove);
    }
    cerr << "Count: " << GLOBAL_COUNT << endl;
}