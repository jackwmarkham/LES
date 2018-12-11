//Assigning pins to variables, pin 1 left blank to prevent issues with flashing software
const int contOne50 = 2;
const int contOne100 = 3;
const int contTwo50 = 4;
const int contTwo100 = 5;
const int contOneSensor = 6;
const int contTwoSensor = 7;
const int spillSensor = 22;
const int lineSensor = 8;
const int synthraSignal = 9;
const int valve1 = 52;
const int valve2 = 50;
const int latchingValvePower = 48;
const int latchingValveSelect = 46;
const int greenLED = 44;
const int yellowLED = 42;
const int redLED = 40;
const int blueLED = 38;

//All possible fill states, follow the format {contOne50, contOne100, contTwo50, contTwo100}
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
boolean array_comp(int *a, const int *b){
     int n;

     // test each element to be the same. if not, return false
     for (n=0;n<4;n++) if (a[n]!=b[n]) return false;

     //ok, if we have not returned yet, they are equal :)
     return true;
}

//Function to flash a given LED
void flashing(int light){
  digitalWrite(light, HIGH);
  delay(500);
  digitalWrite(light, LOW);
  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, LOW);
  delay(500); 
}

//Function to turn a given LED on
void light_on(int light){
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(light, HIGH);
}

//Function to check sensors and power the correct indicator lights
void set_lights(){
  int fillState[] = {digitalRead(contOne50), digitalRead(contOne100), digitalRead(contTwo50), digitalRead(contTwo100)};

  if (array_comp(fillState, llll)||array_comp(fillState, hlhl)||array_comp(fillState, llhl)) {

    light_on(greenLED);
  
  } else if (array_comp(fillState, llhh) || array_comp(fillState, hlhh) || array_comp(fillState, hhll)||array_comp(fillState, hhhl)){
    
    light_on(yellowLED);
    
  } else if (array_comp(fillState, hhhh)) {

    light_on(redLED);

  }  
}

//Function to set the latching valve to the correct position
void set_latching_valve(int container){

  if (container == 1){
    digitalWrite(latchingValveSelect, LOW);
    digitalWrite(latchingValvePower, HIGH);
    delay(1000);
    digitalWrite(latchingValvePower, LOW);
  } else if (container == 2){
    digitalWrite(latchingValveSelect, HIGH);
    delay(100);
    digitalWrite(latchingValvePower, HIGH);
    delay(1000);
    digitalWrite(latchingValvePower, LOW);
    delay(100);
    digitalWrite(latchingValveSelect, LOW);
  } else {
    Serial.println("ERROR WITH LATCHING VALVE SETTING");
    delay(1000);
    exit(0);
  }
}

//Function to check sensors and determine the correct position for the latching valve
void select_container(){
  int fillState[] = {digitalRead(contOne50), digitalRead(contOne100), digitalRead(contTwo50), digitalRead(contTwo100)};

  if (array_comp(fillState, llll)||array_comp(fillState, hlhl)) {

    //Leave valve in original position
  
  } else if (array_comp(fillState, hlll)|| array_comp(fillState, llhh) || array_comp(fillState, hlhh)){
    
    //Set valve to container 1
    Serial.println("SETTING VALVE TO CONT1");
    set_latching_valve(1);
    
  } else if (array_comp(fillState, llhl) || array_comp(fillState, hhll) || array_comp(fillState, hhhl)){

    //Set valve to container 2
    Serial.println("SETTING VALVE TO CONT2");
    set_latching_valve(2);
    
  } else if (array_comp(fillState, hhhh)) {

      //Full state
      Serial.println("BOTH CONTAINERS FULL");
      digitalWrite(valve1, LOW);
      digitalWrite(valve2, LOW);
      delay(1000);
      exit(0);

  } else {

    Serial.println ("ERROR - CHECK LEVEL SENSORS"); 
    digitalWrite(valve1, LOW);
    digitalWrite(valve2, LOW);
    while(true){
      flashing(redLED);
    } 
  }
  
}

