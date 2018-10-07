#include <iostream>
#include <vector>
#include <string>
#include "frame.h"

int test_frame() {
    std::vector<std::string> v = {"Hello", "World"};

    std::vector<std::string> ret = frame(v);
    print_vec_str(v);
    return 0;
}

int test_vcat() {
    std::vector<std::string> v = {"Hello", "Wooorld"};
    auto ret = vcat(v, frame(v));
    print_vec_str(ret);
    return 0;
}

int test_hcat() {
    auto ret = hcat({"Hello", "World"}, frame({"Oooh", "La", "La la la"}));
    print_vec_str(ret);
    return 0;
}

int test_center(bool use_frame=false) {
    std::vector<std::string> ret = {"Oooh", "La", "La la la"};
    print_vec_str(center(ret, use_frame));
    return 0;
}

int main() {
    test_frame();
    test_vcat();
    test_hcat();
    test_center();
    test_center(true);
    return 0;
}