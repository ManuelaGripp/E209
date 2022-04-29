#define led PD7
#define led_ PD6
int contVerm = 0;
int contVerd = 0;



ISR(TIMER0_OVF_vect)
{
  contVerm++;
  contVerd ++;

  if(contVerd >=3676){
     PORTD |= (1 << led_);
    _delay_ms(100);
    PORTD &= ~(1 << led_);
    contVerd = 0;
  }

  if (contVerm >= 61) {
    PORTD |= (1 << led);
    _delay_ms(100);
    PORTD &= ~(1 << led);
    contVerm = 0;
  }
}

void ConfigTimer0(void)
{
  TCCR0B |= (1 << CS02) | (1 << CS00); //clock/1024
  TCCR0A |= 0;
  TIMSK0 |= (1 << TOIE0);
}


int main(void) {

  DDRD = (1 << led) | (1 << led_);
  ConfigTimer0();
  sei();
  while (1) {

  }


}
