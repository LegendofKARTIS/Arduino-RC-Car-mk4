#include <BluetoothSerial.h>
BluetoothSerial SerialBT;

#define in1 25
#define in2 26
#define in3 27
#define in4 14
#define led 32

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP_RC-Car");

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(led, OUTPUT);

  StopAll();
}

void loop() {
  if (SerialBT.available()) {
    char cmd = SerialBT.read();
    Serial.print("Received: ");
    Serial.println(cmd);
    handleCommand(cmd);
  }
}

void handleCommand(char cmd) {
  StopAll(); // Stop all before processing new command

  switch (cmd) {
    case 'F': // Forward only
      moveForward();
      break;
    case 'B': // Backward only
      moveBackward();
      break;
    case 'L': // Left only
      turnLeft();
      break;
    case 'R': // Right only
      turnRight();
      break;
    case 'G': // Forward + Left
      moveForward();
      turnLeft();
      break;
    case 'H': // Forward + Right
      moveForward();
      turnRight();
      break;
    case 'I': // Backward + Left
      moveBackward();
      turnLeft();
      break;
    case 'J': // Backward + Right
      moveBackward();
      turnRight();
      break;
    case 'S': // Stop all
    case 'X':
      digitalWrite(led, HIGH);
      break;
    case 'x':
      digitalWrite(led, LOW);
      break;
    default:
      StopAll();
      break;
  }
}

void moveForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}

void moveBackward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  
}

void turnLeft() {
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void turnRight() {
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void StopAll() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(led, LOW);
}
