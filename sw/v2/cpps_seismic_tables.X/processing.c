#include "processing.h"

//void PID_init(double kp, double ki, double kd)
//{
//    k1= kp + ki + kd;
//    k2=(-kp)?2*kd;
//    k3= kd;
//    // init u0
//    u=0;
//}

//void PID_exec()
//{
//    e2 = e1; // update error variables
//    e1 = e;
//
//    // Light sensor
//    // read variable from sensor
//
//    // setpoint comes from LUT with sine
//    e = setpoint ? y; // compute new error
//
//    delta_u = k1*e + k2*e1 + k3*e2; // PID algorithm
//
//    u = u + delta_u;
//    if (u > UMAX)
//    {
//        u = UMAX; // limit to DAC range
//    }
//    if(u < UMIN)
//    {
//        u = UMIN;
//    }
//
//    //PWM out
//    //send to DAC hardware
//}
