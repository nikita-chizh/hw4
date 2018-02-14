#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <arpa/inet.h>
#include <stdint.h>


template<typename T>
struct Print_ip {
    void operator()(const T &ip) {
    }
};


struct Int_Converter {
    size_t size;
    long value;

    Int_Converter() = delete;

    Int_Converter(char c) : value(c) {
        size = sizeof(c);
    }

    Int_Converter(short c) : value(c) {
        size = sizeof(c);
    }

    Int_Converter(int c) : value(c) {
        size = sizeof(c);
    }

    Int_Converter(long c) : value(c) {
        size = sizeof(c);
    }
};

template<>
struct Print_ip<Int_Converter> {
    void operator()(Int_Converter ip) {
        if (ip.size < 8)
            ip.value = htonl(ip.value);
        else
            ip.value = htobe64(ip.value);
        auto *pointer = (unsigned char *) &ip.value;
        auto last = ip.size - 1;
        for (int i = 0; i < ip.size; i++) {
            std::cout << (int) pointer[i];
            if (i != last) std::cout << '.';
        }
        std::cout << std::endl;
    }
};


template<>
struct Print_ip<std::string> {
    void operator()(const std::string &ip) {
        std::cout << ip << std::endl;
    }
};

template<typename T>
struct Print_ip<std::vector<T>> {
    void operator()(const std::vector<T> &ip) {
        auto last =  ip.end() - 1;
        for (auto iter = ip.cbegin(); iter != ip.end(); ++iter) {
            std::cout << *iter;
            if(iter != last) std::cout << '.';
        }
        std::cout<< std::endl;
    }
};

template<typename T>
struct Print_ip<std::list<T>> {
    void operator()(const std::list<T> &ip) {
        auto last = std::prev(ip.end());
        for (auto iter = ip.cbegin(); iter != ip.end(); ++iter) {
            std::cout << *iter;
            if(iter != last) std::cout << '.';
        }
        std::cout<< std::endl;
    }
};



Print_ip<Int_Converter> print_ip_int;
Print_ip<std::string> print_ip_str;
Print_ip<std::vector<int>> print_ip_vec;
Print_ip<std::list<int>> print_ip_list;



int main() {
//    255
//    0.0
//    127.0.0.1
//    123.45.67.89.101.112.131.41
    print_ip_int(char(-1));
    print_ip_int(short(0));
    print_ip_int(int(2130706433));
    print_ip_int(long(8875824491850138409));
    //
    print_ip_str("127.0.0.1");
    //
    print_ip_vec(std::vector<int>{255,255,255,255});
    //
    print_ip_list(std::list<int>{1,1,1,1});

    return 0;
}