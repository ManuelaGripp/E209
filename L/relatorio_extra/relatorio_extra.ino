
//12s -> 735
//3s -> 184
//15s -> 919

int cont = 0;
int ctr = 0;

ISR(TIMER0_OVF_vect) {
  cont++;
  if (ctr == 0) {
    if (cont > 735) {
      PORTD &= ~(1 << PD5);
      PORTD |= (1 << PD4);
      ctr++;
      cont = 0;
    }
  } else if (ctr == 1) {
    if (cont > 184) {
      PORTD &= ~(1 << PD4);
      PORTD |= (1 << PD3);
      ctr++;
      cont = 0;
    }
  } else if (ctr == 2) {
    if (cont > 919) {
      PORTD &= ~(1 << PD3);
      PORTD |= (1 << PD5);
      ctr = 0;
      cont = 0;
    }
  }
}
int main(void) {

  DDRD = 0b000111000;
  PORTD |= (1 << PD5);
  TCCR0A = 0;
  TCCR0B |= (1 << CS02) | (1 << CS00);
  TIMSK0 |= (1 << TOIE0);
  sei();
  while (1) {

  }

}