//Function to check the spill sensor for loss of liquid containment
void check_spill_sensor(){
  if(digitalRead(spillSensor) == HIGH){
    Serial.println("ERROR - LOSS OF CONTAINMENT");
    light_on(blueLED);
    digitalWrite(valve1, LOW);
    digitalWrite(valve2, LOW);
    delay(1000);
    exit(0);
  }
}

//Function to check if containers are properly in place
void check_containers(){
  if(digitalRead(contOneSensor) == LOW || digitalRead(contTwoSensor) == LOW){
    Serial.println("ERROR - CHECK CONTAINERS");
    digitalWrite(valve1, LOW);
    digitalWrite(valve2, LOW);
    while(true){
      flashing(redLED);
    }
  }
}

//Debugging function that returns the values of all sensor inputs
void sensor_check(){
  Serial.println("contOne50 =");
  Serial.println(digitalRead(contOne50));
  Serial.println("contOne100 =");
  Serial.println(digitalRead(contOne100));
  Serial.println("contTwo50 =");
  Serial.println(digitalRead(contTwo50));
  Serial.println("contTwo100 =");
  Serial.println(digitalRead(contTwo100));
  Serial.println("contOneSensor =");
  Serial.println(digitalRead(contOneSensor));
  Serial.println("contTwoSensor =");
  Serial.println(digitalRead(contTwoSensor));
  Serial.println("spillSensor =");
  Serial.println(digitalRead(spillSensor));
  Serial.println("lineSensor =");
  Serial.println(digitalRead(lineSensor));
}

void setup() {

  //Initializing the LEDs and valves as outputs
  
  pinMode(valve1, OUTPUT);
  pinMode(valve2, OUTPUT);
  pinMode(latchingValvePower, OUTPUT);
  pinMode(latchingValveSelect, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  
  //Initialize the sensors and synthra signal as inputs
  pinMode(contOne50, INPUT);
  pinMode(contOne100, INPUT);
  pinMode(contTwo50, INPUT);
  pinMode(contTwo100, INPUT);
  pinMode(contOneSensor, INPUT);
  pinMode(contOneSensor, INPUT);
  pinMode(spillSensor, INPUT);
  pinMode(lineSensor, INPUT);
  pinMode(synthraSignal, INPUT);
  
  Serial.begin(2400);

  delay(1000);

  sensor_check();

  check_spill_sensor();

  Serial.println("NO SPILL");
  
  check_containers();

  Serial.println("CONTAINERS IN PLACE");

  set_lights();

  select_container();
      
}

void loop() {

  // digitalWrite(valve1, HIGH);
  // delay(5000);
  // digitalWrite(valve2, HIGH);
  // delay(5000);

  // Wait for start signal
  Serial.println("Waiting for initation...");
  while(digitalRead(synthraSignal) != HIGH){}


  // digitalWrite(latchingValvePower, HIGH);
  // Serial.println("1");
  // delay(5000);
  // digitalWrite(latchingValveSelect, HIGH);
  // Serial.println("2");
  // delay(5000);
  // digitalWrite(latchingValvePower, LOW);
  // Serial.println("3");
  // delay(5000);
  // digitalWrite(latchingValveSelect, LOW);
  // Serial.println("4");
    
  // Open both valves and wait 1 min for flow to start
  Serial.println("Transfer initiated");
  digitalWrite(valve1, HIGH);
  digitalWrite(valve2, HIGH);
  check_spill_sensor();
  check_containers();
  //delay(60000);
  delay(15000);



  while(digitalRead(lineSensor) != LOW){
    set_lights();
    select_container();
    check_spill_sensor();
    check_containers();
    //delay(60000);
    delay(5000);
  }
  
  // Wait 5 min and close valves
  Serial.println("Transfer shutdown commencing");
  //delay(360000);
  delay(5000);
  digitalWrite(valve1, LOW);
  digitalWrite(valve2, LOW);
  Serial.println("Transfer complete");
  delay(1000);
  exit(0);
}
