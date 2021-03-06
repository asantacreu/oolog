
#include "oolog.h"
#include "printers/Console.h"
#include "printers/decorators/NewLine.h"
#include "printers/decorators/Timestamp.h"
#include "printers/decorators/Level.h"
#if defined _WINDOWS
	#include "printers/decorators/ColorWin32Console.h"
#else
	#include "printers/decorators/ColorANSI.h"
#endif



void ComplexOperation(oolog::Log& myLog) {
    myLog.Debug("Starting Complex Operation --------------------------");
    myLog.Verbose("preparing values....");
    myLog.Info("Starting");
    myLog.Warning("Some values are out of bound.");
    myLog.Error("Complex operation detected error. Error code: ", 3);
    myLog.Fatal("Couldn't recover after error. Cancelling operation");
    myLog.Info("Operation failed");
    myLog.Verbose("preparing to exit");
    myLog.Debug("Exiting complex Operation ---------------------------");
}



void RunApp(oolog::Log& myLog) {
    myLog.Info("App has started!");

    myLog.Verbose("hello world from oolog!");

    ComplexOperation(myLog);

    myLog.Info("Closing app...");
}



int main(){
    std::shared_ptr<oolog::printers::Printer> logPrinter =
        std::make_shared<oolog::printers::decorators::Level>(
        std::make_shared<oolog::printers::decorators::Timestamp>(
#if defined _WINDOWS
        std::make_shared<oolog::printers::decorators::ColorWin32Console>(
#else
        std::make_shared<oolog::printers::decorators::ColorANSI>(
#endif
        std::make_shared<oolog::printers::decorators::NewLine>(
        std::make_shared<oolog::printers::Console>()))));


    oolog::Log log(logPrinter, oolog::LogLevel::Verbose);

    RunApp(log);

    return 0;
}

