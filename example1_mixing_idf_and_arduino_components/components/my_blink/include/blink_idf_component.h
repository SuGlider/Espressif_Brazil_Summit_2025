#ifndef BLINK_IDF_H
#define BLINK_IDF_H

// the component header may be used in C or C++ files
#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_BLINK_LED_STRIP
void blink_led(uint8_t red, uint8_t green, uint8_t blue);
#else
void blink_led(void); // for simple GPIO LED
#endif
void configure_led(void);

#ifdef __cplusplus
}
#endif

#endif // BLINK_IDF_H
