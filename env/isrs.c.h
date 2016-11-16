#ifdef CEU_ISR__TIMER1_COMPA_vect_num
ISR(TIMER1_COMPA_vect)
{
    if (isrs[TIMER1_COMPA_vect_num] != NULL) {
        isrs[TIMER1_COMPA_vect_num]();
    }
}
#endif

#ifdef CEU_ISR__TIMER1_OVF_vect_num
ISR(TIMER1_OVF_vect)
{
    if (isrs[TIMER1_OVF_vect_num] != NULL) {
        isrs[TIMER1_OVF_vect_num]();
    }
}
#endif

#ifdef CEU_ISR__USART_RX_vect_num
ISR(USART_RX_vect)
{
    if (isrs[USART_RX_vect_num] != NULL) {
        isrs[USART_RX_vect_num]();
    }
}
#endif

#ifdef CEU_ISR__USART_TX_vect_num
ISR(USART_TX_vect)
{
    if (isrs[USART_TX_vect_num] != NULL) {
        isrs[USART_TX_vect_num]();
    }
}
#endif
