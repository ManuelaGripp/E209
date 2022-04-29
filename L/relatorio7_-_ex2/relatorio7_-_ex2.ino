
int main(void){

  DDRD = 0b00010011; //PD0  e PD1 como saida
  PORTD = 0b00001100; // Pull-up ligado PD2(max) PD3(min)


  while(1){

  if(!(PIND & (1 << PD3)) && (PIND & (1 << PD2))){
    PORTD &= ~(1 << PD1); // Desliga led cheio
    PORTD |= (1 << PD0); // Liga led enchendo
    PORTD |= (1 << PD4); // Liga valvula
  }else if(!(PIND & (1 << PD2))){
    PORTD &= ~(1 << PD0); // Desliga led enchendo 
    PORTD &= ~(1 << PD4); // Desliga valvula
    PORTD |= (1 << PD1); // Liga led cheio
  }

  }
}
