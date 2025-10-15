#include <stddef.h>
#include <assert.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>

#include "linux_if.h"

#define CHECK_RC(rc) \
    if (rc != 0) assert_perror(errno);

static const struct timeval start_time;

static const char *gpio_pin_names[] = {
	[L9963E_IF_CS] = NULL,
	[L9963E_IF_TXEN] = NULL,
	[L9963E_IF_BNE] = NULL,
	[L9963E_IF_ISOFREQ] = NULL,
	[L9963E_IF_DIS] = NULL
};

static struct gpio_pin {
	struct gpiod_chip *chip;
	struct gpiod_line *line;
} gpio_pin[sizeof(gpio_pin_names)/sizeof(gpio_pin_names[0])];

static L9963E_IF_PinState GPIO_ReadPin(L9963E_IF_PINS pin) {
#if 0
    L9963E_IF_PinState state;
    switch (pin) {
        case L9963E_IF_CS:
            state = HAL_GPIO_ReadPin(SPI1_CS_Pin);
            break;
        case L9963E_IF_TXEN:
            state = HAL_GPIO_ReadPin(TXEN_Pin);
            break;
        case L9963E_IF_BNE:
            state = HAL_GPIO_ReadPin(BNE_Pin);
            break;
        case L9963E_IF_ISOFREQ:
            state = HAL_GPIO_ReadPin(ISOFREQ_Pin);
            break;
        case L9963E_IF_DIS:
            state = HAL_GPIO_ReadPin(DIS_Pin);
            break;
    }

    return state == L9963E_IF_GPIO_PIN_RESET ? GPIO_PIN_RESET : GPIO_PIN_SET;  //convert lib state to stm state
#endif
}

static L9963E_StatusTypeDef GPIO_WritePin(L9963E_IF_PINS pin, L9963E_IF_PinState pin_state) {
#if 0
    bool stm_state = state == L9963E_IF_GPIO_PIN_RESET ? GPIO_PIN_RESET
                                                                : GPIO_PIN_SET;  //convert lib state to stm state
    switch (pin) {
        case L9963E_IF_CS:
            HAL_GPIO_WritePin(SPI1_CS_Pin, stm_state);
            break;
        case L9963E_IF_TXEN:
            HAL_GPIO_WritePin(TXEN_GPIO_Port, TXEN_Pin, stm_state);
            break;
        case L9963E_IF_BNE:
            HAL_GPIO_WritePin(BNE_GPIO_Port, BNE_Pin, stm_state);
            break;
        case L9963E_IF_ISOFREQ:
            HAL_GPIO_WritePin(ISOFREQ_GPIO_Port, ISOFREQ_Pin, stm_state);
            break;
        case L9963E_IF_DIS:
            HAL_GPIO_WritePin(DIS_GPIO_Port, DIS_Pin, stm_state);
            break;
        default:
            return L9963E_ERROR;
    }
    return L9963E_OK;
#endif
}

static L9963E_StatusTypeDef SPI_Receive(uint8_t *data, uint8_t size, uint8_t timeout_ms) {
#if 0
    HAL_StatusTypeDef errorcode;

    errorcode = HAL_SPI_Receive(&hspi1, data, size, timeout_ms);

    switch (errorcode) {
        case HAL_OK:
            return L9963E_OK;
        case HAL_TIMEOUT:
            return L9963E_TIMEOUT;
        default:
            return L9963E_ERROR;
    }
#endif
}

static L9963E_StatusTypeDef SPI_Transmit(uint8_t *data, uint8_t size, uint8_t timeout_ms) {
#if 0
    HAL_StatusTypeDef errorcode;

    errorcode = HAL_SPI_Transmit(&hspi1, data, size, timeout_ms);

    switch (errorcode) {
        case HAL_OK:
            return L9963E_OK;
        case HAL_TIMEOUT:
            return L9963E_TIMEOUT;
        default:
            return L9963E_ERROR;
    }
#endif
}

static uint32_t GetTickMs(void) {
    struct timeval now,tv;
    int rc;

    CHECK_RC(gettimeofday(&now, NULL));

    timersub(&now, &start_time, &tv);

    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

static void DelayMs(uint32_t delay) {
    usleep(delay * 1000);
}

const L9963E_IfTypeDef L9963E_if_linux = {
    .L9963E_IF_GPIO_ReadPin = GPIO_ReadPin,
    .L9963E_IF_GPIO_WritePin = GPIO_WritePin,
    .L9963E_IF_SPI_Receive = SPI_Receive,
    .L9963E_IF_SPI_Transmit = SPI_Transmit,
    .L9963E_IF_GetTickMs = GetTickMs,
    .L9963E_IF_DelayMs = DelayMs
};

