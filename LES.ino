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
const int latchingValve = 12;
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
boolean array_comp(int *a, int *b){
     int n;

     // test each element to be the same. if not, return false
     for (n=0;n<4;n++) if (a[n]!=b[n]) return false;

     //ok, if we have not returned yet, they are equal :)
     return true;
}

void flashing(int light){
  digitalWrite(light, HIGH);
  delay(500); // Wait for 1000 millisecond(s)
  digitalWrite(light, LOW);
  delay(500); // Wait for 1000 millisecond(s)
}

void light_on(int light){
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(light, HIGH);
}

void set_lights(){
  //int fillState[] = {digitalRead(contOne50), digitalRead(contOne100), digitalRead(contTwo50), digitalRead(contTwo100)};
  int fillState[] = {HIGH, LOW, HIGH, HIGH};

  if (array_comp(fillState, llll)||array_comp(fillState, hlhl)) {

    light_on(greenLED);
  
  } else if (array_comp(fillState, llhh) || array_comp(fillState, hlhh) || array_comp(fillState, hhll)||array_comp(fillState, hhhl)){
    
    light_on(yellowLED);
    
  } else if (array_comp(fillState, hhhh)) {

    light_on(redLED);

  }  
}

void set_latching_valve(){
  //int fillState[] = {digitalRead(contOne50), digitalRead(contOne100), digitalRead(contTwo50), digitalRead(contTwo100)};
  int fillState[] = {HIGH, LOW, HIGH, HIGH};

  if (array_comp(fillState, llll)||array_comp(fillState, hlhl)) {

    //Leave valve in original position
  
  } else if (array_comp(fillState, hlll)|| array_comp(fillState, llhh) || array_comp(fillState, hlhh)){
    
    //Set valve to container 1
    Serial.println("SETTING VALVE TO CONT1");
    
  } else if (array_comp(fillState, llhl) || array_comp(fillState, hhll) || array_comp(fillState, hhhl)){

    //Set valve to container 2
    Serial.println("SETTING VALVE TO CONT2");
    
  } else if (array_comp(fillState, hhhh)) {

      //Full state
      Serial.println("BOTH CONTAINERS FULL");
      digitalWrite(valve1, LOW);
      digitalWrite(valve2, LOW);
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

void check_spill_sensor(){
  // if(digitalRead(spillSensor) == HIGH){
  if(false){
    Serial.println("ERROR - LOSS OF CONTAINMENT");
    digitalWrite(blueLED, HIGH);
    digitalWrite(valve1, LOW);
    digitalWrite(valve2, LOW);
    delay(1000);
    exit(0);
  }
}

void check_containers(){
  //if(digitalRead(contOneSensor) == LOW || digitalRead(contTwoSensor) == LOW){
  if(false){
    Serial.println("ERROR - CHECK CONTAINERS");
    digitalWrite(valve1, LOW);
    digitalWrite(valve2, LOW);
    while(true){
      flashing(redLED);
    }
  }
}

void setup() {
  // initializing the LEDs and valves as outputs
  pinMode(valve1, OUTPUT);
  pinMode(valve2, OUTPUT);
  pinMode(latchingValve, OUTPUT);
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
  pinMode(synthraSignal, INPUT);
  
  Serial.begin(2400);

  check_spill_sensor();

  Serial.println("NO SPILL");
  
  check_containers();

  Serial.println("CONTAINERS IN PLACE");

  set_latching_valve();
      
}

void loop() {

  // Wait for start signal
  Serial.println("Waiting for initation...");
  while(digitalRead(synthraSignal) == LOW){}
    
  // Open both valves and wait 2 min for flow to start
  digitalWrite(valve1, HIGH);
  digitalWrite(valve2, HIGH);
  delay(120000);

  while(digitalRead(lineSensor) == HIGH){
    set_lights();
    set_latching_valve();
    check_spill_sensor();
    check_containers();
    delay(60000);
  }
  
  // Wait 5 min and close valves
  delay(360000);
  digitalWrite(valve1, LOW);
  digitalWrite(valve2, LOW);
  Serial.println("Cleaning cycle complete");
  exit(0);
}