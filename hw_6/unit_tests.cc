#include "gtest/gtest.h"
#include "stopwatch.h"
#include "random_process.h"
#include "filter.h"

namespace {
    TEST(Stopwatch, test1) {

      #define SLEEP std::this_thread::sleep_for(std::chrono::milliseconds(1500))

      Stopwatch w; // should set the stopwatch to 0 seconds
      w.start(); 
      SLEEP;
      w.stop();    
      std::cout << w.get_seconds() << "\n"; // about 1.5
      SLEEP;
      std::cout << w.get_seconds() << "\n"; // still about 1.5
      w.start(); 
      SLEEP;
      w.stop();    
      std::cout << w.get_seconds() << "\n"; // about 3.0
      w.reset();
      std::cout << w.get_seconds() << "\n"; // 0.0
    }

    TEST(Stopwatch, test2) {

      #define SLEEP std::this_thread::sleep_for(std::chrono::milliseconds(1500))

      Stopwatch w; // should set the stopwatch to 0 seconds
      w.start(); 
      SLEEP;   
      w.start(); 
      SLEEP;
      w.stop();    
      std::cout << w.get_seconds() << "\n"; // about 1.5
      w.reset();
      std::cout << w.get_seconds() << "\n"; // 0.0
    }

    TEST(Stopwatch, test3) {

      #define SLEEP std::this_thread::sleep_for(std::chrono::milliseconds(1500))

      Stopwatch w; // should set the stopwatch to 0 seconds
      w.start(); 
      SLEEP;   
      w.stop();    
      std::cout << w.get_seconds() << "\n"; // about 1.5
      w.stop();    
      std::cout << w.get_seconds() << "\n"; // about 1.5
      w.reset();
      std::cout << w.get_seconds() << "\n"; // 0.0
    }

    TEST(Stopwatch, test4) {

      #define SLEEP std::this_thread::sleep_for(std::chrono::milliseconds(1500))

      Stopwatch w; // should set the stopwatch to 0 seconds
      w.start(); 
      SLEEP;   
      w.stop();    
      std::cout << w.get_seconds() << "\n"; // about 1.5
         
      std::cout << w.get_minutes() << "\n"; 

      std::cout << w.get_milliseconds() << "\n"; 

      std::cout << w.get_nanoseconds() << "\n"; 
    }

    TEST(RandomProcessAndFilter, test1) {
      elma::Manager m;

      RandomProcess r("random numbers");
      Filter f("filter");
      elma::Channel link("link");

      m.schedule(r, 1_ms)
        .schedule(f, 1_ms)
        .add_channel(link)
        .init()
        .run(100_ms);
    }
}