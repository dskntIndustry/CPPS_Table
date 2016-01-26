/* 
 * File:   processing.h
 * Author: uadmin
 *
 * Created on 18. janvier 2016, 09:25
 */

#ifndef PROCESSING_H
#define	PROCESSING_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "config.h"

double e, e1, e2, u, delta_u, y;
double k1, k2, k3, kp, ki, kd;
double setpoint, u;

void PID_init(void);
void PID_exec(void);


#ifdef	__cplusplus
}
#endif

#endif	/* PROCESSING_H */

