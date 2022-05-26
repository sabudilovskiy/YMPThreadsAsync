//
// Created by MRV on 4/30/2022.
//

#ifndef YMPTHREADS_CONSOLE_H
#define YMPTHREADS_CONSOLE_H
#include "Thread_Pool.h"
#include "Support.h"
#include <string>
#include "Timer.h"
class Console{
protected:
    Thread_Pool& tp;
    enum COMMANDS{
        EXIT,
//        INFO_ALL,
//        INFO_THREAD,
        ANSWER_ALL = 3,
        ANSWER_THREAD = 4
    } command;
    const inline static std::function<bool(const int&)> verifer_index = [](const int& a){return a >= 0;};
    const inline static std::function<int(std::string&&)> converter = [](std::string&& str){return std::stoi(str);};
    const inline static std::function<bool(const int&)> verifer_command = [](const int&a){return ANSWER_THREAD >= a && a>=(int)COMMANDS::EXIT;};
    void execute_command(){
        switch (command) {
//            case INFO_ALL:
//            {
//                std::cout << tp.get_info_about_threads();
//            }
//                break;
//            case INFO_THREAD:
//            {
//                int i = input(verifer_index, converter , "Введите номер потока: ", "Допущена ошибка при вводе, повторите ввод: ");
//                try{
//                    std::cout << tp.get_info_about_thread(i) << '\n';
//                }
//                catch(...){
//                    std::cout << "Некорректный номер\n";
//                }
//            }
//                break;
            case ANSWER_ALL:{
                auto answers = tp.get_answers();
                if (!answers.empty()){
                    for (int i = 0; i < answers.size(); i++){
                        std::cout << "Найденное " << i << " потоком: ";
                        for (auto & it : answers[i]){
                            std::cout << it.first << " наибольший множитель: " << it.second << '\n';
                        }
                        std::cout << '\n';
                    }
                }
                else std::cout << "Пока не найдено ни одного подходящего числа\n";
                auto time = tp.get_work_time();
                std::cout << "Потребовалось ";
                if (time > 60){
                    std::cout << time/60 << " минут ";
                    time %= 60;
                }
                std::cout << time << " секунд\n";
            }
                break;
            case ANSWER_THREAD:{
                int i = input(verifer_index, converter , "Введите номер потока: ", "Допущена ошибка при вводе, повторите ввод: ");
                try{
                    auto answer = tp.get_answer(i);
                    if (!answer.empty()){
                        for (auto & it : answer){
                            std::cout << it.first << " наибольший множитель: " << it.second << '\n';
                        }
                    }
                    else std::cout << "Поток пока не нашёл ни одного подходящего числа\n";
                }
                catch(...) {
                    std::cout << "Ошибка при вводе\n";
                }
            }
            break;
        }
    }
public:
    Console(Thread_Pool &thread_pool) : tp(thread_pool), command(ANSWER_THREAD) {}
    void start(){
        while (command != EXIT){
            static const std::string message = "Введите команду:\n0)выйти\n1)вывести информацию о всех потоках\n2)вывести информацию об одном потоке\n3)вывести найденные числа\n4)вывести числа, найденные конкретным потоком\n";
            static const std::string error = "Допущена ошибка в номере команды, повторите ввод: ";
            command = (COMMANDS)input<int>(verifer_command, converter, message, error);
            execute_command();
        }
    }
};
#endif //YMPTHREADS_CONSOLE_H
