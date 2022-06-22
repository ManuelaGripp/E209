#include <stdio.h>
#include <stdlib.h>
#define FOSC 16000000U // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC / 16 / BAUD - 1

char msg_tx[20];
char msg_rx[32];
int pos_msg_rx = 0;
int tamanho_msg_rx = 3;
unsigned int x = 0, valor = 0;

//Prototipos das funcoes
void UART_Init(unsigned int ubrr);
void UART_Transmit(char *dados);

int main(void)
{
  UART_Init(MYUBRR);
  sei();

  DDRD |= (1 << PD6);
  TCCR0A|=(1<<WGM01)|(1<<WGM00)|(1<<COM0A1);
  TCCR0B=1;//Selecionaopçãoparafrequência
  OCR0A=0;

  x = 0;
  valor = 0;
  //valor = 8
  while (1)
  {
    valor = ((msg_rx[0] - 48) * 100 +
    (msg_rx[1] - 48) * 10 +
    (msg_rx[2] - 48) * 1);

  OCR0A = (valor * 255)/100;
  int valor1 = (valor * 255)/100;
  itoa(OCR0A, msg_tx, 10);
  UART_Transmit(msg_tx);
  UART_Transmit("\n");
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
