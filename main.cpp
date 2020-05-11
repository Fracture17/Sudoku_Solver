#include "omp.h"

#include "BruteForce.h"
#include "BruteForceBasicChecks.h"
#include "Crooks.h"
#include "Problems.h"
#include <fstream>

using namespace std;


void timeSolver(Board (*solver)(Board& initialState), fstream& stream) {
    for (int i = 0; i < 50; ++i) {
        Board board(reinterpret_cast<short *>(hardBoards[i]));
        auto start = std::chrono::high_resolution_clock::now();

        board = solver(board);

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        stream << "Board " << i << " time: " << duration / 1000000.0 << " seconds" << endl;
    }
}

int main() {
    fstream crooksResults("crooksResults.txt", fstream::out);
    fstream basicResults("basicResults.txt", fstream::out);
    for(int threads = 1; threads <= 16; threads++) {
        omp_set_num_threads(threads);

        crooksResults << "Crooks, threads=" << threads << endl;
        timeSolver(solveCrooks, crooksResults);

        basicResults << "Brute Force with basic checks, threads=" << threads << endl;
        timeSolver(solveBruteForceWithBasicChecks, basicResults);

        //fstream bruteResults("bruteResults.txt", fstream::out);
        //bruteResults << "Brute Force, threads=" << threads << endl;
        //timeSolver(solveBruteForce, bruteResults);
    }

    return 0;
}
