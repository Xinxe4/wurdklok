#define LED_COLS 15
#define LED_ROWS 10
#define NR_LEDS (LED_COLS * LED_ROWS)
#define INTERVAL 10
#define LOOP_CLOCK (60000 / INTERVAL)
#define LOOP_BRIGHTNESS (500 / INTERVAL)
#define LOOP_CLOCK (200 / INTERVAL)
#define LOOP_BLUETOOTH (20 / INTERVAL) //20 ms
#define LOOP_ALARM (10000 / INTERVAL) // Check alarm every 10 sec

// Pinouts
#define STATUS_LED 2
