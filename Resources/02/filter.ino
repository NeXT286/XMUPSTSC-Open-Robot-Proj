float K1 = 0.02;
float angle, angle_dot;
float Q_angle = 0.001; // ¹ý³ÌÔëÉùµÄÐ­·½²î
float Q_gyro = 0.003;  //0.003 ¹ý³ÌÔëÉùµÄÐ­·½²î ¹ý³ÌÔëÉùµÄÐ­·½²îÎªÒ»¸öÒ»ÐÐÁ½ÁÐ¾ØÕó
float R_angle = 0.5;   // ²âÁ¿ÔëÉùµÄÐ­·½²î ¼È²âÁ¿Æ«²î
float dt = 0.005;	  // Î¢·ÖÊ±¼ä(¼ì²âÊ±¼ä£¬0.005=5ms)
char C_0 = 1;
float Q_bias, Angle_err;
float PCt_0, PCt_1, E;
float K_0, K_1, t_0, t_1;
float Pdot[4] = {0, 0, 0, 0};
float PP[2][2] = {{1, 0}, {0, 1}};

void FilterInit(float AccelAngle)
{
	angle = AccelAngle;
}
/**************************************************************************
º¯Êý¹¦ÄÜ£º¼òÒ×¿¨¶ûÂüÂË²¨
Èë¿Ú²ÎÊý£ºÍ¨¹ý¼ÓËÙ¶È¼ÆËã³öµÄ¸©Ñö½Ç¡¢½ÇËÙ¶È
·µ»Ø  Öµ£ºÎÞ
**************************************************************************/
float Kalman_Filter(float _accelAngle, float GyroX)
{
	GyroX /= 16.4;							 //³ýÒÔ16.4ÓÃÀ´×ª»»ÍÓÂÝÒÇÁ¿³Ì
	angle += (GyroX - Q_bias) * dt;			 //ÏÈÑé¹À¼Æ
	Pdot[0] = Q_angle - PP[0][1] - PP[1][0]; // Pk-ÏÈÑé¹À¼ÆÎó²îÐ­·½²îµÄÎ¢·Ö

	Pdot[1] = -PP[1][1];
	Pdot[2] = -PP[1][1];
	Pdot[3] = Q_gyro;
	PP[0][0] += Pdot[0] * dt; // Pk-ÏÈÑé¹À¼ÆÎó²îÐ­·½²îÎ¢·ÖµÄ»ý·Ö
	PP[0][1] += Pdot[1] * dt; // =ÏÈÑé¹À¼ÆÎó²îÐ­·½²î
	PP[1][0] += Pdot[2] * dt;
	PP[1][1] += Pdot[3] * dt;

	Angle_err = _accelAngle - angle; //zk-ÏÈÑé¹À¼Æ

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

