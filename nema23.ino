#define step_pin 7
#define dir_pin 8
#define en_pin 9

#define pushButton1_pin 5
#define pushButton2_pin 6

int _pbL = 0;
int _pbR = 0;

void setup() {
  //Output pin
  Serial.begin(9600);
  pinMode(step_pin, OUTPUT);
  pinMode(dir_pin, OUTPUT);
  pinMode(en_pin, OUTPUT);

  //Input pin
  pinMode(pushButton1_pin, INPUT);
  pinMode(pushButton2_pin, INPUT);

  //set Enable output to LOW
  //digitalWrite(en_pin, HIGH);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  _pbL = digitalRead(pushButton1_pin);
  _pbR = digitalRead(pushButton2_pin);
  
  Serial.println("PBL = " + String(_pbL) + " PBR = " + String(_pbR));
  
  
  
 /*
  setPositionDirection(_pbL, _pbR);
  delay(1000);

  setCurrentPostion(_pbL, _pbR);
  delay(1000);
  */
  if(_pbL == 1)
  {
    digitalWrite(dir_pin, LOW);
    setStep();
  }
  else if(_pbR == 1)
  {
    digitalWrite(dir_pin, HIGH);
    setStep();
  } 

  delay(100);
}

/*because we use 200 steps of servo motor,
 *200 steps means motor spins 360 degree or 1.8 degree each step
 *to obtain 180 degree we need 100 steps which is 90 degree to the left 
 *and 90 degrees to the right therefore we only need to count to 50 for each side
 */
void setStep()
{
  for(int i=0; i<50; i++)
  {
    digitalWrite(step_pin, HIGH);
    delay(1);
    digitalWrite(step_pin, LOW);
    delay(1);   
  }   
}

void setPositionDirection(int x, int y)
{
  if(x == 1 && y == 0)
  {
    digitalWrite(en_pin, HIGH);
    digitalWrite(dir_pin, HIGH);
    setStep();
  } 
  else if(x == 0 && y == 1)
  {
    digitalWrite(en_pin, HIGH);
    digitalWrite(dir_pin, LOW);
    setStep();
  }  
  else
    digitalWrite(en_pin, LOW);
}

/*
 * Hold in the current position 
 * when the push button L or R is holding
 * and back to the default position if neither L nor R is hold
 */
void setCurrentPosition(int x, int y)
{
  if(x == 1)
  {
    while(x)
    {
      digitalWrite(en_pin, LOW);
      delay(1000);
    }
    if(x == 0)
    {
      digitalWrite(en_pin, HIGH);
      digitalWrite(dir_pin, LOW);
      setStep();
    }
  }
  else if(y == 1)
  {
    while(y)
    {
      digitalWrite(en_pin, LOW);
      delay(1000);
    }
    if(y == 0)
    {
      digitalWrite(en_pin, HIGH);
      digitalWrite(dir_pin, HIGH);
      setStep();
    }
  }
}
