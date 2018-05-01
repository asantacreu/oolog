
#include "oolog.h"
#include "printers/ConsoleLogPrinter.h"
#include "printers/ColoredLogPrinter.h"
#include "printers/EndlLogPrinter.h"
#include "printers/TypedLogPrinter.h"

#include <thread>
#include <chrono>



void ThreadedFunction(oolog::Log* myLog) {
	std::thread::id threadId = std::this_thread::get_id();
	for (int i = 0; i < 10; i++) {
		myLog->Info(i, " - thread id: ", threadId);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}



int main(){
    std::shared_ptr<oolog::LogPrinter> logPrinter =
        std::make_shared<oolog::TypedLogPrinter>(
        std::make_shared<oolog::ColoredLogPrinter>(
		std::make_shared<oolog::EndlLogPrinter>(
        std::make_shared<oolog::ConsoleLogPrinter>())));

    oolog::Log log(logPrinter, oolog::LogLevel::Verbose);

	std::thread threadOne(ThreadedFunction, &log);
	std::thread threadTwo(ThreadedFunction, &log);

	threadOne.join();
	threadTwo.join();


    return 0;
}

