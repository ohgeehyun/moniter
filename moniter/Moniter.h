#pragma once
#include <mutex>
#include <thread>
#include <condition_variable>

// ���ø� ����� Monitor Ŭ����
// T: ��ȣ�� ���� �������� Ÿ��
template <typename T>
class Monitor {

protected:
    mutable std::mutex mtx;        // ���ؽ�: ���� �����Ϳ� ���� ������ ����ȭ
    std::condition_variable cv;    // ���� ����: ������ �� ����� ���� ���
    T shared_data;                 // ��ȣ�Ǵ� ���� ������

public:
    // ������: �ʱ� �����ͷ� ���� �����͸� �ʱ�ȭ
    Monitor(T initial_data) : shared_data(initial_data) {}

    // ����ȭ�� ������ ���� ���ø� �޼���
    // Func: ���� �����Ϳ� ���� ������ �۾��� �����ϴ� �Լ� ��ü
    template <typename Func>
    auto synchronizedAccess(Func func)  -> decltype(func(shared_data)) {
        std::lock_guard<std::mutex> lock(mtx);  // ���ؽ� ���
        std::cout << "lock�� ����� ������ id : " << std::this_thread::get_id()<< "\n";
        return func(shared_data);               // �Լ� ���� �� ��� ��ȯ
    }

    // ���� ���� ������ ������ ���ø� �޼���
    // Pred: ��� ������ �����ϴ� ���� �Լ�
    // Func: ������ ������ �� ������ �Լ�
    template <typename Pred, typename Func>
    auto waitAndAccess(Pred pred, Func func) -> decltype(func(shared_data)) {
        std::cout << "lock�� ����� ������ id : " << std::this_thread::get_id() << "\n";
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this, &pred] { return pred(shared_data); });  // ���� ���
        return func(shared_data);  // ���� ���� �� �Լ� ���� �� ��� ��ȯ
    }

    // �ϳ��� ��� ���� �����忡 �˸�
    void notify() {
        cv.notify_one();
    }

    // ��� ��� ���� �����忡 �˸�
    void notifyAll() {
        cv.notify_all();
    }
};


