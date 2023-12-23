#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex mtx;
condition_variable cv;
bool flag = false;


void producer()
{
	while (true)
	{
		this_thread::sleep_for(chrono::milliseconds(1000));
		unique_lock<mutex> ul(mtx);
		flag = true;
		cout << "Событие отправлено\n";
		cv.notify_one();
	}
}

void consumer()
{
	while (true)
	{
		unique_lock<mutex> ul(mtx);
		while (!flag) cv.wait(ul);
		flag = false;
		cout << "Событие обработано\n";
	}
}


int main()
{
	setlocale(LC_ALL, "ru");
	thread th1(producer);
	thread th2(consumer);

	th1.join();
	th2.join();

	return 0;
}
