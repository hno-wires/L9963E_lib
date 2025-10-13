#include "main.h"
#include "spi.h"

#include "stm32_if.h"

static L9963E_IF_PinState GPIO_ReadPin(L9963E_IF_PINS pin) {
    GPIO_PinState stm_state;
    switch (pin) {
        case L9963E_IF_CS:
            stm_state = HAL_GPIO_ReadPin(SPI1_CS_GPIO_Port, SPI1_CS_Pin);
            break;
        case L9963E_IF_TXEN:
            stm_state = HAL_GPIO_ReadPin(TXEN_GPIO_Port, TXEN_Pin);
            break;
        case L9963E_IF_BNE:
            stm_state = HAL_GPIO_ReadPin(BNE_GPIO_Port, BNE_Pin);
            break;
        case L9963E_IF_ISOFREQ:
            stm_state = HAL_GPIO_ReadPin(ISOFREQ_GPIO_Port, ISOFREQ_Pin);
            break;
        case L9963E_IF_DIS:
            stm_state = HAL_GPIO_ReadPin(DIS_GPIO_Port, DIS_Pin);
            break;
    }

    return stm_state == GPIO_PIN_RESET ? L9963E_IF_GPIO_PIN_RESET : L9963E_IF_GPIO_PIN_SET;  //convert lib state to stm state
}
static L9963E_StatusTypeDef GPIO_WritePin(L9963E_IF_PINS pin, L9963E_IF_PinState state) {
    GPIO_PinState stm_state = state == L9963E_IF_GPIO_PIN_RESET ? GPIO_PIN_RESET
                                                                : GPIO_PIN_SET;  //convert lib state to stm state
    switch (pin) {
        case L9963E_IF_CS:
            HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, stm_state);
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
}
static L9963E_StatusTypeDef SPI_Receive(uint8_t *data, uint8_t size, uint8_t timeout_ms) {
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
}
static L9963E_StatusTypeDef SPI_Transmit(uint8_t *data, uint8_t size, uint8_t timeout_ms) {
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
}
static uint32_t GetTickMs(void) {
    return HAL_GetTick();
}
static void DelayMs(uint32_t delay) {
    HAL_Delay(delay);
}

const L9963E_IfTypeDef L9963E_if_stm32 = {
    .L9963E_IF_GPIO_ReadPin = GPIO_ReadPin,
    .L9963E_IF_GPIO_WritePin = GPIO_WritePin,
    .L9963E_IF_SPI_Receive = SPI_Receive,
    .L9963E_IF_SPI_Transmit = SPI_Transmit,
    .L9963E_IF_GetTickMs = GetTickMs,
    .L9963E_IF_DelayMs = DelayMs
};
