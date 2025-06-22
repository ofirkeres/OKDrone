/*
* pid.c
*
*  Created on: Jun 22, 2025
*      Author: ofirkeres
*/

/* Includes ------------------------------------------------------------------*/
#include "pid.h"
#include "utilities.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static pid_data_t pid;
/* Private function ----------------------------------------------------------*/

/**
 * @brief Initializes the PID Controllers constants.
 *
 * @param gains pointer to structure that holds the PID terms values
 * @param tau
 * @param output_limits
 * @param integral_limits
 */
void PIDController_Init(pid_gains_t* gains, float tau, thresholds_float_t* output_limits, thresholds_float_t* integral_limits)
{
    pid.Kp = gains->Kp;
    pid.Ki = gains->Ki;
    pid.Kd = gains->Kd;

    pid.tau = tau;

    pid.integrator = 0.0;
    pid.differentiator = 0.0;
    pid.prev_error = 0.0;
    pid.prev_measurement = 0.0;

    pid.output_thresholds.min = output_limits->min;
    pid.output_thresholds.max = output_limits->max;

    pid.integral_thresholds.min = integral_limits->min;
    pid.integral_thresholds.max = integral_limits->max;
}

/**
 * @brief
 *
 * @param set_point the desired set point/value
 * @param measurement the measurement from the sensors
 * @param time measurement time - in seconds
 * @return computed output signal.
 */
float PIDController_Compute(float set_point, float measurement, float time)
{
    float error, proportional, output;

    // Error signal
    error = set_point - measurement;

    // Proportional
    proportional = pid.Kp * error;

    // Integral
    pid.integrator += 0.5 * (pid.Ki * time * (error + pid.prev_error));
    pid.integrator = LIMIT(pid.integrator, pid.integral_thresholds.min, pid.integral_thresholds.max);

    // Derivative (band-limited differentiator)
    // Note: derivative on measurement, therefore minus sign in front of equation!
    pid.differentiator = -(2.0 * pid.Kd * (measurement - pid.prev_measurement))
                          + ((2.0 * pid.tau - time) * pid.differentiator)
                          / (2.0 * pid.tau + time);

    // Compute output signal and apply limits
    output = proportional + pid.integrator + pid.differentiator;
    output = LIMIT(output, pid.output_thresholds.min, pid.output_thresholds.max);

    // Store results for future calculations
    pid.prev_error = error;
    pid.prev_measurement = measurement;

    return output;
}
