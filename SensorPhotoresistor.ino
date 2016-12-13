
int LDRValor =0;
int LDRPin = 0;

void setup() {
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(7,INPUT_PULLUP);

  pinMode(4,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  
  int estadoBotao;
  estadoBotao = digitalRead(7);

  LDRValor = analogRead(LDRPin);

  if(LDRValor >300){
    digitalWrite(4,HIGH);  
  }
  else{
    digitalWrite(4,LOW);
  }

  Serial.println(LDRValor);
  delay(100);
  
  digitalWrite(10,estadoBotao);
  digitalWrite(9,!estadoBotao);

}
