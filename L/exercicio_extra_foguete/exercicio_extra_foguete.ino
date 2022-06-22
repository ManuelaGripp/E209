ISR(PCINT0_vect)
{
  if (!(PINB & (1 << PB0))) {
    PORTD ^= (1 << PD7);
    _delay_ms(1000);
    PORTD ^= (1 << PD7);
  }

  if (!(PINB & (1 << PB2))) {

    PORTD ^= (1 << PD6);
    _delay_ms(500);
    PORTD ^= (1 << PD6);

  }

}
// Na interrupção PCINT2
ISR(PCINT2_vect)
{
  PORTB ^= (1 << PB1);
  _delay_ms(2000);
  PORTB ^= (1 << PB1);

}
int main(void)
{
  DDRD = 0b11100000;
  DDRB = 0b00000010;
  PORTB |= (1 << PB0) | (1 << PB2);
  PORTD |= (1 << PD4);


  // Habilita interrupção no grupo PCINT0, PCINT2
  PCICR |= 0b00000101;
  // Habilita PCINT no  pino PB0 -> PCINT0 , pino PB2 -> PCINT2, pino PD4 -> PCINT20
  PCMSK0 |= 0b00000101;
  PCMSK2 |= 0b00010000;
  // Habilita Interrupções globais
  sei();
  for (;;)
  {
    PORTD ^= (1 << PD7);
    _delay_ms(250);
    PORTD ^= (1 << PD7);
  }
}
