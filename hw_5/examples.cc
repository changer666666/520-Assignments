#include <exception>
#include "examples.h"

using namespace std;

bool mySort(double &o1, double &o2) {
    double t1 = o1;
    double t2 = o2;
    if (t1 < 0) t1 = -t1;
    if (t2 < 0) t2 = -t2;

    return t1 < t2;
}

void sort_by_magnitude(vector<double> &v) {
    std::sort(v.begin(), v.end(), mySort);

}

vector<int> primes(int n) {
    vector<bool> prime(n + 1);
    for(vector<bool>::iterator i=prime.begin(); i!=prime.end(); ++i) {
        *i = true;
    }

    for (int i = 2; i < n; i++) {
        int sum = i + i;
        while (sum <= n) {
            prime[sum] = false;
            sum += i;
        }
    }
    vector<int> res;
    for(int i = 2; i < n + 1; i++) {
        if (prime[i]) res.push_back(i);
    }
    return res;
}

vector<tuple<int,int>> twins(vector<int> nums) {
    vector<tuple<int, int>> res;
    for (int i = 0; i < nums.size(); i++) {
        int j = i + 1;
        while (nums[i] + 2 >= nums[j]) {
            if (nums[i] + 2 == nums[j]) {
                tuple<int, int> t = make_tuple(nums[i], nums[j]);
                res.push_back(t);
                break;
            }
            j++;
        }
    }
    return res;
}

