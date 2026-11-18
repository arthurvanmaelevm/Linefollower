// ================================
// TB6612FNG Proof of Concept
// ESP32 DevKit V1
// ================================

// Motor A (links)
#define PWMA 23
#define AIN1 22
#define AIN2 21

// Motor B (rechts)
#define PWMB 19
#define BIN1 18
#define BIN2 17

// Standby
#define STBY 16

// PWM instellingen ESP32
const int freq = 5000;
const int resolution = 8;

const int channelA = 0;
const int channelB = 1;

void setup()
{
  Serial.begin(115200);

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  pinMode(STBY, OUTPUT);

  // PWM kanalen configureren
  ledcAttachChannel(PWMA, freq, resolution, channelA);
  ledcAttachChannel(PWMB, freq, resolution, channelB);

  // H-brug activeren
  digitalWrite(STBY, HIGH);

  Serial.println("TB6612 Proof of Concept gestart");
}

void loop()
{
  // ==================
  // Test 1
  // Linker motor vooruit
  // ==================
  Serial.println("Motor links vooruit 50%");

  motorLinks(128);
  motorRechts(0);

  delay(3000);

  // ==================
  // Test 2
  // Linker motor achteruit
  // ==================
  Serial.println("Motor links achteruit 50%");

  motorLinks(-128);
  motorRechts(0);

  delay(3000);

  // ==================
  // Test 3
  // Rechter motor vooruit
  // ==================
  Serial.println("Motor rechts vooruit 50%");

  motorLinks(0);
  motorRechts(128);

  delay(3000);

  // ==================
  // Test 4
  // Rechter motor achteruit
  // ==================
  Serial.println("Motor rechts achteruit 50%");

  motorLinks(0);
  motorRechts(-128);

  delay(3000);

  // ==================
  // Test 5
  // Beide motoren 25%
  // ==================
  Serial.println("Beide motoren 25%");

  motorLinks(64);
  motorRechts(64);

  delay(3000);

  // ==================
  // Test 6
  // Beide motoren 50%
  // ==================
  Serial.println("Beide motoren 50%");

  motorLinks(128);
  motorRechts(128);

  delay(3000);

  // ==================
  // Test 7
  // Beide motoren 100%
  // ==================
  Serial.println("Beide motoren 100%");

  motorLinks(255);
  motorRechts(255);

  delay(3000);

  // ==================
  // Test 8
  // Onafhankelijke sturing
  // ==================
  Serial.println("Links 30%, rechts 80%");

  motorLinks(77);
  motorRechts(204);

  delay(5000);

  stopMotoren();

  Serial.println("Testcyclus afgelopen");
  delay(5000);
}

void motorLinks(int snelheid)
{
  if (snelheid > 0)
  {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    ledcWrite(PWMA, snelheid);
  }
  else if (snelheid < 0)
  {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    ledcWrite(PWMA, abs(snelheid));
  }
  else
  {
    ledcWrite(PWMA, 0);
  }
}

void motorRechts(int snelheid)
{
  if (snelheid > 0)
  {
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    ledcWrite(PWMB, snelheid);
  }
  else if (snelheid < 0)
  {
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    ledcWrite(PWMB, abs(snelheid));
  }
  else
  {
    ledcWrite(PWMB, 0);
  }
}

void stopMotoren()
{
  ledcWrite(PWMA, 0);
  ledcWrite(PWMB, 0);
}