// Copyright (C) 2024 Morgritech
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

/// @file detect_pin_state_change.ino
/// @brief Example showing how to detect state change on a pin using the MT-arduino-pin-debouncer library.

#include <pin_debouncer.h>

/// @brief Pin to debounce (e.g., for a push button).
const uint8_t kPinA = 2;
/// @brief Debounce period in milliseconds (ms) for the pin.
const uint32_t kPinADebouncePeriod_ms = 20;

/// @brief The Pin Debouncer instance for the pin.
mt::PinDebouncer pin_a_debouncer = mt::PinDebouncer(kPinA, kPinADebouncePeriod_ms);
//mt::PinDebouncer pin_a_debouncer = mt::PinDebouncer(kPinA); // Default value of 70 ms is used for the debounce period.

/// @brief The serial communication speed for the Arduino board.
const int kBaudRate = 9600;

/// @brief The main application entry point for initialisation tasks.
void setup(){
  // Initialise the Serial Port.
  Serial.begin(kBaudRate);

  // Initialise the input pin.
  pinMode(kPinA, INPUT);

  Serial.println("\n...Setup complete...\n");
}

/// @brief The continuously running function for repetitive tasks.
void loop(){
  // Variable to keep track of the debouncing operation.
  static mt::PinDebouncer::Status pin_a_status = mt::PinDebouncer::Status::kNotStarted;
  // Variable to keep track of which pin state is being debounced.
  static bool pin_a_debouncing_high = false;
  // Counter to keep track of each unique state change (HIGH-LOW).
  static int counter = 0;

  // Detect state change on the pin.
  if (pin_a_status == mt::PinDebouncer::Status::kNotStarted && pin_a_debouncing_high == false) {
    // Pin not yet activated (e.g., button not pressed).
    if (digitalRead(kPinA) == HIGH) {
      // Pin activated (e.g., button has been pressed).
      counter++;
      pin_a_debouncing_high = true;
      pin_a_status = mt::PinDebouncer::Status::kOngoing;
      Serial.print("Pin state is HIGH ");
      Serial.println(counter);
    }
  }
  else if (pin_a_status == mt::PinDebouncer::Status::kNotStarted && pin_a_debouncing_high == true) {
    // Finished debouncing an activated pin (e.g., a button press).
    if (digitalRead(kPinA) == LOW) {
      // Pin deactivated (e.g., button has been released).
      pin_a_debouncing_high = false;
      pin_a_status = mt::PinDebouncer::Status::kOngoing;
      Serial.print("Pin state is LOW ");
      Serial.println(counter);
    }
  }

  // Debounce the pin if it is activated/deactivated (e.g., button pressed/released).
  if (pin_a_status == mt::PinDebouncer::Status::kOngoing) {
    pin_a_status = pin_a_debouncer.DebouncePin(); // This must be called periodically.
  }
}