//
// Created by MRV on 4/30/2022.
//

#ifndef YMPTHREADS_SUPPORT_H
#define YMPTHREADS_SUPPORT_H
#include <functional>
//verifer,converter, input, _error
template<class T>
T input(std::function<bool(const T&)> verifer, std::function<T(std::string&&)> converter, const std::string& input, const std::string& _error) {
    std::string temp;
    std::cout << input;
    std::cin >> temp;
    try {
        T answer = converter(std::move(temp));
        if (verifer(answer)) return answer;
        throw std::invalid_argument("");
    }
    catch (std::invalid_argument&) {
        while (true) {
            std::cout << _error;
            std::cin >> temp;
            try {
                T answer = converter(std::move(temp));
                if (verifer(answer)) return answer;
            }
            catch (std::invalid_argument&) {
            }
        }
    }
}
#endif //YMPTHREADS_SUPPORT_H
