#pragma once

#include "Moniter.h"

// Monitor Ŭ���� ���
//[](){}�� ���� �Լ��Դϴ�. ����Ϳ����� �Ű������� �Լ�����ü�� ���޹ް��ֱ⶧���� ���ٷ� �Լ��� �����ϰ��ֽ��ϴ�.
class Counter : public Monitor<int> {

	public:
		//������ : ��Ű ī���� ���� ����
		Counter(int initial_cout) : Monitor<int>(initial_cout) {}

		//ī���� ���� �޼���
		void increment() {
			std::cout << "increment function ������ " << '\n';
			synchronizedAccess([](int& data){
				++data;
				std::cout << "increment function �Ϸ� ���� count�� ���� : " << data << '\n';
				return data;
				});
			notifyAll(); //����� ������ ����� ��� �����带 ����
		}

		//ī���� ���� �޼���
		void decrement() {
			std::cout << "decrement function ������ " << '\n';
			synchronizedAccess([](int& data) {
				--data;
				std::cout << "decrement function �Ϸ� . ���� count�� ���� : " << data << '\n';
				return data;
			});
			notifyAll(); //����� ������ ����� ��� �����带 ����
		}

		//ī���Ͱ� Ư�� ���� ������ ������ ���
		void waitForCount(int target_count) {
			std::cout << "waitForCount function ������ " << '\n';
			waitAndAccess([target_count](int& data) { //
				return data == target_count;
			}, [](int& data) {
				return data;
			});
		}

		//������ ī���� ���� ��ȯ
		int getCount()  {
			return synchronizedAccess([](int& data) {
				return data;
			});

		}

};