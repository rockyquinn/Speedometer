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

// currentTime & newTime is used to time out the interval of a magnet passing
unsigned long lastTime, newTime;
// DIAMETER is the diameter of the tire
float DIAMETER;
// CIRCUMFERENCE is a constant that keeps track of the circumference of a tire
float CIRCUMFERENCE;
// previousInput is the last input received from the hall effect sensor
int previousInput;
// spd is used to keep track of the current speed
int spd;

/*
  Setup is the start up code. Only runs once.
*/
void setup()
{
  Serial.begin(9600);
  while(!Serial){;}
  
  DIAMETER = 31;
  CIRCUMFERENCE = (3.1415926535 * DIAMETER / 63360);
  previousInput = 512;
  spd = 00;
  lastTime = millis();
  newTime = lastTime;
  
  Serial.println("testing variables...");
  Serial.print("Circumference = ");Serial.println(CIRCUMFERENCE);
  Serial.print("lastTime = ");Serial.println(lastTime);
  Serial.print("newTime = ");Serial.println(newTime);
  Serial.println("Testing complete!\n");
}

/*
  Loop is the code that's going to run over and over until:
    - The arduino is turned off
    - The arduino is reset
    - The arduino crashes
*/
void loop()
{
  measure_magnet();
  update_display(spd);
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
    Serial.println(" increased.");
    newTime = millis();
    calc_speed();
  }
  previousInput = raw;
}


/*
  calc_speed gets called every second and uses  and circumference to 
  determine the speed of the wheel.
*/
void calc_speed()
{
  if(newTime != lastTime)
  {
    Serial.println("Testing calc_speed()...");
    Serial.print("spd = ");Serial.println( (CIRCUMFERENCE/( (newTime-lastTime)*3600000 )) );
    spd = ( (int)(CIRCUMFERENCE/( (newTime-lastTime)*3600000 )) );
    Serial.print("spd = ");Serial.println(spd);
    Serial.println("Testing complete!\n");
  
    if(spd > 99)
      spd = 99;
    else if(spd < 0)
      spd = 101;
  }
  return;
}


/*
  display used to show speed or error code
 
  parameters:
    - val = value to display 
    
  local vars:
    - d1 = first digit of val (Tens place)
    - d2 = second digit of val (Ones place)
*/
void update_display(int val)
{
  //Display 00-99 for speeds
  //Display EE for time error         (val==100)
  //Display E1 for calc_speed errors  (val==101)
  int d1 = val/10;
  int d2 = val%10;
}
