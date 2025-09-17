#include <example/date.h>
#include <example/span.h>
#include <ranges>
#include <vector>

using example::date;
using example::span;

void print_dates(span<date> dates) {
    for (size_t i = 0; i < dates.size(); i++) {
        auto d = dates[i];
        puts(std::format("{}: {}", i, d).c_str());
    }
}


int main() {
    using namespace std::ranges;

    iota_view dates(date(2025, 8, 25), date(2025, 9, 5));

    print_dates(std::vector(dates.begin(), dates.end()));
}
