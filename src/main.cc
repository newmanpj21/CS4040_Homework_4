/**
 * @file main.cc
 * @brief Main file for HW4
 * @author Pete Newman
 * @date 11/02/2023
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;

// function prototypes

/**
 * @brief function to calculate the max revenue for a rod of length n
 *
 * @param p is the array of prices
 * @param n is the length of the rod
 * @return int
 */
int memoizedCutRod(vector<int> p, int n);

/**
 * @brief helper function for memoizedCutRod
 *
 * @param p is the array of prices
 * @param n is the length of the rod
 * @param r is the array of memoized values
 * @return int
 */
int memoizedCutRodAux(vector<int> p, int n, vector<int> &r);

/**
 * @brief This struct is used internally to store a combination of coins
 *
 */
struct Combination
{
    vector<int> coins;
};

/**
 * @brief function to calculate the number of ways to make change for x cents
 *
 * @param x is the amount of change to make
 * @param coins is the vector of coin denominations
 * @return vector<Combination>
 */
vector<Combination> calcCoinCombinations(int x, vector<int> &coins);

/**
 * @brief function to calculate the number of ways to make change for x cents
 *
 * @param x is the amount of change to make
 * @param coins is the vector of coin denominations
 * @return long long int
 */
long long int calcCoinChange(int x, vector<int> &coins);

/**
 * @brief Main function for HW4. This function executes the test experiments
 */
int main()
{
    // this section checks for a file named "combinations.txt". If it is found, it is deleted
    // this is to ensure that the file is empty before the program starts
    if (remove("combinations.txt") != 0)
    {
        perror("Combinations file not present (this is normal)");
    }
    else
    {
        puts("Combinations file successfully deleted (this is normal)");
    }

    // opens the file
    ofstream combinationsFile;
    combinationsFile.open("combinations.txt", ios::app);

    // test experiments

    // this vector, p, stores the price information. the index of the vector is the length of the rod
    // and the value at that index is the price of the rod of that length
    vector<int> p(17, -1);
    p[1] = 1;
    p[2] = 5;
    p[4] = 9;
    p[6] = 17;
    p[8] = 20;
    p[10] = 30;
    p[12] = 36;
    p[16] = 48;

    cout << endl
         << "Testing rod cutting problem" << endl
         << endl;

    // // time the rod cutting function for the inputs : 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096
    int n[11] = {4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096};
    int ans = 0;
    for (int i = 0; i < 11; i++)
    {
        // time the rod cutting function
        auto start = chrono::high_resolution_clock::now();
        ans = memoizedCutRod(p, n[i]);
        auto stop = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = stop - start;
        cout << "Max revenue for rod of length " << n[i] << " is " << ans << ". Time taken by rod cutting function: "
             << elapsed.count() << " seconds" << endl;
    }

    // this section tests the coin change problem
    cout << endl
         << "Testing coin change problem with the Harry Potter currency" << endl
         << endl;
    vector<int> harryPotterCurrency = {1, 29, 493};
    int x[9] = {10, 50, 100, 500, 1000, 1500, 2000, 3000, 5000};

    long long int answer = 0;
    for (int i = 0; i < 9; i++)
    {
        // time the coin change function
        auto start = chrono::high_resolution_clock::now();
        answer = calcCoinChange(x[i], harryPotterCurrency);
        auto stop = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = stop - start;
        cout << "Number of ways to make change for " << x[i] << " cents is " << answer << ". Time taken by coin change function: "
             << elapsed.count() << " seconds" << endl;
    }

    cout << endl
         << "Testing coin change problem with the US currency" << endl
         << endl;
    vector<int> usCurrency = {1, 5, 10, 25, 50, 100, 200, 500, 1000, 2000};
    for (int i = 0; i < 9; i++)
    {
        // time the coin change function
        auto start = chrono::high_resolution_clock::now();
        answer = calcCoinChange(x[i], usCurrency);
        auto stop = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = stop - start;
        cout << "Number of ways to make change for " << x[i] << " cents is " << answer << ". Time taken by coin change function: "
             << elapsed.count() << " seconds" << endl;
    }

    cout << endl
         << "Testing adapted coin change problem with the US currency" << endl
         << endl;
    int adaptedInputs[4] = {10, 25, 50, 100};
    combinationsFile << "Testing adapted coin change problem with the US currency" << endl
                     << endl;
    for (int i = 0; i < 4; i++)
    {
        // time the adapted coin change function
        auto start = chrono::high_resolution_clock::now();
        vector<Combination> combinations = calcCoinCombinations(adaptedInputs[i], usCurrency);
        auto stop = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = stop - start;
        cout << "Time taken by adapted coin change function to calculate " << adaptedInputs[i] << " cents: " << elapsed.count() << " seconds" << endl;

        // write the combinations to the file
        combinationsFile << "Number of ways to make change for " << adaptedInputs[i] << " cents is " << endl;
        for (Combination combination : combinations)
        {
            for (int coin : combination.coins)
            {
                combinationsFile << coin << " ";
            }
            combinationsFile << endl;
        }
    }

    cout << endl
         << "Testing adapted coin change problem with the Harry Potter currency" << endl
         << endl;
    combinationsFile << endl
                     << "Testing adapted coin change problem with the Harry Potter currency" << endl
                     << endl;
    for (int i = 0; i < 4; i++)
    {
        // time the adapted coin change function
        auto start = chrono::high_resolution_clock::now();
        vector<Combination> combinations = calcCoinCombinations(adaptedInputs[i], harryPotterCurrency);
        auto stop = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = stop - start;
        cout << "Time taken by adapted coin change function to calculate " << adaptedInputs[i] << " cents: " << elapsed.count() << " seconds" << endl;

        // write the combinations to the file
        combinationsFile << "Number of ways to make change for " << adaptedInputs[i] << " cents is " << endl;
        for (Combination combination : combinations)
        {
            for (int coin : combination.coins)
            {
                combinationsFile << coin << " ";
            }
            combinationsFile << endl;
        }
    }

    cout << endl
         << "NOTICE: I have included the output of the adapted coin change problem in the file 'combinations.txt'. It is located in the root directory of the project." << endl
         << "This is because the output is too large to be printed to the console." << endl;

    // close the file
    combinationsFile.close();
    return 0;
}

