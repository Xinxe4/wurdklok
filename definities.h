#define LED_COLS 15
#define LED_ROWS 10
#define NR_LEDS (LED_COLS * LED_ROWS)
#define INTERVAL 10
#define LOOP_CLOCK (60000 / INTERVAL)
#define LOOP_BRIGHTNESS (500 / INTERVAL)
#define LOOP_CLOCK (200 / INTERVAL)
#define LOOP_BLUETOOTH (20 / INTERVAL) //20 ms
#define LOOP_ALARM (10000 / INTERVAL) // Check alarm every 10 sec
#define FULL_AMBIENT_LIGHT 0 // Measurement of the photo resistor for maximum light
#define NO_AMBIENT_LIGHT 1000.0 // Measurement of the photo resistor for complete darkness


// Pinouts
#define PORT_STATUS_LED 2
#define PORT_SRSE_1 11
#define PORT_SRSE_2 00000000000
#define PORT_SROE 2
#define PORT_SRCL 12
#define PORT_SRLA 8
#define PORT_BT_RX 7
#define PORT_BT_TX 6
