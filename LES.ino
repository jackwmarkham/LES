/*

*/

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

int contState = 0;
int spillState;
//int fillState[] = {0, 0, 0, 0}; 

boolean array_cmp(int *a, int *b){
     int n;

     // test each element to be the same. if not, return false
     for (n=0;n<4;n++) if (a[n]!=b[n]) return false;

     //ok, if we have not returned yet, they are equal :)
     return true;
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

  delay(5000);

  //int spillState = digitalRead(spillSensor);
  int spillState = LOW;

  //int fillState[] = {digitalRead(contOne50), digitalRead(contOne100), digitalRead(contTwo50), digitalRead(contTwo100)};
  int fillState[] = {LOW, LOW, LOW, LOW};

  int compState[] = {LOW, LOW, LOW, LOW};
 // int fillState[] = {HIGH, LOW, HIGH, HIGH};
 //Check spill sensor
 
 if (spillState == HIGH) {
    //Go to ERROR state
    Serial.println("ERROR");
    
  } else {

    Serial.println("NO SPILL");

    //Check for containers
    
    if (digitalRead(contOneSensor) == HIGH && digitalRead(contTwoSensor) == HIGH) {

      Serial.println("BOTH CONTAINERS PRESENT");

      //Check liquid levels

      if (array_cmp(fillState, compState)) {

          //Leave valve in original position

          //Wait for start signal

          Serial.println("Waiting for initiation...");
        
        // } else if (fillState == {HIGH, LOW, LOW, LOW} || fillState == {LOW, LOW, HIGH, HIGH} || fillState == {HIGH, LOW, HIGH HIGH}){
          
        //   //Set valve to container 1

        //   Serial.println("SETTING VALVE TO CONT1");

        //   //Wait for start signal

        //   Serial.println("Waiting for initiation...");
          
        //  } else if (fillState == {LOW, LOW, HIGH, LOW} || fillState == {HIGH, HIGH, LOW, LOW} || fillState == {HIGH, HIGH, HIGH, LOW} ){

        //   //Set valve to container 2

        //   Serial.println("SETTING VALVE TO CONT2");

        //   //Wait for start signal

        //   Serial.println("Waiting for initiation...");
            
        //    } else if (fillState == {HIGH, HIGH, HIGH, HIGH}) {

        //   //Full state

        //   Serial.println("BOTH CONTAINERS FULL");
      
         } else {

          //How?
          Serial.println ("ERROR"); 
          
         }
      

      
      
    } else {

      //Go to ERROR state

      Serial.println("CONTAINERS NOT IN PLACE");
      
      }
    
  }
  
}

void loop() {
    
}
