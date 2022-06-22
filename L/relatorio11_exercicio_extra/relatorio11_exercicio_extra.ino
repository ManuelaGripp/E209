int main()
{
  u16 adc_result0, adc_result1;
  ADC_init(); // Inicializa ADC

  while (1)
  {
    adc_result0 = ADC_read(ADC0D); // lê o valor do ADC0 = PC0
    adc_result1 = ADC_read(ADC1D); // lê o valor do ADC1 = PC1
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
