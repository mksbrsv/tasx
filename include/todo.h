#ifndef TODO_H
#define TODO_H
#include <fmt/format.h>

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <string_view>
#include <variant>

class todo_item {
 public:
  todo_item() = default;
  todo_item(const std::string& subject, int id, bool status = false);
  todo_item(const todo_item& todo) = default;
  todo_item& operator=(const todo_item& todo) = default;
  void set_status(bool status);
  const std::string str_status() const;
  bool get_status() const;
  int get_id() const;
  std::string get_subject() const;
  std::string to_string() const;

  ~todo_item() = default;
  friend std::ofstream& operator<<(std::ofstream& out, const todo_item& todo);

 private:
  std::string m_subject;
  int m_id;
  bool m_status;
};

template <>
struct fmt::formatter<todo_item> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx);

  template <typename FormatContext>
  auto format(const todo_item& item, FormatContext& ctx);
};

template <typename ParseContext>
constexpr auto fmt::formatter<todo_item>::parse(ParseContext& ctx) {
  return ctx.begin();
}

template <typename FormatContext>
auto fmt::formatter<todo_item>::format(const todo_item& item,
                                       FormatContext& ctx) {
  return fmt::format_to(ctx.out(), "{0}. {1} {2}\n", item.get_id(),
                        item.str_status(), item.get_subject());
}

// template <>
// struct fmt::formatter<todo_item> {
//   using unsigned_fmt = fmt::formatter<unsigned>;
//   using string_view_fmt = fmt::formatter<std::string_view>;
//   using underlying_formatter_type = std::variant<string_view_fmt,
//   unsigned_fmt>;
//
//   template <typename ParseContext>
//   constexpr auto parse(ParseContext& ctx) {
//     auto fmt_end = std::find(ctx.begin(), ctx.end(), '}');
//     if (fmt_end != ctx.begin()) {
//       char representation = *ctx.begin();
//       if (representation == 'd') {
//         underlying_formatter = unsigned_fmt{};
//       } else if (representation != 'r') {
//         throw fmt::format_error("invalid representation");
//       }
//       ctx.advance_to(std::next(ctx.begin()));
//     }
//     return std::visit([&](auto& fmt) { return fmt.parse(ctx); },
//                       underlying_formatter);
//   }
//
//   template <typename FormatContext>
//   auto format(const todo_item& item, FormatContext& ctx) {
//     return std::visit(formatting_visitor<FormatContext>{number, ctx},
//                       underlying_formatter);
//   }
//
//  private:
//   underlying_formatter_type underlying_formatter;
// };

#endif
