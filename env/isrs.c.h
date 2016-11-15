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
