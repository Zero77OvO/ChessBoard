 #ifndef _PID_H
 #define _PID_H



float X_PID_V_value(float measure, float calcu);
float X_PID_X_value(float measure, float calcu);
float Y_PID_V_value(float measure, float calcu);
float Y_PID_X_value(float measure, float calcu);

float PID_turn_value(float measure, float calcu);
float PID_straight_value(float measure, float calcu);
 
void LocationPID_change(int pid, float kp, float ki, float kd);



typedef struct {
    float kp;
    float ki;
    float kd;
    
    float pwm;
    float last_pwm;
    float error;
    float last_error;
    float integral;
} IncrementalPID;


void IncrementalPID_init(IncrementalPID *pid, float kp, float ki, float kd);
void IncrementalPID_change(IncrementalPID *pid, float kp, float ki, float kd) ;
float IncrementalPID_update(IncrementalPID *pid, float setpoint, float current_value);






extern float Kp_x_x;    
extern float Ki_x_x;
extern float Kd_x_x;

extern float Kp_y_x; 
extern float Ki_y_x;
extern float Kd_y_x;


extern float Kp_x_v;  
extern float Ki_x_v;
extern float Kd_x_v;   


extern float Kp_y_v;  
extern float Ki_y_v;
extern float Kd_y_v;  



extern float err_x_v;     
extern float last_err_x_v ;
extern float err_sum_x_v ;
extern float err_difference_x_v;


extern float err_x_x;      
extern float last_err_x_x ;
extern float err_sum_x_x ;
extern float err_difference_x_x;



extern float err_y_v ;      
extern float last_err_y_v ;
extern float err_sum_y_v ;
extern float err_difference_y_v;

extern float err_y_x ;     
extern float last_err_y_x ;
extern float err_sum_y_x ;
extern float err_difference_y_x;



extern float X_v_out;    
extern float X_x_out;   

extern float Y_v_out;    
extern float Y_x_out; 


 #endif
