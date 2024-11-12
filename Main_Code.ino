#include <LiquidCrystal_I2C.h>  //Library for controlling the LCD display via I2C


  #define kp 10 // Proportional gain
  #define kd 1 // Drivative gain
  #define volTotal 120 // Total amount of volume to be poured in ml

  #define calFactor 133.5 //Experimentally determined value to calibrate flow meters. 1oz = 133.5 pulses

// Defining pinouts for everything
  // Pins for signal from the hall encoder on the flowmeter
    // DO NOT change these since these are the only pins that can use interupts
    #define flow1Pin 2
    #define flow2Pin 3
    #define flow3Pin 18
    #define flow4Pin 19

  // PWM pins to control the motors atached to the pumps
    #define motor1Pin 4
    #define motor2Pin 5
    #define motor3Pin 6
    #define motor4Pin 7

    // Limit switch pins
      // Switches were not used in final demo
    #define doorOpenPin 8
    #define doorClosePin 9

  // Logic switches
    #define openSwitch 51 // change these!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! also define for pullup
    #define closeSwitch 52
    #define buttonRecieve 53  // Big red Button pin

  // Pins for Matrix Keypad
    const char rows = 4;  // set display to four rows
    const char cols = 4;  // set display to three columns
    // Defined as char to make setting pinmode easier in setup
    const char rowPins[rows] = { 23, 25, 27, 29};
    const char colPins[cols] = { 28, 26, 24, 22};

 int flowPinA = 0;
 int flowPinB = 0;
 int motPinA = 0;
 int motPinB = 0;


//======================================================================
// Variable Initializations
  // All drink customizations can be edited here
   // Spaces at the end fixed a bug where drink names merged
    char Drink1[] = "Dr. Pepper    ";
    char Drink2[] = "Root Beer     ";
    char Drink3[] = "Loganberry    ";
    char Drink4[] = "Sprite        ";
    char Ratio1[] = "1:3           ";
    char Ratio2[] = "1:1           ";
    char Ratio3[] = "3:1           ";
    char Ratio4[] = "1:0           ";
  // All of these setup the matrix keypad

    char msg[] = ""; // Message to be displayed on line 1 of LCD
    char choice("");

    char keys[rows][cols] = {
      { '1', '2', '3', 'A' },
      { '4', '5', '6', 'B' },
      { '7', '8', '9', 'C' },
      { '*', '0', '#', 'D' }
    };
    
    char key("");
    // sets the LCD address to 0x27 for a 16 chars and 2 line display
      LiquidCrystal_I2C lcd(0x27, 20, 4);
  // Timing variables
    unsigned long currentMillis = 0;
    unsigned long prevMillis = 0;
    int sampleRate = 1;

  // Volume of drinks added to cup
  float volA = 0;
  float volB = 0;

  int volA_desired = 50;
  int volB_desired = 50;

  // Control loop vars
  float errA = 0; // Error signal of pump A
  float errB = 0; // Error signal of pump B
  float prev_errA = 0;
  float prev_errB = 0;
  float derivA = 0;
  float derivB = 0;

  double VsA = 0; //Voltage to motor A
  double VsB = 0; //Voltage to motor B

  // Counts pulses from the flow meter
  volatile long pulseA;
  volatile long pulseB;

//======================================================================
// Interupt functions
    // Occurs during interupts and counts the pulses from the flow meter
    void pulseCountA() {
      pulseA++;
    }
    void pulseCountB() {
      pulseB++;
    }
//======================================================================
void setup() {

  // Serial only for debugging, remove for final product
  Serial.begin(9600);

 //analogWrite(6,250);
 // Initializations for LCD
    lcd.init();
    lcd.backlight();
    lcd.setCursor(3, 0);
    lcd.clear();

 // Pinmode for big button
    pinMode(buttonRecieve, INPUT_PULLUP);
    pinMode(closeSwitch, INPUT_PULLUP);
    pinMode(openSwitch, INPUT_PULLUP);

 // Sets pinmode for each keypad
   // Loop through each row of the keypad
    for (int r = 0; r < rows; r++) {
      // Set the row pins as input
      pinMode(rowPins[r], INPUT_PULLUP);
   }
  // Loop through each column of the keypad
    for (int c = 0; c < cols; c++) {
      // Set the column pins as output
      pinMode(colPins[c], OUTPUT);
    }

  //Enables digitalpins to read interupts sent from the flowmeter
  attachInterrupt(digitalPinToInterrupt(18), pulseCountA, RISING);
  attachInterrupt(digitalPinToInterrupt(flowPinB), pulseCountB, RISING);

}

