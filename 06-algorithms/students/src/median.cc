#include <vector>
#include <stdexcept>
#include <algorithm>

using std::vector; using std::domain_error;

double median(vector<double> arr) {
    //Compute median score in vector
    typedef vector<double>::size_type v_size;

    v_size size = arr.size();
    if (size == 0) { //Edge case checking
        throw domain_error("Median of empty error");
    }

    sort(arr.begin(), arr.end()); //Inplace sort

    return (size % 2 == 0) ? (arr[size/2] + arr[(size-1)/2]) / 2 : arr[size/2];
}