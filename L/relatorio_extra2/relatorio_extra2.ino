#define farol PD6
#define motor PD3
#define porta PD4

boolean ctr = true;

ISR(INT0_vect) {

  ctr = !ctr;
}

int main(void) {

  DDRD = 0b00100000;
  PORTD = 0b00011110;
  EICRA |= (1 << ISC01);//habilita descida
  EIMSK |= (1 << INT0);//habilita int0
  sei();


  while (1) {
    if (ctr) {
      while(!(PIND &= (1 << farol)) && (PIND &= (motor << 1))) {
        PORTD |= (1 << PD5);
      } 
      while ( !(PIND &= (1 << porta))) {
        PORTD |= (1 << PD5);
      }
      while( (PIND &= (1 << porta)) && !(PIND &= (1 << motor))) {
        PORTD |= (1 << PD5);
      }
      PORTD &= ~(1 << PD5);
    } else{
      PORTD &= ~(1 << PD5);
    }
  }
}
