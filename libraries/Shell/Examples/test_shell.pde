#include <Shell.h>

Shell shell;
uint8_t my_size = 120;
uint16_t my_length = 321;

void setup() {
  Serial.begin(57600);
  shell.add_command("size", "to fill the size property", &my_size);
  shell.add_command("length", "to fill the length property", &my_length);
  shell.set_readwrite();
  shell.save_callback(saveIt);
}

void saveIt() {
  Serial.println("saved properties");
}

void loop() {
  while (Serial.available() > 0) {
    uint8_t c = Serial.read();
    if (c == 13 || c == 10) {
      Serial.println();
    }
    Serial.print(c);
    shell.parse_command(c);
  }
}
