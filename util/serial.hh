#ifndef _SERIAL_HH
#define _SERIAL_HH
int  serial_if        (void);
int  serial_available (void);
void serial_begin     (int speed);
void serial_end       (void);
void serial_write     (const uint8_t* buf, size_t len);
int  serial_read 	  (void);
#endif
