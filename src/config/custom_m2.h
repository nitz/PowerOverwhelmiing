#pragma once

/** SPI configurations, used for MicroSD Card on the Dock */
// Pins are defined in nrf52840_m2.h
#define APP_SDCARD_SPI_INSTANCE			0

/** SPI configurations, used for ILI9341 TFT controller */
#define ILI9341_SCK_PIN					NRF_GPIO_PIN_MAP(0, 21)
#define ILI9341_MISO_PIN				NRF_GPIO_PIN_MAP(0, 24)
#define ILI9341_MOSI_PIN				NRF_GPIO_PIN_MAP(0, 4)
#define ILI9341_SS_PIN					NRF_GPIO_PIN_MAP(0, 26)
#define ILI9341_DC_PIN					NRF_GPIO_PIN_MAP(0, 20)
#define ILI9341_RESET_PIN				NRF_GPIO_PIN_MAP(0, 27)
#define ILI9341_BACKLIGHT_CONTROL_PIN	NRF_GPIO_PIN_MAP(0, 23)
#define ILI9341_HEIGHT					320
#define ILI9341_WIDTH					240
#define ILI9341_SPI_INSTANCE			3

/** GPIO configurations, used for user input */
#define INPUT_BUTTON_UP_PIN				NRF_GPIO_PIN_MAP(1, 7)
#define INPUT_BUTTON_DOWN_PIN			NRF_GPIO_PIN_MAP(1, 4)
#define INPUT_BUTTON_LEFT_PIN			NRF_GPIO_PIN_MAP(1, 3)
#define INPUT_BUTTON_RIGHT_PIN			NRF_GPIO_PIN_MAP(1, 2)
#define INPUT_BUTTON_CENTER_PIN			NRF_GPIO_PIN_MAP(1, 1)
#define INPUT_BUTTON_EX1_PIN			NRF_GPIO_PIN_MAP(1, 0)
#define INPUT_BUTTON_EX2_PIN			0xFF // none

/** UART configurations, used for logging */
#define NRF_LOG_BACKEND_UART_TX_PIN		16
