#ifndef EQUIP_CHECK_TEST_RUNNER_HPP
#define EQUIP_CHECK_TEST_RUNNER_HPP

#include <iostream>
#include <source_location>
#include <string_view>

class TestRunner
{
public:
    void expect(
        bool condition,
        std::string_view expression,
        const std::source_location location = std::source_location::current()
    )
    {
        if (condition)
        {
            return;
        }

        ++failures;
        std::cerr << location.file_name() << ':' << location.line()
                  << ": expectation failed: " << expression << '\n';
    }

    [[nodiscard]] int result() const
    {
        return failures == 0 ? 0 : 1;
    }

private:
    int failures { 0 };
};

#define EXPECT(runner, expression) \
    (runner).expect((expression), #expression, std::source_location::current())

#endif
