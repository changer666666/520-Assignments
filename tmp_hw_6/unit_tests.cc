#include "gtest/gtest.h"
#include "integrator.h"
#include "derivative.h"

namespace {
    class Constant : public Process {
        public:

        Constant(std::string name) : Process(name) {}

        void init() {}
        void start() {}
        void update() {
            channel("link").send(1);
        }
        void stop() {}
    };  

    TEST(Integrator, test1) {
      elma::Manager m;

      Integrator r("integrator");
      Constant s("constant");
      elma::Channel link("link");

      m.schedule(r, 1_ms)
        .schedule(s, 1_ms)
        .add_channel(link)
        .init()
        .run(100_ms);
    }

    class Increase : public Process {
        public:

        Increase(std::string name) : Process(name) {}

        void init() {}
        void start() {
            n = 0;
        }
        void update() {
            channel("link").send(n);
            n += 5;
        }
        void stop() {}

        private:
        int n;
    };  

    TEST(Derivative, test2) {
      elma::Manager m;

      Derivative r("derivative");
      Increase s("increase");
      elma::Channel link("link");

      m.schedule(r, 2_ms)
        .schedule(s, 1_ms)
        .add_channel(link)
        .init()
        .run(100_ms);
    }
}