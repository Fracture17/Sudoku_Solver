#include "omp.h"

#include "BruteForce.h"
#include "BruteForceBasicChecks.h"
#include "Crooks.h"
#include "Problems.h"

using namespace std;


void timeSolver(Board (*solver)(Board& initialState)) {
    for (int i = 0; i < 50; ++i) {
        Board board(reinterpret_cast<short *>(hardBoards[i]));
        board.display();
        auto start = std::chrono::high_resolution_clock::now();

        board = solver(board);

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        cout << "Board " << i << " time: " << duration / 1000000.0 << " seconds" << endl;
        board.display();
    }
}

int main() {
    int threads = 6;
    omp_set_num_threads(threads);

    cout << "Crooks, threads=" << threads << endl;
    timeSolver(solveCrooks);
    cout << "Brute Force with basic checks, threads=" << threads << endl;
    timeSolver(solveBruteForceWithBasicChecks);
    cout << "Brute Force, threads=" << threads << endl;
    timeSolver(solveBruteForce);

    return 0;
}
