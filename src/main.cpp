#include "helper/flags/flags.hpp"

int main(int argc, char** argv) {
    flags(argc, argv);
    run_file("./test.nl");
    return 0;
}