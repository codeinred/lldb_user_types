#pragma once
#include <chrono>
#include <cstdint>
#include <format>
#include <string>


namespace example {
using std::chrono::year_month_day;


class date {
    /// Days since epoch
    int32_t days_;

    constexpr date(int32_t days) noexcept : days_(days) {}

  public:
    constexpr static date from_days(int32_t days) noexcept {
        return date(days);
    }

    date() = default;


    date(int year, unsigned m, unsigned d)
      : date(year_month_day(std::chrono::year(year),
                            std::chrono::month(m),
                            std::chrono::day(d))) {}

    date& operator++() noexcept { return ++days_, *this; }
    date& operator--() noexcept { return --days_, *this; }
    date  operator++(int) noexcept { return date{days_++}; }
    date  operator--(int) noexcept { return date{days_--}; }

    date operator+(int count) const noexcept { return date(days_ + count); }
    date operator-(int count) const noexcept { return date(days_ - count); }

    int64_t operator-(date rhs) const noexcept {
        return int64_t(days_) - rhs.days_;
    }

    bool operator==(date const& rhs) const noexcept  = default;
    bool operator<=>(date const& rhs) const noexcept = default;

    date(year_month_day ymd)
      : days_(std::chrono::sys_days(ymd).time_since_epoch().count()) {}

    year_month_day to_ymd() const {
        return std::chrono::sys_days(std::chrono::days(days_));
    }

    std::string to_string() const {
        auto ymd = to_ymd();
        return std::format("{:0>4}-{:0>2}-{:0>2}",
                           int(ymd.year()),
                           unsigned(ymd.month()),
                           unsigned(ymd.day()));
    }
};


} // namespace example


template <>
struct std::formatter<example::date, char> : std::formatter<std::string, char> {
    template <class FmtContext>
    FmtContext::iterator format(example::date d, FmtContext& ctx) const {
        return std::formatter<std::string, char>::format(d.to_string(), ctx);
    }
};
