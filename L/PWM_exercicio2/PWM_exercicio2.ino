#define pwm PD6
#define botao PD2

int brilho = 0;



ISR(INT0_vect) {
  brilho += 38;
  if (brilho > 254) {
    brilho = 0;
  }
  OCR0A = brilho;
  Serial.println(brilho);
  //_delay_ms(1000);
}

int main() {

Serial.begin(9600);
  //PORTAS
  DDRD |= (1 << pwm);
  PORTD |= (1 << botao);

  //Interrupcao
  EICRA |= (1 << ISC01);
  EIMSK |= (1 << INT0);
  sei();

  //TIMER PWM
  TCCR0A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
  TCCR0B |= (1 << CS00);
  OCR0A = 0;

  while (1) {

  }

}
