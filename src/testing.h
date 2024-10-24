#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <stdexcept>

namespace jvl::testing
{
    class test;

    std::vector<test *> tests{};

    inline void add_test(test *t) {
        tests.emplace_back(t);
    }

    template <typename T>
    inline void equal(T expected, T actual, std::string_view fail_reason = "") {
        if (expected != actual) {
            if (fail_reason.empty()) fail_reason = "expected != actual";
            throw std::logic_error(fail_reason.data());
        }
    }

    template <typename T>
    inline void not_equal(T expected, T actual, std::string_view fail_reason = "") {
        if (expected == actual) {
            if (fail_reason.empty()) fail_reason = "expected == actual";
            throw std::logic_error(fail_reason.data());
        }
    }

    inline void assert(bool assertion, std::string_view fail_reason = "") {
        if (!assertion) {
            if (fail_reason.empty()) fail_reason = "invalid assertion";
            throw std::logic_error(fail_reason.data());
        }
    }

    class test
    {
        std::string_view _name;
        std::function<void()> _test_impl;
        
    public:
        test(std::string_view name, std::function<void()> fn)
            : _name(name)
            , _test_impl(fn)
        {
            add_test(this);
        }

        [[nodiscard]] std::string_view get_name() const noexcept {
            return _name;
        }

        [[nodiscard]] std::string_view run() {
            try
            {
                _test_impl();
                return "🟢 OK";
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                return "🟥 Failure";
            }
        }
    };


    #define TEST(x,fn) jvl::testing::test x(#x,fn);

    inline void run_tests()
    {
        for (auto &test : tests) {
            std::cout << "" << test->get_name() << " " << test->run() << "\n";
        }
    }
}