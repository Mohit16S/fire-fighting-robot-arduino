

const int flamePin = 2;
const int smokePin = A0;
const int tempPin  = A1;

const int relayPin = 7;

const int IN1 = 8;
const int IN2 = 9;
const int IN3 = 10;
const int IN4 = 11;


// -------- THRESHOLD VALUES --------

int smokeLimit = 400;
int tempLimit  = 150;



void setup()
{
  Serial.begin(9600);

  pinMode(flamePin, INPUT);
  pinMode(relayPin, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  digitalWrite(relayPin, HIGH);   // pump OFF

  stopRobot();

  Serial.println("Fire Robot Started");
}




void forward()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void leftTurn()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void rightTurn()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopRobot()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}




void pumpON()
{
  digitalWrite(relayPin, LOW);
  Serial.println("Pump ON");
}

void pumpOFF()
{
  digitalWrite(relayPin, HIGH);
  Serial.println("Pump OFF");
}



int readFlame()
{
  return digitalRead(flamePin);
}

int readSmoke()
{
  return analogRead(smokePin);
}

int readTemp()
{
  return analogRead(tempPin);
}




bool fireDetected()
{
  int flame = readFlame();
  int smoke = readSmoke();
  int temp  = readTemp();

  Serial.print("Flame: ");
  Serial.println(flame);

  Serial.print("Smoke: ");
  Serial.println(smoke);

  Serial.print("Temp: ");
  Serial.println(temp);

  if (flame == LOW)
    return true;

  if (smoke > smokeLimit)
    return true;

  if (temp > tempLimit)
    return true;

  return false;
}




void searchFire()
{
  Serial.println("Searching Fire");

  forward();
  delay(800);

  leftTurn();
  delay(400);

  rightTurn();
  delay(400);

  stopRobot();
}




void extinguishFire()
{
  Serial.println("Fire Detected");

  forward();
  delay(1500);

  stopRobot();

  pumpON();
  delay(5000);

  pumpOFF();
}




void loop()
{
  if (fireDetected())
  {
    extinguishFire();
  }
  else
  {
    searchFire();
  }

  delay(200);
}