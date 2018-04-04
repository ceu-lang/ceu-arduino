#ifdef CEU_ISR__ADC_vect_num
ISR(ADC_vect)
{
    if (isrs[ADC_vect_num].fun != NULL) {
        isrs[ADC_vect_num].fun(isrs[ADC_vect_num].mem);
    }
}
#endif

#ifdef CEU_ISR__PCINT0_vect_num
ISR(PCINT0_vect)
{
    if (isrs[PCINT0_vect_num].fun != NULL) {
        isrs[PCINT0_vect_num].fun(isrs[PCINT0_vect_num].mem);
    }
}
#endif

#ifdef CEU_ISR__SPI_STC_vect_num
ISR(SPI_STC_vect)
{
    if (isrs[SPI_STC_vect_num].fun != NULL) {
        isrs[SPI_STC_vect_num].fun(isrs[SPI_STC_vect_num].mem);
    }
}
#endif

#ifdef CEU_ISR__TIMER1_COMPA_vect_num
ISR(TIMER1_COMPA_vect)
{
    if (isrs[TIMER1_COMPA_vect_num].fun != NULL) {
        isrs[TIMER1_COMPA_vect_num].fun(isrs[TIMER1_OVF_vect_num].mem);
    }
}
#endif

#ifdef CEU_ISR__TIMER1_OVF_vect_num
ISR(TIMER1_OVF_vect)
{
    if (isrs[TIMER1_OVF_vect_num].fun != NULL) {
        isrs[TIMER1_OVF_vect_num].fun(isrs[TIMER1_OVF_vect_num].mem);
    }
}
#endif

#ifdef CEU_ISR__USART_RX_vect_num
ISR(USART_RX_vect)
{
    if (isrs[USART_RX_vect_num].fun != NULL) {
        isrs[USART_RX_vect_num].fun(isrs[USART_RX_vect_num].mem);
    }
}
#endif

#ifdef CEU_ISR__USART0_RX_vect_num
ISR(USART0_RX_vect)
{
    if (isrs[USART0_RX_vect_num].fun != NULL) {
        isrs[USART0_RX_vect_num].fun(isrs[USART0_RX_vect_num].mem);
    }
}
#endif

#ifdef CEU_ISR__USART_TX_vect_num
ISR(USART_TX_vect)
{
    if (isrs[USART_TX_vect_num].fun != NULL) {
        isrs[USART_TX_vect_num].fun(isrs[USART_TX_vect_num].mem);
    }
}
#endif

#ifdef CEU_ISR__USART0_TX_vect_num
ISR(USART0_TX_vect)
{
    if (isrs[USART0_TX_vect_num].fun != NULL) {
        isrs[USART0_TX_vect_num].fun(isrs[USART0_TX_vect_num].mem);
    }
}
#endif

#ifdef CEU_ISR__WDT_vect_num
ISR (WDT_vect)
{
    if (isrs[WDT_vect_num].fun != NULL) {
        isrs[WDT_vect_num].fun(isrs[WDT_vect_num].mem);
    }
}
#endif

#ifdef CEU_ISR__TC3_IRQn
void TC3_Handler()
{
    if (isrs[TC3_IRQn].fun != NULL) {
        isrs[TC3_IRQn].fun(isrs[TC3_IRQn].mem);
    }
}
#endif

#ifdef CEU_ISR__TC4_IRQn
void TC4_Handler()
{
    if (isrs[TC4_IRQn].fun != NULL) {
        isrs[TC4_IRQn].fun(isrs[TC4_IRQn].mem);
    }
}
#endif

#ifdef CEU_ISR__ADC_IRQn
void ADC_Handler (void)
{
    if (isrs[ADC_IRQn].fun != NULL) {
        isrs[ADC_IRQn].fun(isrs[ADC_IRQn].mem);
    }
}
#endif

#ifdef CEU_ISR__SERCOM4_IRQn
void SERCOM4_Handler()
{
    if (isrs[SERCOM4_IRQn].fun != NULL) {
        isrs[SERCOM4_IRQn].fun(isrs[SERCOM4_IRQn].mem);
    }
}
#endif
