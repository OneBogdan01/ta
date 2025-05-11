#pragma once

#include "fmt/color.h"
namespace tale
{
namespace log
{

// TODO make it editable from an interface
constexpr fmt::color ColorInfo {fmt::color::green};
template< typename... T >

static void Info(fmt::format_string< T... > fmt, T&&... args)
{
  fmt::print(fmt::fg(ColorInfo), "[Info] ");
  fmt::print(fmt, std::forward< T >(args)...);
  fmt::print("\n");
}

} // namespace log
} // namespace tale
