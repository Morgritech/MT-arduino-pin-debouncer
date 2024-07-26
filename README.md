# MT-arduino-pin-debouncer

[![Static check](https://github.com/Morgritech/MT-arduino-pin-debouncer/actions/workflows/static-check.yaml/badge.svg)](https://github.com/Morgritech/MT-arduino-pin-debouncer/actions/workflows/static-check.yaml) [![Build examples](https://github.com/Morgritech/MT-arduino-pin-debouncer/actions/workflows/build-examples.yaml/badge.svg)](https://github.com/Morgritech/MT-arduino-pin-debouncer/actions/workflows/build-examples.yaml)

Pin debouncer library for the Arduino platform, to filter out noise on an input pin.

This library implements a non-blocking function to detect and filter out random state changes on input pins. The library can handle detection of state changes on multiple pins.

See the "examples" folder for how to get started on using the library to detect state changes on a pin.

An ideal use-case for the library would be to incorporate it into other libraries where pin debouncing is required, such as the [MT-arduino-momentary-button](https://github.com/Morgritech/MT-arduino-momentary-button) library.

This library can be installed via the Arduino Library Manager.
