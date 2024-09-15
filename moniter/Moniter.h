#pragma once
#include <mutex>
#include <thread>
#include <condition_variable>

// 템플릿 기반의 Monitor 클래스
// T: 보호할 공유 데이터의 타입
template <typename T>
class Monitor {

protected:
    mutable std::mutex mtx;        // 뮤텍스: 공유 데이터에 대한 접근을 동기화
    std::condition_variable cv;    // 조건 변수: 스레드 간 통신을 위해 사용
    T shared_data;                 // 보호되는 공유 데이터

public:
    // 생성자: 초기 데이터로 공유 데이터를 초기화
    Monitor(T initial_data) : shared_data(initial_data) {}

    // 동기화된 접근을 위한 템플릿 메서드
    // Func: 공유 데이터에 대해 수행할 작업을 정의하는 함수 객체
    template <typename Func>
    auto synchronizedAccess(Func func)  -> decltype(func(shared_data)) {
        std::lock_guard<std::mutex> lock(mtx);  // 뮤텍스 잠금
        std::cout << "lock을 취득한 스레드 id : " << std::this_thread::get_id()<< "\n";
        return func(shared_data);               // 함수 실행 및 결과 반환
    }

    // 조건 대기와 접근을 결합한 템플릿 메서드
    // Pred: 대기 조건을 정의하는 술어 함수
    // Func: 조건이 만족된 후 실행할 함수
    template <typename Pred, typename Func>
    auto waitAndAccess(Pred pred, Func func) -> decltype(func(shared_data)) {
        std::cout << "lock을 취득한 스레드 id : " << std::this_thread::get_id() << "\n";
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this, &pred] { return pred(shared_data); });  // 조건 대기
        return func(shared_data);  // 조건 만족 후 함수 실행 및 결과 반환
    }

    // 하나의 대기 중인 스레드에 알림
    void notify() {
        cv.notify_one();
    }

    // 모든 대기 중인 스레드에 알림
    void notifyAll() {
        cv.notify_all();
    }
};