void loop() {

  /*****************************************************************************
  All user input code to take drink orders before starting the arduino loop
  *******************************************************************************/
    lcd.setCursor(0, 0);
    lcd.print("Choose drink 1:");
    lcd.setCursor(0, 1);
    lcd.print("# to continue");
    volatile int drinkA = drinkSelect();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Choose drink 2:");

    volatile int drinkB = drinkSelect();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Choose ratio");

  //  int ratio = ratioSelect();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Press the Button!");

    volatile int buttonState = digitalRead(buttonRecieve);

      while (buttonState != 0 ) {
        buttonState = digitalRead(buttonRecieve);

      }
      lcd.clear();
      lcd.print("POURING...");

  // //Establishes what motors and sensors from user input
      if (drinkA = 1) {
      flowPinA = flow1Pin;
      motPinA = motor1Pin;
    } else if (drinkA = 2) {
      flowPinA = flow2Pin;
      motPinA = motor2Pin;
    } else if (drinkA = 3) {
      flowPinA = flow3Pin;
      motPinA = motor3Pin;
    } else if (drinkA = 4) {
      flowPinA = flow4Pin;
      motPinA = motor4Pin;
    }
      if (drinkB = 1) {
      flowPinB = flow1Pin;
      motPinB = motor1Pin;
    } else if (drinkB = 2) {
      flowPinB = flow2Pin;
      motPinB = motor2Pin;
    } else if (drinkB = 3) {
      flowPinB = flow3Pin;
      motPinB = motor3Pin;
    } else if (drinkB = 4) {
      flowPinB = flow4Pin;
      motPinB = motor4Pin;
    }

    // Function
    writePin(drinkA, motPinA, flowPinA);
    writePin(drinkB, motPinB, flowPinB);

    // Debugging stuff
    // Serial.print(motPinA);
    // Serial.print(motPinB);
    // Serial.print(flowPinA);
    // Serial.println(flowPinB);


  // Commented out as we couldn't get rdrink ratio selection it to work for the demo
  //  Serial.println(ratio);
    // switch(ratio) {
    //   case 1:
    //     volA_desired = (1/4)*volTotal;
    //     volB_desired = (3/4)*volTotal;
    //     break;
    //   case 2:
    //     volA_desired = (1/2)*volTotal;
    //     volB_desired = (1/2)*volTotal;
    //     break;
    //   case 3:
    //     volA_desired = (3/4)*volTotal;
    //     volB_desired = (1/4)*volTotal;
    //     break;   
    //   case 4:
    //     volA_desired = volTotal;
    //     volB_desired = 0;   
    // }

    // Since select doesn't work were going with a 1:1 ration
    volA_desired = (0.5)*volTotal;
    volB_desired = (0.5)*volTotal;


  //Door not implemented yet
  // // Door swinging loop goes here
  //   while (closeSwitch == 0) {
  //     analogWrite(doorOpenPin, 80);
  //     analogWrite(doorClosePin, 0);
  //   }
  //     analogWrite(doorOpenPin, 0);



  /****************************************************************************
  Control Loop
  ******************************************************************************/
    volatile float errTot;
    volatile float errA;
    volatile float errB;

     errA = volA_desired - volA;
     errB = volB_desired - volB;

  while (errTot >= 0) {
     
     // Calculations
      volA = calFactor*pulseA;
      volB = calFactor*pulseB;

      errA = volA_desired - volA;
      errB = volB_desired - volB;

     derivative component of the contro
     derivA = errA - prev_errA;
     derivB = errB - prev_errB;

     // Command signal for pumps
      VsA = kp*errA + kd*derivA;
      VsB = kp*errB + kd*derivB;

      // Caps the command signal to 255 max and 0 min
        if (VsA > 255) {
          VsA = 255;
       }else if (VsA < 0) {
          VsA = 0;
        } 
        if (VsB > 255) {
          VsB = 255;
        }
        else if (VsB < 0) {
          VsB = 0;
        } 

        // Debugging stuff
        Serial.print(errA);
        Serial.print(",");
        Serial.print(pulseA);
        Serial.print(",");
        Serial.print(volA);
        Serial.print(",");
        Serial.print(errB);
        Serial.print(",");
        Serial.print(VsB);
        Serial.print(",");
        Serial.println(volB);

    analogWrite(motPinA, VsA);
    analogWrite(motPinB, VsB);

   prev_errA = errA;
   prev_errB = errB;
    errTot = errA + errB;




  }

  ////////////////////////////////////////////////////////////////////////  
  // Reset after pouring
  analogWrite(motPinA,0);
  analogWrite(motPinB,0);

  errA = 0;
  errB = 0;
  prev_errA = 0;
  prev_errB = 0;
  
}
