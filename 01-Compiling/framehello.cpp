#include <iostream>
#include <string>

void print_table(std::string msg, int pad_v = 1, int pad_h = 2) {

    //const int NUM_PAD_V = 2; //Number of padding rows above/below name
    //const int NUM_PAD_H = 5; //Numbe of padding space left/right of name
    const std::string::size_type num_cols = msg.size() + pad_h * 2;
    const std::string space(num_cols, ' ');
    const std::string stars(num_cols + 2, '*');
    const std::string padding(pad_h, ' ');

    const int num_rows = 2 * (pad_h + 1) + 1;
    for (int i = 0; i < num_rows; i++) {
        if (i == 0 || i == num_rows - 1) {
            std::cout << stars << std::endl;
        } else if (i == (num_rows / 2)) {
            std::cout << "*" + padding + msg + padding + "*" << std::endl;
        } else {
            std::cout << "*" + space + "*" << std::endl;
        }
    }
}
int main() {
    std::string myname;
    std::cout << "Enter name: ";
    std::cin >> myname;

    const std::string msg = "Hello, " + myname;
    print_table(msg);
    
    return 0;
}