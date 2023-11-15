/**
 * @file main.cc
 * @brief Main file for HW4
 * @author Pete Newman
 * @date 11/02/2023
 */

#include <iostream>
#include <string>
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
 * @brief function to calculate the minimum number of coins to make change for x
 *
 * @param x is the amount of change to make
 * @param coins is the vector of coin denominations
 * @return int
 */
long long int calcCoinChange(int x, vector<int> &coins);

/**
 * @brief Main function for HW4
 */
int main()
{
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

    int n = 64;
    auto start = chrono::high_resolution_clock::now();
    cout << "Max revenue for rod of length " << n << " is " << memoizedCutRod(p, n) << endl;
    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = stop - start;
    cout << "Time taken by rod cutting function: " << elapsed.count() << " seconds" << endl
         << endl;

    // this section tests the coin change problem
    vector<int> coins = {1, 5, 10, 25, 50, 100, 200, 500, 1000, 2000};
    int x = 5000;
    auto start2 = chrono::high_resolution_clock::now();
    cout << "Number of ways to make change for " << x << " cents is " << calcCoinChange(x, coins) << endl;
    auto stop2 = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed2 = stop2 - start2;
    cout << "Time taken by coin change function: " << elapsed2.count() << " seconds" << endl
         << endl;
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