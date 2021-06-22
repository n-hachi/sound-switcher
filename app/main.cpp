#include <getopt.h>

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>

#include "sound/lib.hpp"
#include "version.h"

std::string appname;

void Usage(void) {
    std::cout << "Usage: " << appname << " [OPTION] files" << std::endl;
}
void Version(void) {
    std::cout << appname << " " << PROJECT_VERSION << std::endl
              << "commit : " << COMMIT_HASH << std::endl;
}

int main(int argc, char* argv[]) {
    appname = argv[0];

    int opt;
    while ((opt = getopt(argc, argv, "hv")) != -1) {
        switch (opt) {
            case 'h':
                Usage();
                std::exit(EXIT_SUCCESS);
            case 'v':
                Version();
                std::exit(EXIT_SUCCESS);
            default: /* '?' */
                Usage();
                std::exit(EXIT_FAILURE);
        }
    }

    if (optind >= argc) {
        Usage();
        std::exit(EXIT_FAILURE);
    }

    // Store files to switcher
    SoundSwitcher switcher;
    for (int i = optind; i < argc; ++i) {
        std::string filename = argv[i];

        // Debug
        std::cout << "file : " << filename << std::endl;

        switcher.Insert(filename);
    }

    switcher.Start();
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    switcher.Stop();

    return 0;
}
