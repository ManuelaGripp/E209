
ntmain(void) {
  DDRD = DDRD | 0b10000000;           // Pino PD7 definido como saída
  PORTD = PORTD | 0b00010000;       // Habilitar resistor de PULL-UP no PD4
  PORTD = PORTD & ~(0b10000000); // Desliga a saída PD7
  for (;;)
  {
    if ((PIND & 0b00010000) == 0)            // Botão pressionado?
    {
      PORTD = PORTD | 0b10000000;       // Aciona a saída
      _delay_ms(5000);
      PORTD = PORTD & ~(0b10000000); // Desliga a saída}}}
    }
  }
  //2) led nao acendeu ja que ele nao foi definido como saida



  /*3) Definimos PD2 como saida, habilitamos o pull-up do PD0, substitui a condição pelo PD0 e acionamos o PD2 para que o led2 acendesse
    int main(void) {
    DDRD = DDRD | 0b10000100;           // Pino PD7 e PD2 definidos como saída

    PORTD = PORTD | 0b00010001;       // Habilitar resistor de PULL-UP no PD4
    PORTD = PORTD & ~(0b10000100); // Desliga a saída PD7 e PD4

    for (;;)
    { if ((PIND & 0b00000001) == 0) // Botão pressionado?
      {
        PORTD = PORTD | 0b00000100;       // Aciona a saída
        _delay_ms(5000);
        PORTD = PORTD & ~(0b00000100); // Desliga a saída}}}
      }
    }
    }


    4) Adicionou bit 1 no PORTD na posiçao 7

    int main(void) {
    DDRD = DDRD | 0b10000100;           // Pino PD7 e PD2 definidos como saída

    PORTD = PORTD | 0b00010001;       // Habilitar resistor de PULL-UP no PD4
    PORTD = PORTD & ~(0b10000100); // Desliga a saída PD7 e PD4

    for (;;)
    { if ((PIND & 0b00000001) == 0) // Botão pressionado?
      {
        PORTD = PORTD | 0b10000100;       // Aciona a saída
        _delay_ms(5000);
        PORTD = PORTD & ~(0b10000100); // Desliga a saída}}}
      }
    }
    }

    5) Teoricamente os leds ficariam o tempo todo acesos

    6)

    int main(void) {
    DDRD = DDRD | 0b10000100;           // Pino PD7 e PD2 definidos como saída

    //PORTD = PORTD | 0b00010001;       // Habilitar resistor de PULL-UP no PD4
    PORTD = PORTD & ~(0b10000100); // Desliga a saída PD7 e PD4

    for (;;)
    {

      PORTD &=~(0b00000100); // desliga PD2
      PORTD |= 0b10000000; //liga -PD7
      _delay_ms(2000);
      PORTD &=~(0b10000000); // deliga PD7
      PORTD |= 0b00000100;
      _delay_ms(2000);


    }
    }

  */
