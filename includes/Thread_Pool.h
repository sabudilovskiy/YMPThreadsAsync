//
// Created by MRV on 4/30/2022.
//

#ifndef YMPTHREADS_THREAD_POOL_H
#define YMPTHREADS_THREAD_POOL_H
#include <thread>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <set>
#include <future>
long long have_3_uniq_dividers(long long number){
    std::set<long long> dividers;
    long long old_number = number;
    int i = 2;
    double sq = sqrt(number);
    while (i < sq && dividers.size() < 4){
        while (number % i == 0) {
            number/= i;
            sq /= sqrt(i);
            auto old_dividers = dividers;
            for (auto it = old_dividers.begin(), end = old_dividers.end(); it!=end; ++it){
                dividers.insert(*it*i);
            }
            dividers.insert(i);
        }
        i++;
    }
    if (i < number && dividers.size() < 4){
        auto old_dividers = dividers;
        for (auto it = old_dividers.begin(), end = old_dividers.end(); it!=end; ++it){
            dividers.insert(*it*number);
        }
        dividers.insert(number);
    }
    dividers.erase(old_number);
    long long answer = 1;
    if (dividers.size() == 3) answer = *std::next(dividers.begin(), 2);
    return answer;
}
std::vector<std::pair<long long, long long>> find_all_numbers(long long begin, long long end){
    std::vector<std::pair<long long, long long>> answer;
    for (long long i = begin; i < end; i++){
        if (long long temp = have_3_uniq_dividers(i); temp != 1){
            answer.emplace_back(i, temp);
        }
    }
    return answer;
}

class Thread_Pool{
protected:
    short n;
    long long all_begin, all_end;
    std::vector<long long> begin_section;
    std::vector<long long> end_section;
    std::vector<std::future<std::vector<std::pair<long long, long long>>>> answers;
    std::vector<std::pair<long long, long long>> find_all_numbers(int number_thread){
        long long begin = begin_section[number_thread];
        long long end = end_section[number_thread];
        return ::find_all_numbers(begin, end);
    }
public:
    Thread_Pool(const long long& begin, const long long& end, short n = std::thread::hardware_concurrency() - 1): all_begin(begin), all_end(end), n(n){
        answers.reserve(n);
        begin_section.resize(n);
        end_section.resize(n);
        long long one_thread = (end - begin)/n;
        begin_section[0] = begin;
        end_section[0] = begin + one_thread;
        for (int i = 1; i < n; i++){
            begin_section[i] = begin_section[i - 1] + one_thread;
            end_section[i] = end_section[i - 1] + one_thread;
        }
        end_section[n - 1] = end;
        for (int i = 0; i < n; i++){
            answers.emplace_back(std::async(std::launch::async, &Thread_Pool::find_all_numbers, this, i));
        }
    }
    std::vector<std::vector<std::pair<long long , long long>>> get_answers() {
        std::vector<std::vector<std::pair<long long, long long>>> real_answers;
        real_answers.reserve(n);
        for (int i = 0; i < n; i++){
            real_answers.emplace_back(answers[i].get());
        }
        return real_answers;
    }
    std::vector<std::pair<long long, long long>> get_answer(int i){
        if (0<=i && i < n){
            return answers[i].get();
        }
        else throw std::invalid_argument("");
    }
};
#endif //YMPTHREADS_THREAD_POOL_H
