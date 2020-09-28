//
// Created by think on 3/5/16.
//

#include <pigpiod_if2.h>

#include <cstring>
#include <iostream>

#include "SparkFunSX1509.h"

void isrfn();

const byte SX1509_BUTTON_PIN = 0;  // Active-low button
const byte SX1509_ADDRESS = 0x3E;  // SX1509 I2C address
uint8_t buttonPressed = 0;         // Track button press in ISR
const byte INT_PIN = 7;  // SX1509 int output to wiringPI Pin 7, next to SDA/SCL
const int time_out = 10;

uint32_t buttonHit = 0;

int main(int argc, char** argv) {
  auto io = SX1509();

  auto pigpio_id = pigpio_start(0, 0);
  if (pigpio_id < 0) {
    fprintf(stderr, "Unable to setup pigpio: %s\n", strerror(errno));
    return 1;
  }

  if (!io.begin(pigpio_id, SX1509_ADDRESS)) {
    std::cout << "Init failed" << std::endl;
    return 1;
  }

  io.pinMode(SX1509_BUTTON_PIN, INPUT_PULLUP);
  io.enableInterrupt(SX1509_BUTTON_PIN, FALLING);
  io.debounceTime(2);
  io.debouncePin(SX1509_BUTTON_PIN);

  set_pull_up_down(pigpio_id, INT_PIN, PI_PUD_UP);
  set_mode(pigpio_id, INT_PIN, PI_INPUT);
  if (callback(pigpio_id, INT_PIN, FALLING_EDGE, nullptr) != 0) {
    fprintf(stderr, "Unable to setup ISR: %s\n", strerror(errno));
    return 1;
  }

  while (true) {
    if (buttonPressed == 0) {
      time_sleep(0.100);
      continue;
    }
    unsigned int intStatus = io.interruptSource();

    if (intStatus & (1 << SX1509_BUTTON_PIN)) {
      buttonHit++;
      std::cout << "ButtonHit: " << buttonHit << std::endl;
    }

    buttonPressed--;  // Clear the buttonPressed flag
  }
  return 0;
}

// button() is an Arduino interrupt routine, called whenever
// the interrupt pin goes from HIGH to LOW.
void isrfn(int gpio, int level, uint32_t tick) {
  buttonPressed++;  // Set the buttonPressed flag to true
                    // We can't do I2C communication in an Arduino ISR. The best
                    // we can do is set a flag, to tell the loop() to check next
                    // time through.
}
