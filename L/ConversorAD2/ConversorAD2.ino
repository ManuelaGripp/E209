int main()
{
  TCCR0A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
  TCCR0B |= (1 << CS00);
  u16 adc_result0, adc_result1;
  float tensao;
  ADC_init(); // Inicializa ADC
  OCR0A = 0;
  DDRD |= (1 << PD6);
  Serial.begin(9600);
  while (1)
  {
    adc_result0 = ADC_read(ADC0D); // lê o valor do ADC0 = PC0
    //tensao = (adc_result0/1023.0)*255;
    tensao = 255-((adc_result0/1023.0)*255);
    Serial.println(tensao);
    OCR0A = tensao;   
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
