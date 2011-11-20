#include <Shell.h>

Shell shell;
uint8_t my_size = 120;
uint16_t my_length = 321;
uint8_t my_array[3];

void setup() {
  Serial.begin(115200);
  
  shell.addCommand("size", "to fill the size property", &my_size);
  shell.addCommand("length", "to fill the length property", &my_length);
  shell.addCommand("array1", "to fill the array property", &my_array[0]);
  shell.addCommand("array2", "to fill the array property", &my_array[1]);
  shell.addCommand("array3", "to fill the array property", &my_array[2]);
  shell.setReadwrite();
  shell.addCommand("save", "save parameters", saveIt);
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
    shell.parseCommand(c);
  }
}
