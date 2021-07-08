#include "sound/lib.hpp"

#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>
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

    waitpid(pid_, NULL, 0);
}

void SoundSwitcher::set_options(const std::vector<std::string> &options) {
    options_.resize(options.size());
    std::copy(options.begin(), options.end(), options_.begin());
}

void SoundSwitcher::Start(const int num) {
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
        int fd = open("/dev/null", O_WRONLY | O_CREAT, 0666);
        dup2(fd, 1);
        dup2(fd, 2);

        std::vector<char *> command_vec;
        command_vec.push_back(const_cast<char *>("/usr/bin/aplay"));
        command_vec.push_back(const_cast<char *>(map_.at(num).c_str()));

        // finally append null
        command_vec.push_back(NULL);

        // call execvp function
        char **command = command_vec.data();
        execvp(command[0], &command[0]);
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

std::map<int, std::string> SoundSwitcher::map() { return map_; }
