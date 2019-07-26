/*
全局变量
	float dt
		功能：积分时间 0.005=5ms
功能函数
	float Kalman_Filter(float _accelAngle, float GyroX)
	功能：使用卡曼滤波计算倾角
	输入参数：
		_accelAngle：
			功能：加速度计算出的角速度
		GyroX：
			功能：角速度
	输出参数：	
		滤波后的倾角	
*/

float K1 = 0.02;
float angle, angle_dot;
float Q_angle = 0.001; 
float Q_gyro = 0.003;  
float R_angle = 0.5;   
float dt = 0.005;	  // 积分时间 0.005=5ms
char C_0 = 1;
float Q_bias, Angle_err;
float PCt_0, PCt_1, E;
float K_0, K_1, t_0, t_1;
float Pdot[4] = {0, 0, 0, 0};
float PP[2][2] = {{1, 0}, {0, 1}};


float Kalman_Filter(float _accelAngle, float GyroX)
{
	GyroX /= 16.4;							 //单位换算
	angle += (GyroX - Q_bias) * dt;			 
	Pdot[0] = Q_angle - PP[0][1] - PP[1][0]; 

	Pdot[1] = -PP[1][1];
	Pdot[2] = -PP[1][1];
	Pdot[3] = Q_gyro;
	PP[0][0] += Pdot[0] * dt; 
	PP[0][1] += Pdot[1] * dt; 
	PP[1][0] += Pdot[2] * dt;
	PP[1][1] += Pdot[3] * dt;

	Angle_err = _accelAngle - angle; 

	PCt_0 = C_0 * PP[0][0];
	PCt_1 = C_0 * PP[1][0];

	E = R_angle + C_0 * PCt_0;

	K_0 = PCt_0 / E;
	K_1 = PCt_1 / E;

	t_0 = PCt_0;
	t_1 = C_0 * PP[0][1];

	PP[0][0] -= K_0 * t_0; //ºóÑé¹À¼ÆÎó²îÐ­·½²î
	PP[0][1] -= K_0 * t_1;
	PP[1][0] -= K_1 * t_0;
	PP[1][1] -= K_1 * t_1;

	angle += K_0 * Angle_err;   //ºóÑé¹À¼Æ
	Q_bias += K_1 * Angle_err;  //ºóÑé¹À¼Æ
	angle_dot = GyroX - Q_bias; //Êä³öÖµ(ºóÑé¹À¼Æ)µÄÎ¢·Ö=½ÇËÙ¶È
	return angle;
}

