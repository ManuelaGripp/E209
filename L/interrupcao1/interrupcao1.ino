ISR(INT0_vect){

  PORTD |= (1 << PD4);
  _delay_ms(1000);
  PORTD &= ~(1 << PD4);
  
  }

  ISR(INT1_vect){

  EIMSK ^= 0b00000001; 
  }

int main(void){

  DDRD = 0b00110000;
  PORTD = 0b00001100;
  EICRA = 0b00001011;
  EIMSK = 0b00000011;
  sei();

  while(1){

  PORTD ^= 0b00100000;
  _delay_ms(500);

  }

}
