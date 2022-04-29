#define LED1 PB1
#define LED2 PB2
#define LED3 PB3

#define BOTAO1 PD1 
#define BOTAO2 PD2
#define BOTAO3 PD3 


int main(void) {

  DDRB = 00001110;
  DDRD = 0;
  PORTD = 00001110;
  
  while (1) {

  if(!(PIND & 0b00001110)){
    
    PORTB |= 0b00001000;
    PORTB &= ~(0b00000110);

    } else if(!( PIND & 0b00000110)){
      
      PORTB |= 0b00000110;
      PORTB &= ~(0b00001000);
      
    } else if(!(PIND & 0b00001100)){
      
      PORTB |= 0b00001000;
      PORTB &= ~(0b00000110);
      
    } else if(!(PIND & 0b00001010)){
      
      PORTB |= 0b00001000;
      PORTB &= ~(0b00000110);

    } else if (!(PIND & 0b00001000)){
      PORTB |= 0b00001000;
      PORTB &= ~(0b00000110);
      
    } else if (!(PIND & 0b00000100)){
      PORTB |= 0b00000100;
      PORTB &= ~(0b00001010);

    } else if(!(PIND & 0b0000010)){
      PORTB |= 0b00000010;
      PORTB &= ~(0b00001100);
      
    }
      
  }
  
}
