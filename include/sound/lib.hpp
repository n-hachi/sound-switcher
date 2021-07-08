#ifndef SAMPLE_CLIENT_INCLUDE_SOUND_LIB_HPP
#define SAMPLE_CLIENT_INCLUDE_SOUND_LIB_HPP

#include <sys/types.h>

#include <map>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

class SoundSwitcher {
   public:
    void Start(const int num);
    void Stop();
    void Insert(const std::string &path);
    void set_options(const std::vector<std::string> &options);
    size_t Size() const;
    std::map<int, std::string> map();

   private:
    // Need to be not public
    pid_t pid_ = -1;
    std::map<int, std::string> map_;
    std::vector<std::string> options_;

    // Thread related method and variables to wait for child process.
    void ThreadFunc();
    std::thread th_;
    bool is_running_ = false;
};

#endif
