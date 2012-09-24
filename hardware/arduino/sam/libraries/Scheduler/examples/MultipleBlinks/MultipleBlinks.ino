
// Include Scheduler since we want to manage multiple tasks.
#include <Scheduler.h>

int led1 = 13;
int led2 = 12;
int led3 = 11;

void setup() {
  Serial1.begin(115200);

  // Setup the 3 pins as OUTPUT
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  // Add "loop2" and "loop3" to scheduling.
  // "loop" is always started by default.
  Scheduler.startLoop(loop2);
  Scheduler.startLoop(loop3);
}

// Task no.1: blink LED with 1 second delay.
void loop() {
  digitalWrite(led1, HIGH);

  // IMPORTANT:
  // We must use 'sleep' instead of 'delay' to guarantee
  // that the other tasks get executed.
  // (sleep passes control to other tasks while waiting)
  sleep(1000);

  digitalWrite(led1, LOW);
  sleep(1000);
}

// Task no.2: blink LED with 0.1 second delay.
void loop2() {
  digitalWrite(led2, HIGH);
  sleep(100);
  digitalWrite(led2, LOW);
  sleep(100);
}

// Task no.3: accept commands from Serial1 port
// '0' turns off LED
// '1' turns on LED
void loop3() {
  if (Serial1.available()) {
    char c = Serial1.read();
    if (c=='0')
      digitalWrite(led3, LOW);
    if (c=='1')
      digitalWrite(led3, HIGH);
  }

  // IMPORTANT:
  // We must call 'yield' at a regular basis to pass
  // control to other tasks.
  yield();
}