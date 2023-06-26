#ifndef _THREAD_H
#define _THREAD_H

#include <atomic>
#include <map>
#include <string>
#include <thread>

namespace Thread 
{
    extern std::map<std::string, std::map<std::string, std::atomic<bool>>> spoof_signal;
    extern std::map<std::string, std::map<std::string, std::thread>> spoof_thread;
    extern std::map<std::string, std::atomic<bool>> listen_signal;
    extern std::map<std::string, std::thread> listening_thread;
    bool stop_thread(const std::string &target_ip, const std::string &spoof_src_ip);
    bool stop_thread(const std::string &ip);
    void stop_all_threads();
}

#endif