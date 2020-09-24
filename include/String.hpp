#pragma once

#include "Include.hpp"

namespace CatanLeaderboard {

/// \brief Split a string into words using whitespace as a delimiter.
std::vector<std::string> split_by_whitespace(const std::string& text) noexcept {
  std::istringstream stream{text};
  std::vector<std::string> words{std::istream_iterator<std::string>{stream}, std::istream_iterator<std::string>{}};
  return words;
}

/// \brief Split a string into words using a given delimiter. The delimiter character is removed.
std::vector<std::string> split(const std::string& text, const char delimiter) noexcept {
  std::stringstream stream(text);
  std::string word;
  std::vector<std::string> words;
  while (std::getline(stream, word, delimiter)) {
    words.push_back(word);
  }
  return words;
}

/// \brief Remove whitespace in a string.
std::string remove_whitespace(const std::string& text) noexcept {
  std::string new_text{text};
  new_text.erase(remove_if(new_text.begin(), new_text.end(), ::isspace), new_text.end());
  return new_text;
}

/// \brief Remove non-alphanumeric characters in a string.
std::string remove_non_alphanumeric_characters(const std::string& text) noexcept {
  std::string new_text;
  for (const char character : text) {
    if (::isalnum(character)) {
      new_text += character;
    }
  }
  return new_text;
}

/// \brief Remove non-alphabetic characters in a string.
std::string remove_non_alphabetic_characters(const std::string& text) noexcept {
  std::string new_text;
  for (const char character : text) {
    if (::isalpha(character)) {
      new_text += character;
    }
  }
  return new_text;
}

/// \brief Pad a string to a given length using trailing spaces.
/// \details If the string is already longer than the given length, nothing is changed.
std::string pad_to_length(const std::string& text, uint_least64_t length) noexcept {
  std::string padded_text{text};
  if (length > padded_text.length()) {
    padded_text.append(length - padded_text.length(), ' ');
  }
  return padded_text;
}

/// \brief Print a real number as a string to a given number of significant digits.
std::string real_number_to_string(const double value, const uint_least8_t significant_digits = 7) noexcept {
  if (value == 0.0) {
    return "0";
  } else {
    const double absolute_value{std::abs(value)};
    const double log10_absolute_value{std::log10(absolute_value)};
    const int_least64_t floor_log10_absolute_value{(int_least64_t)std::floor(log10_absolute_value)};
    const int_least64_t raw_precision{(int_least64_t)significant_digits - floor_log10_absolute_value - 1};
    const uint_least64_t precision{(uint_least64_t)std::min(std::max(raw_precision, (int_least64_t)0), (int_least64_t)16)};
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(precision) << value;
    return stream.str();
  }
}

/// \brief Print a real number as a percentage rounded to the nearest 1%.
std::string real_number_to_percentage_string(const double value) noexcept {
  if (value == 0.0) {
    return "0%";
  } else {
    const double value_100{value * 100};
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(0) << value_100 << "%";
    return stream.str();
  }
}

/// \brief Parse a string as a natural number.
std::optional<uint_least64_t> string_to_natural_number(const std::string& text) noexcept {
  char* end = 0;
  const unsigned long long int value = std::strtoull(text.c_str(), &end, 10);
  if (end != text.c_str() && *end == '\0' && value != ULLONG_MAX) {
    return {(uint_least64_t)(value)};
  }
  const std::optional<uint_least64_t> no_value;
  return no_value;
}

/// \brief Parse a string as an integer number.
std::optional<int_least64_t> string_to_integer_number(const std::string& text) noexcept {
  char* end = 0;
  const long long int value = std::strtoll(text.c_str(), &end, 10);
  if (end != text.c_str() && *end == '\0' && value != LLONG_MAX) {
    return {(int_least64_t)(value)};
  }
  const std::optional<int_least64_t> no_value;
  return no_value;
}

/// \brief Parse a string as a real number.
std::optional<double> string_to_real_number(const std::string& text) noexcept {
  char* end = 0;
  const double value = strtod(text.c_str(), &end);
  if (end != text.c_str() && *end == '\0' && value != HUGE_VAL && value != -HUGE_VAL) {
    return {value};
  }
  const std::optional<double> no_value;
  return no_value;
}

} // namespace CatanLeaderboard
