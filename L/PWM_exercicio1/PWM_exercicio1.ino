#define pwm PD6
#define botao PD2

int brilho = 0;


ISR(INT0_vect){

  OCR0A = 179; 
}

int main(){

//PORTAS
DDRD |= (1 << pwm);
PORTD |= (1 << botao);

//Interrupcao
EICRA = 0;
EIMSK |= (1 << INT0);
sei();

//TIMER PWM
TCCR0A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
TCCR0B |= (1 << CS00);


while(1){
  OCR0A = 0;
}
  
}
