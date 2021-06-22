#include "sound/lib.hpp"

#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>
#include <thread>
#include <vector>

void SoundSwitcher::Stop() {
    // If pid_ is less equal than 0, there is no child process.
    if (pid_ <= 0) {
        return;
    }

    // If pid is more than 0, stop child process.
    kill(pid_, SIGTERM);

    // If thread is joinable
    if (is_running_ && th_.joinable()) {
        th_.join();
    }

    // Set false value to is_running
    is_running_ = false;
}

void SoundSwitcher::ThreadFunc() {
    // Setup flag
    is_running_ = true;

    // Just for Debug
    // std::cout << "Path this point, pid_ = " << pid_ << std::endl;
    std::cout << "Path this point" << std::endl;

    waitpid(pid_, NULL, 0);

    // Print
    std::cout << "Child process exited." << std::endl;
}

void SoundSwitcher::Start() {
    // If child process has already executed, stop it at first.
    Stop();

    pid_ = vfork();
    if (pid_ == -1) {
        std::cerr << "Error: vfork" << std::endl;
        return;
    }
    if (pid_ == 0) {
        if (Size() <= 0) {
            return;
        }

        const char **argv = new const char *[3];
        argv[0] = "/usr/bin/aplay";
        argv[1] = map_.at(0).c_str();
        argv[2] = NULL;

        const char *cmd = argv[0];
        execvp(cmd, (char **)argv);
    }
    if (pid_ > 0) {
        // Wait for child process exit.
        std::thread th(&SoundSwitcher::ThreadFunc, this);
        th_ = std::move(th);
    }
}

void SoundSwitcher::Insert(const std::string &path) {
    int size = (int)map_.size();
    map_.insert(std::pair<int, std::string>(size, path));
}

size_t SoundSwitcher::Size() const { return map_.size(); }
