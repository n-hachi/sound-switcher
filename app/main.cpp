#include <getopt.h>

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

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
        switcher.Insert(filename);
    }

    while (true) {
        // Print prompt
        std::cout << "> ";
        std::string line;
        std::getline(std::cin, line);

        std::istringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;
        while (ss >> token) {
            tokens.push_back(token);
        }

        if (tokens[0] == "start") {
            if (tokens.size() < 2) {
                std::cout << "input 'start <number>' , 'stop' or 'quit'"
                          << std::endl;
                continue;
            }
            int num = std::stoi(tokens[1]);
            // Just for debug
            std::cout << "command = 'start' , val = " << num << std::endl;
            switcher.Start();
        } else if (tokens[0] == "stop") {
            std::cout << "command = 'stop'" << std::endl;
            switcher.Stop();
        } else if (tokens[0] == "quit") {
            break;
        } else {
            std::cout << "input 'start <number>' , 'stop' or 'quit'"
                      << std::endl;
        }
    }

    switcher.Stop();

    return 0;
}
