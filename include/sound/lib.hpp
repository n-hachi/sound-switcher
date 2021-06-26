#ifndef SAMPLE_CLIENT_INCLUDE_SOUND_LIB_HPP
#define SAMPLE_CLIENT_INCLUDE_SOUND_LIB_HPP

#include <sys/types.h>

#include <map>
#include <mutex>
#include <string>
#include <thread>

class SoundSwitcher {
   public:
    void Start(const int num);
    void Stop();
    void Insert(const std::string &path);
    size_t Size() const;

   private:
    // Need to be not public
    pid_t pid_ = -1;
    std::map<int, std::string> map_;

    // Thread related method and variables to wait for child process.
    void ThreadFunc();
    std::thread th_;
    bool is_running_ = false;
};

#endif
