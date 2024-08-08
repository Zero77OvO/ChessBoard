#include "pid.h"


float Kp_x_x=0.5;    
float Ki_x_x=0.01;
float Kd_x_x=0.0;

float Kp_y_x=0.01; 
float Ki_y_x=0.001;
float Kd_y_x=0.001;


float Kp_x_v=2.0;  
float Ki_x_v=0.2;
float Kd_x_v=0.0;   


float Kp_y_v=0.0;  
float Ki_y_v=0.0;
float Kd_y_v=0.0;  

float Kp_turn=0.0;  
float Ki_turn=0.0;
float Kd_turn=0.0; 

float Kp_straight=0.0;  
float Ki_straight=0.0;
float Kd_straight=0.0; 

float err_x_v;     
float last_err_x_v ;
float err_sum_x_v ;
float err_difference_x_v;


float err_x_x;      
float last_err_x_x ;
float err_sum_x_x ;
float err_difference_x_x;



float err_y_v ;      
float last_err_y_v ;
float err_sum_y_v ;
float err_difference_y_v;

float err_y_x ;     
float last_err_y_x ;
float err_sum_y_x ;
float err_difference_y_x;

float err_turn ;     
float last_err_turn ;
float err_sum_turn ;
float err_difference_turn;

float err_straight ;     
float last_err_straight ;
float err_sum_straight ;
float err_difference_straight;


float X_v_out;    
float X_x_out;   

float Y_v_out;    
float Y_x_out;   


float Turn_out;  
float straight_out;  


float X_PID_V_value(float measure, float calcu)   
{
    err_x_v = measure - calcu;
    err_sum_x_v += err_x_v;
    // xianfu	
	  // if(err_sum_v > 1000)
		// err_sum_v = 1000;
	  // else if(err_sum_v < -1000)
		// err_sum_v = -1000;
    err_difference_x_v = err_x_v - last_err_x_v;
    X_v_out = Kp_x_v * err_x_v +Kd_x_v * (err_x_v - last_err_x_v)+ Ki_x_v*err_sum_x_v;
    last_err_x_v = err_x_v;

  // if(X_v_out<500){X_v_out=500;}
	// if(X_v_out>2500){X_v_out=2500;}

    return X_v_out;
}

float X_PID_X_value(float measure, float calcu)   
{
    err_x_x = measure - calcu;
    err_sum_x_x += err_x_x;
    // xianfu	
	  if(err_sum_x_x > 5)
		err_sum_x_x = 5;
	  else if(err_sum_x_x < -5)
		err_sum_x_x = -5;
	
    err_difference_x_x = err_x_x - last_err_x_x;
    X_x_out = Kp_x_x * err_x_x + Kd_x_x * (err_x_x - last_err_x_x)+ Ki_x_x*err_sum_x_x;

    last_err_x_x = err_x_x;
	
    // if(X_x_out-last_X_X>300||X_x_out-last_X_X<-200){ X_x_out=last_X_X;}
//  if(X_x_out<-500){X_x_out=-500;}
//	if(X_x_out>500){X_x_out=500;}


    return X_x_out;
}


float Y_PID_V_value(float measure, float calcu) 
{
    err_y_v = measure - calcu;
    err_sum_y_v += err_y_v;
    // xianfu

   
    err_difference_y_v = err_y_v - last_err_y_v;
    Y_v_out = Kp_y_v * err_y_v + Kd_y_v * (err_y_v - last_err_y_v)+ Ki_y_v*err_sum_y_v;;
    last_err_y_v = err_y_v;
	// if(Y_v_out<1000){Y_v_out=1000;}
	// if(Y_v_out>3000){Y_v_out=3000;}
	//HAL_Delay(10);
    return Y_v_out;
}

float Y_PID_X_value(float measure, float calcu)  
{
    err_y_x = measure - calcu;
    err_sum_y_x += err_y_x;
    // xianfu
     if(err_sum_y_x > 5)
		err_sum_y_x = 5;
	  else if(err_sum_y_x < -5)
		err_sum_y_x = -5;
		
		
    err_difference_y_x = err_y_x - last_err_y_x;
    Y_x_out = Kp_y_x * err_y_x + Kd_y_x * (err_y_x - last_err_y_x)+ Ki_y_x*err_sum_y_x;;
    last_err_y_x = err_y_x;
		
	// if(Y_x_out<-500){Y_x_out=-500;}
	// if(Y_x_out>500){Y_x_out=500;}
	//HAL_Delay(10);
    return Y_x_out;
}
//200x200

float PID_turn_value(float measure, float calcu)  
{
    err_turn = measure - calcu;
    err_sum_turn += err_turn;
    // xianfu
     if(err_sum_turn > 5)
		err_sum_turn= 5;
	  else if(err_sum_turn < -5)
		err_sum_turn = -5;
		
		
    err_difference_turn = err_turn - last_err_turn;
    Turn_out = Kp_turn * err_turn + Kd_turn * (err_turn - last_err_turn)+ Ki_turn*err_sum_turn;;
    last_err_turn = err_turn;
		
	// if(Turn_out<-500){Turn_out=-500;}
	// if(Turn_out>500){Turn_out=500;}
	//HAL_Delay(10);
    return Turn_out;
}




float PID_straight_value(float measure, float calcu)  
{
    err_straight = measure - calcu;
    err_sum_straight += err_straight;
    // xianfu
     if(err_sum_straight > 5)
		err_sum_straight= 5;
	  else if(err_sum_straight < -5)
		err_sum_straight = -5;
		
		
    err_difference_straight = err_straight - last_err_straight;
    straight_out = Kp_straight * err_straight + Kd_straight * (err_straight - last_err_straight)+ Ki_straight*err_sum_straight;;
    last_err_straight = err_straight;
		
	// if(Turn_out<-500){Turn_out=-500;}
	// if(Turn_out>500){Turn_out=500;}
	//HAL_Delay(10);
    return straight_out;
}


void LocationPID_change(int pid, float kp, float ki, float kd) {
  if(pid==1){Kp_x_x=kp;  Ki_x_x=ki;  Kd_x_x=kd;}
  if(pid==2){Kp_y_x=kp;  Ki_y_x=ki;  Kd_y_x=kd;}
  if(pid==3){Kp_x_v=kp;  Ki_x_v=ki;  Kd_x_v=kd;}
  if(pid==4){Kp_y_v=kp;  Ki_y_v=ki;  Kd_y_v=kd;}
  if(pid==5){Kp_turn=kp; Ki_turn=ki; Kd_turn=kd;}
  if(pid==6){Kp_straight=kp;Ki_straight=ki;Kd_straight=kd;}

}






void IncrementalPID_init(IncrementalPID *pid, float kp, float ki, float kd) {
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    

}

void IncrementalPID_change(IncrementalPID *pid, float kp, float ki, float kd) {
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    
}


float IncrementalPID_update(IncrementalPID *pid, float setpoint, float current_value) {
    pid->error = setpoint - current_value;
    
    // Proportional term
    float p_term = pid->kp * pid->error;
    
    // Integral term (with anti-windup)
    pid->integral += pid->error;
    float i_term = pid->ki * pid->integral;
	
    // if(i_term > 5)i_term = 5;else if(i_term < -5)i_term = -5;
    // Derivative term
    float d_term = pid->kd * (pid->error - pid->last_error);
    
    // PID output (incremental form)
    pid->pwm += p_term + i_term + d_term - pid->last_pwm;
    
    // Update for next iteration
    pid->last_error = pid->error;
    pid->last_pwm = pid->pwm;
	

	
    return pid->pwm;
}