// function implementations

int memoizedCutRod(vector<int> p, int n)
{
    // create a vector to store the memoized values
    vector<int> r(n + 1, -1);
    // call the helper function
    return memoizedCutRodAux(p, n, r);
}

int memoizedCutRodAux(vector<int> p, int n, vector<int> &r)
{
    // if the value is already memoized, return it
    if (r[n] >= 0)
    {
        return r[n];
    }
    // if the length of the rod is 0, return 0
    else if (n == 0)
    {
        return 0;
    }
    // otherwise, calculate the max revenue
    else
    {
        int q = -1;
        for (int i = min(n, (int)p.size() - 1); i >= 1; i--)
        {
            // if the price is -1, skip it. this is to account for the fact that the price vector
            // is not necessarily the same length as the rod
            if (p[i] == -1)
            {
                continue;
            }
            // otherwise, calculate the max revenue
            if (n - i >= 0)
            {
                q = max(q, p[i] + memoizedCutRodAux(p, n - i, r));
            }
        }
        r[n] = q;
        return q;
    }
}

vector<Combination> calcCoinCombinations(int x, vector<int> &coins)
{
    // create a vector to store the number of ways to make change for each value
    vector<vector<Combination>> combinations(x + 1);
    Combination initial;
    initial.coins = {};
    combinations[0].push_back(initial);

    // iterate through the coins
    for (long unsigned int i = 0; i < coins.size(); i++)
    {
        // iterate through the values
        int coinValue = coins[i];
        for (int j = coinValue; j <= x; j++)
        {
            for (Combination &combination : combinations[j - coinValue])
            {
                Combination newCombination = combination;
                newCombination.coins.push_back(coinValue);
                combinations[j].push_back(newCombination);
            }
        }
    }
    return combinations[x];
}

long long int calcCoinChange(int x, vector<int> &coins)
{
    // create a vector to store the number of ways to make change for each value
    vector<long long int> ways(x + 1, 0);
    ways[0] = 1;
    // iterate through the coins
    for (long unsigned int i = 0; i < coins.size(); i++)
    {
        // iterate through the values
        int coinValue = coins[i];
        for (int j = coinValue; j <= x; j++)
        {
            // add the number of ways to make change for the value - the coin value to the number of ways to make change for the value
            ways[j] = ways[j - coinValue] + ways[j];
        }
    }
    return ways[x];
}