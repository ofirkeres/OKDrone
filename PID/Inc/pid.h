/*
* pid.h
*
*  Created on: Jun 22, 2025
*      Author: ofirkeres
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INC_OKDRONE_PID_H
#define INC_OKDRONE_PID_H

/* Includes ------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef struct pid_gains
{
    float Kp;
    float Ki;
    float Kd;
} pid_gains_t;

typedef struct pid_data
{
    float Kp;
    float Ki;
    float Kd;
    float tau;
    float integrator;
    float differentiator;
    float prev_error;
    float prev_measurement;
    thresholds_float_t output_thresholds;
    thresholds_float_t integral_thresholds;
} pid_data_t;

/* Exported constants --------------------------------------------------------*/
#define KP (0.0)
#define KI (0.0)
#define KD (0.0)
#define PID_TAU (0.02)
#define PID_INTEGRAL_MIN_THRESHOLD (-5.0)
#define PID_INTEGRAL_MAX_THRESHOLD (5.0)
/* Exported macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void PIDController_Init(pid_gains_t* gains, float tau, thresholds_float_t* output_limits, thresholds_float_t* integral_limits);
float PIDController_Compute(float set_point, float measurement, float time);

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function ----------------------------------------------------------*/

#endif /* INC_OKDRONE_PID_H */
