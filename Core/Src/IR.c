#include "IR.h"
//front right
static void ADC1_Select_CH4(void){
	ADC_ChannelConfTypeDef sConfig = {0};

    sConfig.Channel = ADC_CHANNEL_4;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_7CYCLES_5;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
    	Error_Handler();
    }
}

//front left
static void ADC1_Select_CH9(void){
    ADC_ChannelConfTypeDef sConfig = {0};

    sConfig.Channel = ADC_CHANNEL_9;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_7CYCLES_5;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
}

//side right
static void ADC1_Select_CH5(void){
    ADC_ChannelConfTypeDef sConfig = {0};

    sConfig.Channel = ADC_CHANNEL_5;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_7CYCLES_5;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
}

//side left
static void ADC1_Select_CH8(void){
    ADC_ChannelConfTypeDef sConfig = {0};

    sConfig.Channel = ADC_CHANNEL_8;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_7CYCLES_5;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
}

float measure_dist(dist_t dist){
	GPIO_TypeDef* emitter_port;
	uint16_t emitter_pin;
	GPIO_TypeDef* receiver_port;
	uint16_t receiver_pin;

	float slope = 0.0;
	float intercept = 0.0;

	HAL_ADC_Stop(&hadc1);

	switch(dist){
	    case DIST_FL:
	    	emitter_port = EMIT_FL_GPIO_Port;
	    	emitter_pin = EMIT_FL_Pin;
	    	receiver_port = RECIV_FL_GPIO_Port;
	    	receiver_pin = RECIV_FL_Pin;
	    	ADC1_Select_CH9();
	    	slope = FL_SLOPE;
	    	intercept = FL_INTERCEPT;
	    	break;
	    case DIST_FR:
	    	emitter_port = EMIT_FR_GPIO_Port;
	    	emitter_pin = EMIT_FR_Pin;
	    	receiver_port = RECIV_FR_GPIO_Port;
	    	receiver_pin = RECIV_FR_Pin;
	    	ADC1_Select_CH4();
	    	slope = FR_SLOPE;
	    	intercept = FR_INTERCEPT;
	    	break;
	    case DIST_SL:
	    	emitter_port = EMIT_SL_GPIO_Port;
			emitter_pin = EMIT_SL_Pin;
			receiver_port = RECIV_SL_GPIO_Port;
			receiver_pin = RECIV_SL_Pin;
			ADC1_Select_CH8();
			slope = SL_SLOPE;
			intercept = SL_INTERCEPT;
			break;
	    case DIST_SR:
			emitter_port = EMIT_SR_GPIO_Port;
			emitter_pin = EMIT_SR_Pin;
			receiver_port = RECIV_SR_GPIO_Port;
			receiver_pin = RECIV_SR_Pin;
			ADC1_Select_CH5();
			slope = SR_SLOPE;
			intercept = SR_INTERCEPT;
			break;
	    default:
	    	break;
	}
	HAL_GPIO_WritePin(emitter_port, emitter_pin, GPIO_PIN_SET);
	//HAL_Delay(5);

	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	uint16_t adc_val = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);

	float dis_m = (adc_val-intercept)/slope;

	HAL_GPIO_WritePin(emitter_port, emitter_pin, GPIO_PIN_RESET);

	return dis_m;
	//return (float)adc_val;
}

