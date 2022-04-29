int main(void){

  DDRD = 0b00000011; //PD0(MA)  e PD1(MF) como saida
  PORTD = 0b00011100; // Pull-up ligado PD4(SF) PD3(SA)
  EICRA = 0b00000010; // Transiçao de descida
  EIMSK = 0b00000001; // Ligando a interrupcao

  sei();


  while(1){

  int cont = 0;
   char estado;
  if( !(PIND & (1<< PD3)) && !(PIND & (1 << PD2))){
    PORTD &= ~(1 << PD0);// Desliga MA
    PORTD |= (1 << PD1);// Liga MF
    estado = PORTD;
  } else if(!(PIND & (1<< PD4)) && !(PIND & (1 << PD2))){
    PORTD &= ~(1 << PD1);// Desliga MF
    PORTD |= (1 << PD0);// Liga MA
    estado = PORTD;
  }else if(!(PIND & (1<< PD2))){
    if(cont % 2 == 0){
      PORTD = 0;
    } else{
      estado ^= 0b00000011;
      PORTD = estado;
    }

    cont++;
  }
  if(!(PIND & (1 << PD3))){
    PORTD &= ~(1 << PD0);// Desliga MA
    PORTD |= (1 << PD1);// Liga MF
    estado = PORTD;
  }else if(!( PIND & (1<< PD4))){
    PORTD &= ~(1 << PD1);// Desliga MF
    PORTD |= (1 << PD0);// Liga MA
    estado = PORTD;

  } 
  }
}
