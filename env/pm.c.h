#ifndef CEU_PM
#define ceu_pm_set(a,b)
#else

#define CEU_PM_STATE(peripheral) bitRead(ceu_pm_state, peripheral)
#define ceu_pm_set(a,b) ceu_pm_set_(a,b)

#ifdef __cplusplus
extern "C" {
#endif

static u32 ceu_pm_state = 0;        // up to 32 peripherals

void ceu_pm_sleep (void);

void ceu_pm_set (u8 peripheral, bool state) {
    bitWrite(ceu_pm_state, peripheral, state);
}

#ifdef __cplusplus
}
#endif

#endif
