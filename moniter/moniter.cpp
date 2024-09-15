// moniter.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
/*
    이런 c++에선 따로 moniter가 없어서 사용하고싶으면 mutex와 condition variable을 이용하여 따로 만들어야한다!
    자바는 모든 객체가 생성될떄 자동으로들어간다고한다. 언어마다 다르니 사용할 언어마다 참고해야할듯 하다.
    
    프로젝트설명
    Moniter.h <- 모니터 클래스를 정의 해놓은 헤더 파일
    Counter.h <- 카운터 클래스를 정의 해놓은 헤더 파일

    스레드 3개를 실행시켜 증감과 차감을 하며 카운터값에 먼저 도달 하게 모니터로 임계구역에 동시에 진입은 막아놓은 프로그램

    느낌점이 크게 있는데 c++의 모토가 유연성과 자유로움이라 모니터 자체를 딱히 언어영역에서 지원을 하지않기 때문에 실제로 사용하고싶으면 
    구현을해서 사용해야 할 영역에 목적에 맞게 개발을 해야해서 잘쓰면 더 좋게 흘러갈수도있지만 내 실력으로 과연 될까 싶기도하다. 결국 노ㅗㅗㅗ력이 더 해야한다는게 느껴진다. 
*/

#include <iostream>
#include <thread>
#include <functional>
#include <vector>
#include "Counter.h"

void incrementTask(Counter& counter, int increments) { //증가 함수
    for (int i = 0; i < increments; ++i) {
        std::cout << "thread1 실행중" << "\n";
        counter.increment();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void decrementTask(Counter& counter, int decrements) {//감소 함수
    for (int i = 0; i < decrements; ++i) {
        std::cout << "thread2 실행중" << "\n";
        counter.decrement();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void waitTask(Counter& counter, int target) { // 카운터의 값이 목표값에 도달할떄까지 기다렸다 목표값에 도달시 가르처주는함수.

    std::cout << "thread3 실행중" << "\n";
    std::cout << "Waiting for counter to reach " << target << ".....\n";
    counter.waitForCount(target);
    std::cout << "Counter reached " << target << "!\n";
}

;
int main()
{
    Counter counter(0);

    //스레드 하나로 전부 실행하여 테스트 한부분은 주석처리 하였습니다.
    /*std::vector<std::thread> threads;
    threads.push_back(std::thread(incrementTask, std::ref(counter), 10));
    threads.push_back(std::thread(decrementTask, std::ref(counter), 5));
    threads.push_back(std::thread(waitTask, std::ref(counter), 5));*/
    std::thread t1(incrementTask, std::ref(counter), 100);
    std::thread t2(decrementTask, std::ref(counter), 5);
    std::thread t3(waitTask, std::ref(counter), 5);
    // 스레드 종료 대기
   /* for (auto& t : threads) {
        t.join();
    }*/

    t1.join();
    t2.join();
    t3.join();
    std::cout << "Final counter value: " << counter.getCount() << "\n";

    system("pause");


    return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
