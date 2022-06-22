#include <stdio.h>
#include <stdlib.h>
#define FOSC 16000000U // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC / 16 / BAUD - 1
#define sc PD7
#define sv PB2
#define valvula PD6

char msg_tx[20];
char msg_rx[32];
int pos_msg_rx = 0;
int tamanho_msg_rx = 1;
unsigned int x = 0, valor = 0;
int potencia_enchimento = 25;

//Prototipos das funcoes
void UART_Init(unsigned int ubrr);
void UART_Transmit(char *dados);

int main(void)
{
  DDRD |= (1 << PD6);
  PORTD |= (1 << sc) | (1 << PD2);
  PORTB |=  (1 << sv);


  //TIMER PWM
  TCCR0A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
  TCCR0B |= (1 << CS00);

  //INTERRUPCAO EXTERNA
  EICRA = 0b00000010;
  EIMSK = 0b00000001;


  UART_Init(MYUBRR);
 
  sei();
  char sair = 0;
  while (1)
  {
    sair = 0;
     OCR0A = 0;

    if ((msg_rx[0] == 'L'))
    {
      UART_Transmit("Sistema Ligado\n");

      while (sair == 0) {
        if (!(PINB & (1 << sv))) {
          OCR0A = potencia_enchimento;
        } else if (PIND & (1 << sc)) {
          OCR0A = 0;
        }
        

        if ((msg_rx[0] == 'D')) {
          UART_Transmit("Sistema Desligado\n");
          msg_rx[0] = ' ';
          sair = true;
        }

        if ((msg_rx[0] == 'V')) {
          itoa(potencia_enchimento, msg_tx, 10);
          UART_Transmit(msg_tx);
          UART_Transmit("\n");
          msg_rx[0] = ' ';
        }

        msg_rx[0] = ' ';


      }

    }




  }
}


ISR(USART_RX_vect)
{
  // Escreve o valor recebido pela UART na posição pos_msg_rx do buffer msg_rx
  msg_rx[pos_msg_rx++] = UDR0;
  if (pos_msg_rx == tamanho_msg_rx)
    pos_msg_rx = 0;
}

void UART_Transmit(char *dados)
{
  // Envia todos os caracteres do buffer dados ate chegar um final de linha
  while (*dados != 0)
  {
    while (!(UCSR0A & (1 << UDRE0))); // Aguarda a transmissão acabar
    // Escreve o caractere no registro de tranmissão
    UDR0 = *dados;
    // Passa para o próximo caractere do buffer dados
    dados++;
  }
}

void UART_Init(unsigned int ubrr)
{
  // Configura a baud rate */
  UBRR0H = (unsigned char)(ubrr >> 8);
  UBRR0L = (unsigned char)ubrr;
  // Habilita a recepcao, tranmissao e interrupcao na recepcao */
  UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
  // Configura o formato da mensagem: 8 bits de dados e 1 bits de stop */
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

//INTERUPCAO EXTERNA
ISR(INT0_vect) {
  potencia_enchimento += 25;
  if (potencia_enchimento > 255) {
    UART_Transmit("Potencia Maxima");
    OCR0A = 255;
  }
  UART_Transmit("Aumentando o pwm\n");
  
  OCR0A = potencia_enchimento;
}
