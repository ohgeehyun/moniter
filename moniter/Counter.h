#pragma once

#include "Moniter.h"

// Monitor 클래스 상속
//[](){}는 람다 함수입니다. 모니터에서는 매개변수로 함수그자체를 전달받고있기때문에 람다로 함수를 전달하고있습니다.
class Counter : public Monitor<int> {

	public:
		//생성자 : 초키 카운터 값을 생성
		Counter(int initial_cout) : Monitor<int>(initial_cout) {}

		//카운터 증가 메서드
		void increment() {
			std::cout << "increment function 진행중 " << '\n';
			synchronizedAccess([](int& data){
				++data;
				std::cout << "increment function 완료 현재 count의 상태 : " << data << '\n';
				return data;
				});
			notifyAll(); //컨디션 변수에 연결된 모든 스레드를 깨움
		}

		//카운터 감소 메서드
		void decrement() {
			std::cout << "decrement function 진행중 " << '\n';
			synchronizedAccess([](int& data) {
				--data;
				std::cout << "decrement function 완료 . 현재 count의 상태 : " << data << '\n';
				return data;
			});
			notifyAll(); //컨디션 변수에 연결된 모든 스레드를 깨움
		}

		//카운터가 특정 값에 도달할 떄까지 대기
		void waitForCount(int target_count) {
			std::cout << "waitForCount function 진행중 " << '\n';
			waitAndAccess([target_count](int& data) { //
				return data == target_count;
			}, [](int& data) {
				return data;
			});
		}

		//현재의 카운터 값을 반환
		int getCount()  {
			return synchronizedAccess([](int& data) {
				return data;
			});

		}

};