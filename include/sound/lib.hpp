#ifndef SAMPLE_CLIENT_INCLUDE_SOUND_LIB_HPP
#define SAMPLE_CLIENT_INCLUDE_SOUND_LIB_HPP

#include <sys/types.h>

#include <mutex>
#include <thread>

class SoundSwitcher {
   public:
    SoundSwitcher();
    void Start();
    void Stop();

   private:
    // Need to be not public
    pid_t pid_ = -1;
    bool is_running_ = false;
    std::thread th_;
};

#endif
