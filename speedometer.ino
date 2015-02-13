/*
  Speedometer
     To serve as a speedometer for any vehicle 
     with round wheels, given a specific circumference.
  
  Screen Info:
    1) Runs on +5 VDC (Voltage Direct Current)
    
  Pin setup:
    +     =>  +5V   \
    -     =>  GND    > Hall effect sensor
    A0    =>  A0    /
    
    D0    =>  2     \ Seven segment display
    GND   =>  GND   /     (first digit)
    
    D0    =>  3     \ Seven segment display
    GND   =>  GND   /     (second digit)
  
  by Rocky Quinn
*/
//HE_IN -> input from hall effect sensor
#define HE_IN 0

// CIRCUMFERENCE is a constant that keeps track of the circumference of a tire
float CIRCUMFERENCE;
// previousInput is the last input received from the hall effect sensor
int previousInput;
// timer is used to time out one second at a time
int timer;
//rate is used to keep track of how many times the magnet has done a full revolution
int rate;

/*
  Setup is the start up code. Only runs once.
*/
void setup()
{
  Serial.begin(9600);
  while(!Serial){;}
  
  CIRCUMFERENCE = (3.1415926535 * 31 * (1/63360));
  previousInput = 512;
  timer = 0;
  rate = 45;
}

/*
  Loop is the code that's going to run over and over until:
    - The arduino is turned off
    - The arduino is reset
    - The arduino crashes
*/
void loop()
{
  timer++;
  measure_magnet();
  if(timer == 10000)
    calc_speed();
}

/*
  measure_magnet uses the hall effect sensor to determine when a
  magnet has rotated around the wheel once.
  
  local vars:
    - raw = input from hall effect sensor
*/
void measure_magnet()
{
  int raw = analogRead(HE_IN);  //Range: 0 -> 1024
  if( ( (raw-previousInput) < (-100)  ||  (raw-previousInput) > 100 ) &&
         raw < 412  ||  raw > 612 )
  {
    Serial.println("Rate increased.");
    rate++;
  }
  previousInput = raw;
  //Serial.println("Raw reading: "+(String)raw);
}

/*
  calc_speed gets called every second and uses rate and circumference to 
  determine the speed of the wheel.
  
  local vars:
    - spd = speed in miles per hour (mph)
*/
void calc_speed()
{
  //Serial.println("calc_speed() called");
  int spd = (int)(rate * CIRCUMFERENCE * 3600);
  Serial.println(spd);
  timer = 0;
}
