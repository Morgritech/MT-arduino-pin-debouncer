// Copyright (C) 2024 Morgritech
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

/// @file pin_debouncer.cpp
/// @brief Class to debounce (filter out noise) on input pins.

#include "pin_debouncer.h"

#include <Arduino.h>

namespace mt {

PinDebouncer::PinDebouncer(uint8_t gpio_pin, uint16_t debounce_period_ms) {
  gpio_pin_ = gpio_pin;
  debounce_period_ms_ = debounce_period_ms; // (ms).
}

PinDebouncer::~PinDebouncer() {}

PinDebouncer::Status PinDebouncer::DebouncePin() {
  PinState pin_state = static_cast<PinState>(digitalRead(gpio_pin_));

  if (debounce_status_ == Status::kNotStarted) {
    debounce_status_ = Status::kOngoing;
    reference_debounce_time_ms_ = millis();
  }
  else if (pin_state != previous_pin_state_) {
    // A bounce has occurred.
    reference_debounce_time_ms_ = millis();
  }
  else if ((millis() - reference_debounce_time_ms_) >= debounce_period_ms_) {
    // Finished debouncing.
    debounce_status_ = Status::kNotStarted;
  }

  previous_pin_state_ = pin_state;
  return debounce_status_;
}

} // namespace mt