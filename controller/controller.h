#ifndef _CONTROL_H
#define _CONTROL_H
#include "../models/host.h"
#include "../models/arp.h"
#include "../models/scanner.h"

#include <set>
#include <map>
#include <vector>

class Controller
{
private:
    NetworkScanner scanner;
    std::set<Host> hosts;
    std::map<Host, ARP> arp;
    std::map<Host, std::string> fake_mac_address;
    int attack_interval_ms;
    void scan_targets();
    void attack(const Host &target);
    void recover(const Host &target);
    void recover_all_hosts();
    std::string get_fake_mac_address() const;
public:
    Controller(const int attack_interval_ms);
    void show_targets();
    std::vector<size_t> get_targets();
    void action(size_t index);
};

#endif