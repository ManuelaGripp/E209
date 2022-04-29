#define LED PB2
#define BOTAO1 PD1 //temperatura
#define BOTAO2 PD2 //pressao
#define BOTAO3 PD3 //nivel
#define BOTAO4 PD4 //peso


int main(void) {

  DDRB = 0b00000100;
  DDRD = 0;
  PORTD = 0b00011110;


  while (1) {
    if (!(PIND & 0b00001110)) {
      PORTB |= (1 << LED);
    } else if (!(PIND & 0b00010010 )){
      PORTB |= (1 << LED);
    } else if(!(PIND & 0b00000100)){
      PORTB |= (1 << LED);
    }
    else if (!( PIND & 0b00000010 )){
      PORTB |= (1 << LED);
    } else{
      PORTB &= ~(1 << LED);
    }
    
    
  }

}
