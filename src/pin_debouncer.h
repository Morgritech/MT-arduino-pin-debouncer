// Copyright (C) 2024 Morgritech
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

/// @file pin_debouncer.h
/// @brief Class to debounce (filter out noise) on input pins.

#ifndef PIN_DEBOUNCER_H_
#define PIN_DEBOUNCER_H_

#include <Arduino.h>

namespace mt {

/// @brief The Pin Debouncer class.
class PinDebouncer {
 public:

  /// @brief Enum of GPIO pin states.
  enum class PinState {
    kLow = 0,
    kHigh,
  };

  /// @brief Enum of debounce status.
  enum class Status {
    kNotStarted = 0,
    kOngoing,
  };

  /// @brief Construct a Pin Debouncer object.
  /// @param gpio_pin The GPIO input pin to debounce.
  /// @param debounce_period The period of time (ms) allowed for pin debouncing.
  explicit PinDebouncer(uint8_t gpio_pin, uint16_t debounce_period = 70);

  /// @brief Destroy the Pin Debouncer object.
  ~PinDebouncer();

  /// @brief Debounce (filter out noise) on the input pin. This must be called periodically.
  /// @return The status of the debounce operation.
  Status DebouncePin() const;

 private:

  /// @brief The GPIO input pin to debounce.
  uint8_t gpio_pin_;
  /// @brief The period of time (ms) allowed for pin debouncing.
  uint16_t debounce_period_;
};

} // namespace mt

#endif // PIN_DEBOUNCER_H_