// Writes the pin numbers to A or B
  // & pointers change the value of whats input to the functions
  void writePin(int drinkNum, int& motPin, int& flowPin) {
    switch(drinkNum) {
      case 1:
        motPin = motor1Pin;
        flowPin = flow1Pin;
        break;
      case 2: 
        motPin = motor2Pin;
        flowPin = flow2Pin;
      case 3:
        motPin = motor3Pin;
        flowPin = flow3Pin;
        break;
      case 4:
        motPin = motor4Pin;
        flowPin = flow4Pin;
        break;
    }
  }

// Gets drink choices
int drinkSelect() {
  int choice;
  // Loop until the '#' key is pressed
  while (key != '#') {
    // Get the pressed key
    char key = getKey();
    // Check if a valid key is pressed
    if (key != 0) {
      // Execute different actions based on the pressed key
      switch (key) {
        // Display Drink1 on the LCD
        case '1':
          lcd.setCursor(0, 1);
          lcd.print("");
          lcd.print(Drink1);
          choice = 1;
          break;
        // Display Drink2 on the LCD
        case '2':
          lcd.setCursor(0, 1);
          lcd.print("");
          lcd.print(Drink2);
          choice = 2;
          break;
        // Display Drink3 on the LCD
        case '3':
          lcd.setCursor(0, 1);
          lcd.print("");
          lcd.print(Drink3);
          choice = 3;
          break;
        // Display Drink4 on the LCD
        case '4':
          lcd.setCursor(0, 1);
          lcd.print("");
          lcd.print(Drink4);
          choice = 4;
          break;

        //Clear the LCD screen
        case '#':
          return choice;
          break;

        default:
          lcd.setCursor(0, 1);
          lcd.print("");
          lcd.print("Invalid Choice");
      }
    }
  }
  return choice;
}
// Gets ratio choices
int ratioSelect() {
  int choice;
  // Loop until the '#' key is pressed
  while (key != '#') {
    // Get the pressed key
    char key = getKey();
    // Check if a valid key is pressed
    if (key != 0) {
      // Execute different actions based on the pressed key
      switch (key) {
        // Display Ratio1 on the LCD
        case 'A':
          lcd.setCursor(0, 1);
          lcd.print("");
          lcd.print(Ratio1);
          choice = 1;
          break;
        // Display Ratio2 on the LCD
        case 'B':
          lcd.setCursor(0, 1);
          lcd.print("");
          lcd.print(Ratio2);
          choice = 2;
          break;
        // Display Ratio3 on the LCD
        case 'C':
          lcd.setCursor(0, 1);
          lcd.print("");
          lcd.print(Ratio3);
          choice = 3;
          break;
        // Display Ratio4 on the LCD
        case 'D':
          lcd.setCursor(0, 1);
          lcd.print("");
          lcd.print(Ratio4);
          choice = 4;
          break;
        // Clear the LCD screen
        case '#':
          return choice;
          break;
        default:
          lcd.setCursor(0, 1);
          lcd.print("");
          lcd.print("Invalid Choice");
    
      }
    }
  }
  return choice;
}
// Reads what key was pressed
  // Credits to https://www.circuitbasics.com/how-to-set-up-a-keypad-on-an-arduino/#google_vignette for this function
  int getKey() { 

      int k = 0;  // Initialize the key value to 0

      // Loop through each column of the keypad
      for (int c = 0; c < cols; c++) {
        // Activate the current column by setting it LOW
        digitalWrite(colPins[c], LOW);

        // Loop through each row of the keypad
        for (int r = 0; r < rows; r++) {
          // Check if the current row is LOW, indicating a key press
          if (digitalRead(rowPins[r]) == LOW) {
            delay(20);  // Debounce time to avoid false readings
            // Wait until the key is released
            while (digitalRead(rowPins[r]) == LOW)
              ;  // Empty loop
            // Store the value of the pressed key
            k = keys[r][c];
          }
        }
        // Deactivate the current column by setting it HIGH
        digitalWrite(colPins[c], HIGH);
      }
      // Return the value of the pressed key
      return k;
 }
