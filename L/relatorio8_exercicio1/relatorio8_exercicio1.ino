#define led PD7
int cont = 0;

ISR(TIMER0_OVF_vect)
{
  cont++;

  if (cont >= 9) {
    PORTD ^= (1 << led);
    cont = 0;
  }

}

void ConfigTimer0(void)
{
  TCCR0B |= (1 << CS02) | (1 << CS00); //clock/1024
  TCCR0A |= 0;
  TIMSK0 |= (1 << TOIE0);
}


int main(void) {

  DDRD = (1 << led);
  ConfigTimer0();
  sei();
  while (1) {

  }


}
