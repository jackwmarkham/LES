/**/const int contOne50 = 1;const int contOne100 = 2;const int contTwo50 = 3;const int contTwo100 = 4;const int contOneSensor = 5;const int contTwoSensor = 6;const int spillSensor = 7;const int lineSensor = 8;const int synthraSignal = 9;const int valve1 = 10;const int valve2 = 11;const int valve3 = 12;const int greenLED = 13;const int yellowLED = 14;const int redLED = 15;const int blueLED = 16;void LightOn (){  Serial.print("Turning led on:");  Serial.print("Red");}void setup() {  // initializing the LEDs and valves as outputs  pinMode(valve1, OUTPUT);  pinMode(valve2, OUTPUT);  pinMode(valve3, OUTPUT);  pinMode(greenLED, OUTPUT);  pinMode(yellowLED, OUTPUT);  pinMode(redLED, OUTPUT);  pinMode(blueLED, OUTPUT);    // initialize the sensors and synthra signal as inputs  pinMode(contOne50, INPUT);  pinMode(contOne100, INPUT);  pinMode(contTwo50, INPUT);  pinMode(contTwo100, INPUT);  pinMode(contOneSensor, INPUT);  pinMode(contOneSensor, INPUT);  pinMode(spillSensor, INPUT);  pinMode(lineSensor, INPUT);  pinMode(valve1, INPUT);  pinMode(valve2, INPUT);  pinMode(valve3, INPUT);  pinMode(synthraSignal, INPUT);    Serial.begin(9600);  LightOn();  }void loop() {    }