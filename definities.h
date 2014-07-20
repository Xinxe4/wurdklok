#define LED_COLS 15
#define LED_ROWS 8
#define NR_LEDS (LED_COLS * LED_ROWS)
#define INTERVAL 10
#define LOOP_CLOCK (60000 / INTERVAL)
#define LOOP_BRIGHTNESS (500 / INTERVAL)
#define LOOP_TEMPERATURE (1000 / INTERVAL)
#define LOOP_BLUETOOTH (20 / INTERVAL) //20 ms
#define LOOP_ALARM (10000 / INTERVAL) // Check alarm every 10 sec
#define FULL_AMBIENT_LIGHT 1 // Measurement of the photo resistor for maximum light
#define NO_AMBIENT_LIGHT 1024.0 // Measurement of the photo resistor for complete darkness


// Pinouts
#define PORT_STATUS_LED 3
#define PORT_MTX_DATA 11
#define PORT_MTX_CLK 13
#define PORT_MTX_LOAD 8
#define PORT_BT_RX 7
#define PORT_BT_TX 6

#define PORT_LIGHT_SENSOR A0

//#define PORT_I2C_A A4
//#define PORT_I2C_B A5

// Modes
static const int CLOCK_MODE = 1;
static const int DRAW_MODE = 2;
static const int TEMPERATURE_MODE = 3;

