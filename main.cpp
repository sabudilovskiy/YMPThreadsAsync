#include <iostream>
#include "Thread_Pool.h"
#include <Windows.h>
#include "Console.h"
#include "Timer.h"
// 294400000 300000000
// 289123456 389123456
// �����:
/*
294499921 2248091

352275361 2571353

373301041 2685619
 */
//525784203 728943762
int main() {
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    long long begin = 2;
    long long end = 2;
    std::function<bool(const long long& x)> verifer_begin = [](const long long& x){
        return x > 1;
    };
    std::function<bool(const long long& x)> verifer_end = [begin](const long long& x){
        return x > begin;
    };
    std::function<long long(std::string&&)> converter = [](std::string&& str){return stoll(str);};
    begin = input(verifer_begin, converter, "������� ������ ���������: ", "�������� ������, ��������� ����: ");
    end = input(verifer_end, converter, "������� ����� ���������: ", "����� ��������� ������ ���� ������ ������: ");
//    Timer timer;
//    auto answer = find_all_numbers(begin, end);
//    timer.mark();
//    auto time = timer.get_points()[0];
//    std::cout << "������������� ";
//    if (time > 60){
//        std::cout << time/60 << " ����� ";
//        time %= 60;
//    }
//    std::cout << time << " ������\n";
//    if (!answer.empty()){
//        for (auto & it : answer){
//            std::cout << it.first << " ���������� ���������: " << it.second << '\n';
//        }
//    }
//    else std::cout << "��������� �� ����� �� ������ ����������� �����\n";
//    timer.reset();
    Thread_Pool tp(begin, end);
    Console console(tp);
    console.start();
}
