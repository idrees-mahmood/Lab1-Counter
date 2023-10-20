#include <iostream>

int main () {

    bool count_pause = false;

    for (int i = 0; i < 15; i++) {
        std::cout << "i = " << i << std::endl;
        std::cout << "count_pause = " << count_pause << std::endl;
        count_pause = (i >= 9) && (i <= 12);
    }
}