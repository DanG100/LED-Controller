

void setup() 
{ 
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT); 
  Serial.println("started");
}

void loop() 
{ 
  if (Serial.available() > 0)
  {
      Serial.readString();
      Serial.println("bitch");
      delay(2000);
  }

  else
  {
    //Serial.println("not available");
    delay(1000);
  }

}