#include "sound/lib.hpp"

#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>

void SoundSwitcher::Stop() {
    // If pid_ is less equal than 0, there is no child process.
    if (pid_ <= 0) {
        return;
    }

    // If pid is more than 0, stop child process.
    kill(pid_, SIGTERM);
    waitpid(pid_, NULL, 0);
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
        char *const args[] = {
            "/usr/bin/aplay",
            "/home/n_hachi/src/github.com/n-hachi/sound-switcher/sounds/"
            "mixkit-retro-game-emergency-alarm-1000.wav",
            ""};
        execvp(args[0], args);
    }
    if (pid_ > 0) {
        waitpid(pid_, NULL, 0);
    }
}
