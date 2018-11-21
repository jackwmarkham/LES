/*

*/

//Assigning pins to variables

const int contOne50 = 1;
const int contOne100 = 2;
const int contTwo50 = 3;
const int contTwo100 = 4;
const int contOneSensor = 5;
const int contTwoSensor = 6;
const int spillSensor = 7;
const int lineSensor = 8;
const int synthraSignal = 9;
const int valve1 = 10;
const int valve2 = 11;
const int valve3 = 12;
const int greenLED = 13;
const int yellowLED = 14;
const int redLED = 15;
const int blueLED = 16;

//All possible fill states

const int llll[] = {LOW, LOW, LOW, LOW};
const int hlll[] = {HIGH, LOW, LOW, LOW};
const int hhll[] = {HIGH, HIGH, LOW, LOW};
const int llhl[] = {LOW, LOW, HIGH, LOW};
const int llhh[] = {LOW, LOW, HIGH, HIGH};
const int hhhl[] = {HIGH, HIGH, HIGH, LOW};
const int hlhh[] = {HIGH, LOW, HIGH, HIGH};
const int hhhh[] = {HIGH, HIGH, HIGH, HIGH};
const int hlhl[] = {HIGH, LOW, HIGH, LOW};

//Function to compare arrays, used to compare level sensor output to possible fillstates
  
boolean array_cmp(int *a, int *b){
     int n;

     // test each element to be the same. if not, return false
     for (n=0;n<4;n++) if (a[n]!=b[n]) return false;

     //ok, if we have not returned yet, they are equal :)
     return true;
}

void set_latching_valve(){

  
  
  }

void setup() {
  // initializing the LEDs and valves as outputs
  pinMode(valve1, OUTPUT);
  pinMode(valve2, OUTPUT);
  pinMode(valve3, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  
  // initialize the sensors and synthra signal as inputs
  pinMode(contOne50, INPUT);
  pinMode(contOne100, INPUT);
  pinMode(contTwo50, INPUT);
  pinMode(contTwo100, INPUT);
  pinMode(contOneSensor, INPUT);
  pinMode(contOneSensor, INPUT);
  pinMode(spillSensor, INPUT);
  pinMode(lineSensor, INPUT);
  pinMode(valve1, INPUT);
  pinMode(valve2, INPUT);
  pinMode(valve3, INPUT);
  pinMode(synthraSignal, INPUT);
  
  Serial.begin(2400);

  //int spillState = digitalRead(spillSensor);
  int spillState = LOW;

  //int fillState[] = {digitalRead(contOne50), digitalRead(contOne100), digitalRead(contTwo50), digitalRead(contTwo100)};
  int fillState[] = {HIGH, LOW, HIGH, HIGH};

  //Check spill sensor
 
 if (spillState == HIGH) {
    //Go to ERROR state
    Serial.println("ERROR - LOSS OF CONTAINMENT");
    
  } else {

    Serial.println("NO SPILL");

    //Check for containers
    
    // if (digitalRead(contOneSensor) == HIGH && digitalRead(contTwoSensor) == HIGH) {
    if (true) {

      Serial.println("BOTH CONTAINERS PRESENT");

      //Check liquid levels

      if (array_cmp(fillState, llll)||array_cmp(fillState, hlhl)) {

          //Leave valve in original position

          //Wait for start signal

          Serial.println("Waiting for initiation...");
        
       } else if (array_cmp(fillState, hlll)|| array_cmp(fillState, llhh) || array_cmp(fillState, hlhh)){
          
           //Set valve to container 1

           Serial.println("SETTING VALVE TO CONT1");

           //Wait for start signal

           Serial.println("Waiting for initiation...");
          
        } else if (array_cmp(fillState, llhl) || array_cmp(fillState, hhll) || array_cmp(fillState, hhhl)){

           //Set valve to container 2

           Serial.println("SETTING VALVE TO CONT2");

           //Wait for start signal

           Serial.println("Waiting for initiation...");
            
        } else if (array_cmp(fillState, hhhh)) {

           //Full state

           Serial.println("BOTH CONTAINERS FULL");
      
        } else {

          //How?
          Serial.println ("ERROR - CHECK LEVEL SENSORS"); 
          
        }
        
    } else {

      //Go to ERROR state

      Serial.println("CONTAINERS NOT IN PLACE");
      
      }
    
  }
  
}

void loop() {

  // Wait for start signal
  
  while(digitalRead(synthraSignal) == LOW){}
    
  // Open both valves and wait 2 min for flow to start

  //Enter loop

    //Check Line Liquid Sensor
    
      //if LOW wait 5 min and close valves

      //if HIGH check liquid level sensors 

        //set latching valve position, if full then close valves and end on full message - red solid

        //check spill sensor, if HIGH close valves and end on error - blue light

        //check container sensors, if either is LOW close valves and end on error - red flashing
    
}
