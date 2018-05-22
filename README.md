# oolog
### Table of contents
- [Overview](#overview)
    - [Why another log library](#why-another-log-library)
- [Getting started](#getting-started)
    - [Get the code](#get-the-code)
    - [Quick start](#quick-start)
    - [Samples](#samples)
- [Design](#design)
    - [Available Printers](#available-printers)
    - [Testing code using oolog](#testing-code-using-oolog)
- [Customization](#customization)
- [License](#license)

# Overview
oolog stands for object oriented log. It is a customizable and easy to use logging library  for Modern C++ application.

## Why another log library
The main reason that motivated me to make another log library was the fact that the most famous C++ log libraries on GitHub don't follow some code practices I am very used to.

In this library you won't use magic global initialization macros, there are no global states and you won't need to learn a new way of formatting text.

With this library, you will use proper objects. You will have the ability to create as many log objects as you want and customize them as you like.

Code using this library, will be easy to test and you won't have to worry about test code logging to console or files. You will only need to inject the provided test double to your class under test.

# Getting started
## Get the code
```
git clone https://github.com/PauGuillamon/oolog.git
```
Once you have the repository, you can [build it](#build) in order to link against a shared or static library, or you can [add the files to your project](#add-files-to-project).

### Build
```
cd oolog
mkdir build
cd build
cmake ..
make
```
By default, it will build:
- static and shared libraries
- tests
- samples

If you only want to build one of them, add a `target` when calling `make`. Examples:
```
make oolog          // will only build shared library
make oolog-static   // will only build static library
make oologTest      // will only build test suite
make sample_001     // will only build sample 001
```
### Add files to project
Add the `src/oolog.cpp` file to your project and add the `include/` folder as include directory.

If you are going to use any of the printers provided by **oolog**, add the printers you need from `src/printers/xxx.cpp` and add the `include/printers/` folder as include directory to your project.

Each printer can also be decorated to add functionality.

## Quick Start
Once you have the library in your project, it is as easy to use it as the following code:
```
#include "oolog.h"
#include "printers/ConsoleLogPrinter.h"

void RunApp(oolog::Log& myLog);

int main(){
    std::shared_ptr<oolog::LogPrinter> logPrinter =
        std::make_shared<oolog::EndlLogPrinter>(
        std::make_shared<oolog::ConsoleLogPrinter>());

    oolog::Log log(logPrinter, oolog::LogLevel::Verbose);

    RunApp(log);

    return 0;
}


void RunApp(oolog::Log& myLog) {
    myLog.Info("App has started!");
    myLog.Verbose("hello log!");
    myLog.Info("Closing app...");
}
```

## Samples
Check the `samples` folder to see more usages of the library.

# Design
The library has been designed to be highly customizable. 
## Available Printers
TODO
## Testing code using oolog
oolog integrates perfectly in test suites (whether they are unit tests or integration tests). You only need to provide a Printer that fulfills your requirements in the test suite.

Furthermore, oolog provides a **FakePrinter** that you can use as test double for your test suite. You won't have to worry about having logs when running your automated tests.

The FakePrinter is actually used to test oolog itself.

# Customization
TODO

# License
MIT License

Copyright (c) 2018 

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.


