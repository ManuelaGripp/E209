
//Hélio Abreu Marques Rocha 1763
//Manuela Gripp Silva 1689

// Variáveis para entrada e saída
char RX_buffer[32];
char RX_index = 0;

// Buffer para estado anterior do RX
char old_rx_hs[32];

// A inicialização do UART consiste em definir a taxa de transmissão,
// definir o formato de quadro, e ativar o Transmissor ou o receptor.

// Função de configuração do UART
void UART_init(int baud)
{
  // Calcula a taxa de transmissão
  int MYUBRR = 16000000 / 16 / baud - 1;

  // Definindo a taxa de transmissão
  UBRR0H = (unsigned char)(MYUBRR >> 8);
  UBRR0L = (unsigned char)(MYUBRR);

  // Definindo o formato de quadro, 8 bits e 1 stop bit
  UCSR0C = (0 << USBS0) | (1 << UCSZ00) | (1 << UCSZ01);

  // Ativa o Transmissor, receptor e define a interrupção
  UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
}

// Função para envio de dados via UART
void UART_send(char *TX_buffer)
{
  // Enquanto tiver caracteres para enviar
  while (*TX_buffer != 0)
  {
    // Prepara o buffer para o envio
    UDR0 = *TX_buffer;

    // Espera o envio ser completado
    while (!(UCSR0A & (1 << UDRE0))) {};

    // Avança o ponteiro do buffer
    TX_buffer++;
  }
}

// Limpa o buffer de entrada e saída
void limpa_RX_buffer(void)
{
  unsigned char dummy;

  // Enquanto houver dados no buffer
  while (UCSR0A & (1 << RXC0))
  {
    // Lê o dado
    dummy = UDR0;
  }

  // Reseta o índice
  RX_index = 0;

  // Limpa todos os dados do buffer
  for (int i = 0; i < 32; i++)
  {
    old_rx_hs[i] = RX_buffer[i];
    RX_buffer[i] = 0;
  }
}

// Função ISR que salva um array de dados recebidos via UART
ISR(USART_RX_vect)
{
  // Salva o dado recebido
  RX_buffer[RX_index] = UDR0;
  RX_buffer[RX_index + 1] = 0;

  // Adiciona mais 1 na contagem
  RX_index++;
}

int brilho = 0;
int cont = 0;

ISR(INT0_vect) {

  brilho += 25;// Aumenta o brilho do led em 10%
  if (brilho > 255) {
    brilho = 0;
  }

  OCR2B = brilho;
}

ISR(TIMER1_OVF_vect) {//366 ciclo de 1.5s
  cont++;
  if ( cont >= 366 ) {
    brilho -= 25;
    cont = 0;
    OCR2B = brilho;
  }

  if (brilho <= 0) {
    TIMSK1 = 0 ; //Desabilita o timer
  }


}

int main()
{

  DDRD = (1 << PD3); //LED PWM 
  PORTD = (1 << PD2);//Botao de interrupcao


  //TIMER
  TCCR1B |= (1 << CS10); //PreScaler 1


  //PWM
  TCCR2A |= (1 << COM2B1) | (1 << WGM01) | (1 << WGM00) ; //FastPWM
  TCCR2B |= (1 << CS00);//Sem PreScaler

  //INTERRUPCAO
  EICRA |= (1 << ISC01);
  EIMSK |= (1 << INT0);

  //ADC
  u16 adc_result0, adc_result1;
  ADC_init(); // Inicializa ADC
  UART_init(9600);
  sei();
  char msg_tx[20];
  int temp = 0;
  int res = 0;
  char estadoSistema;
  OCR2B = 0;

  while (1)
  {

    estadoSistema = 0;
    _delay_ms(500);

    if (RX_buffer[0] == 'L' || RX_buffer[0] == 49) {
      estadoSistema = 1;
      TIMSK1 = 0; //Desliga o timer
      UART_send("SISTEMA LIGADO \n");
      limpa_RX_buffer();
    }

    while (estadoSistema) {
      adc_result0 = ADC_read(ADC0D); // lê o valor do ADC0 = PC0
      res = (adc_result0 / 1023.0) * 255; //convertendo para a faixa de [0,255]
      temp = ((10 * res) / 255) - 40; //convertendo para a faixa de [-40, -30]
      UART_send("TEMPERATURA: ");
      itoa(temp, msg_tx, 10);//Convertendo para string
      UART_send(msg_tx);//Mostrando no serial
      UART_send("C ");
      UART_send("\n");
      //_delay_ms(1000);

      if (RX_buffer[0] == 'D' || RX_buffer[0] == 48 ) {
        estadoSistema = 0;
        UART_send("SISTEMA DESLIGADO\n");
        TIMSK1 |= (1 << TOIE1); //Ligando o timer para delisgamento do led
        limpa_RX_buffer();
      }
      limpa_RX_buffer();
    }
  }

}

void ADC_init(void)
{
  ADMUX = (1 << REFS0);
  ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

int ADC_read(u8 ch)
{
  char i;
  int ADC_temp = 0;
  int ADC_read = 0;

  ch &= 0x07;
  ADMUX = (ADMUX & 0xF8) | ch;
  ADCSRA |= (1 << ADSC);
  while (!(ADCSRA & (1 << ADIF)));

  for (i = 0; i < 8; i++)
  {
    ADCSRA |= (1 << ADSC);
    while (!(ADCSRA & (1 << ADIF)));
    ADC_temp = ADCL;
    ADC_temp += (ADCH << 8);
    ADC_read += ADC_temp;
  }
  ADC_read = ADC_read >> 3;
  return ADC_read;
}
