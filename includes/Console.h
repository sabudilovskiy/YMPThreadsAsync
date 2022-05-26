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
//                int i = input(verifer_index, converter , "������� ����� ������: ", "�������� ������ ��� �����, ��������� ����: ");
//                try{
//                    std::cout << tp.get_info_about_thread(i) << '\n';
//                }
//                catch(...){
//                    std::cout << "������������ �����\n";
//                }
//            }
//                break;
            case ANSWER_ALL:{
                auto answers = tp.get_answers();
                if (!answers.empty()){
                    for (int i = 0; i < answers.size(); i++){
                        std::cout << "��������� " << i << " �������: ";
                        for (auto & it : answers[i]){
                            std::cout << it.first << " ���������� ���������: " << it.second << '\n';
                        }
                        std::cout << '\n';
                    }
                }
                else std::cout << "���� �� ������� �� ������ ����������� �����\n";
                auto time = tp.get_work_time();
                std::cout << "������������� ";
                if (time > 60){
                    std::cout << time/60 << " ����� ";
                    time %= 60;
                }
                std::cout << time << " ������\n";
            }
                break;
            case ANSWER_THREAD:{
                int i = input(verifer_index, converter , "������� ����� ������: ", "�������� ������ ��� �����, ��������� ����: ");
                try{
                    auto answer = tp.get_answer(i);
                    if (!answer.empty()){
                        for (auto & it : answer){
                            std::cout << it.first << " ���������� ���������: " << it.second << '\n';
                        }
                    }
                    else std::cout << "����� ���� �� ����� �� ������ ����������� �����\n";
                }
                catch(...) {
                    std::cout << "������ ��� �����\n";
                }
            }
            break;
        }
    }
public:
    Console(Thread_Pool &thread_pool) : tp(thread_pool), command(ANSWER_THREAD) {}
    void start(){
        while (command != EXIT){
            static const std::string message = "������� �������:\n0)�����\n1)������� ���������� � ���� �������\n2)������� ���������� �� ����� ������\n3)������� ��������� �����\n4)������� �����, ��������� ���������� �������\n";
            static const std::string error = "�������� ������ � ������ �������, ��������� ����: ";
            command = (COMMANDS)input<int>(verifer_command, converter, message, error);
            execute_command();
        }
    }
};
#endif //YMPTHREADS_CONSOLE_H
