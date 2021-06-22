#ifndef SAMPLE_CLIENT_INCLUDE_SOUND_LIB_HPP
#define SAMPLE_CLIENT_INCLUDE_SOUND_LIB_HPP

#include <sys/types.h>

#include <map>
#include <mutex>
#include <string>
#include <thread>

class SoundSwitcher {
   public:
    void Start();
    void Stop();
    void Insert(const std::string &path);
    size_t Size() const;

   private:
    // Need to be not public
    pid_t pid_ = -1;
    std::map<int, std::string> map_;
    void ThreadFunc();
};

#endif
