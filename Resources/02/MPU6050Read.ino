

/**************************************************************************
º¯Êý¹¦ÄÜ£º¶ÁÈ¡6050½Ç¼ÓËÙ¶È¾²Ö¹Ê±µÄÆ«ÒÆÁ¿(ÀÛ¼Æ100´ÎÇóÆ½¾ù)
Èë¿Ú²ÎÊý£ºGyroOffset[]´æ·ÅÍÓÂÝÒÇµÄxyz¾²Ö¹Æ«ÒÆÁ¿(pitch,roll,yew)
·µ»Ø  Öµ£ºÎÞ
**************************************************************************/
void getGyroOffset(int gyroOffset[])
{
	int16_t ax, ay, az;
	int16_t gx, gy, gz;
	int GyroTemp[3] = {0, 0, 0};
	long GyroAcc[3] = {0, 0, 0};
	int i, j;

	for (i = 0; i < 100; i++)
	{
		accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
		GyroTemp[0] = (int)gx;
		GyroTemp[1] = (int)gy;
		GyroTemp[2] = (int)gz;
		for (j = 0; j < 3; j++)
		{
			//if (GyroTemp[j] > 32768)
			//	GyroTemp[j] -= 65536; //Êý¾ÝÀàÐÍ×ª»»  Ò²¿ÉÍ¨¹ýshortÇ¿ÖÆÀàÐÍ×ª»»
			GyroAcc[j] += GyroTemp[j];
		}
	}
	for (j = 0; j < 3; j++)
		gyroOffset[j] = GyroAcc[j] / 100;
}
/*
float getGravAccel()//静止下获取重力加速度
{
        int16_t ax, ay, az;
        int16_t gx, gy, gz;
	int AccelTemp[3] = {0, 0, 0};
	long AccelAcc[3] = {0, 0, 0};
        long a1,a2;
	int i, j;
        float GA;
        
	for (i = 0; i < 100; i++)
	{
                accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
		AccelTemp[0] = (int)ax;
		AccelTemp[1] = (int)ay;
		AccelTemp[2] = (int)az;
                for (j = 0; j < 3; j++)
		{
			//if (GyroTemp[j] > 32768)
			//	GyroTemp[j] -= 65536; //Êý¾ÝÀàÐÍ×ª»»  Ò²¿ÉÍ¨¹ýshortÇ¿ÖÆÀàÐÍ×ª»»
			AccelAcc[j] += AccelTemp[j];
		}
	}
	for (j = 0; j < 3; j++)
		AccelTemp[j] = AccelAcc[j] / 100;
        a1=(long)AccelTemp[0]*(long)AccelTemp[0];
        a2=(long)AccelTemp[2]*(long)AccelTemp[2];
        GA=sqrt(a1+a2);
        //Serial.print("a1:");Serial.print(AccelTemp[0]);Serial.print("\t");
        //Serial.print("a2:");Serial.print(AccelTemp[2]);Serial.print("\t");
        //Serial.print("GA:");Serial.print(GA);Serial.println("\t");
        return GA;
        
}
*/
/**************************************************************************
º¯Êý¹¦ÄÜ£º¶ÁÈ¡6050Ô­Ê¼Öµ,²¢ÓëÇ°99¸öÖµÇóÆ½¾ù
Èë¿Ú²ÎÊý£ºAccel[]£¬´æ·Å¼ÓËÙ¶È¼ÆµÄxyzÖµ£»Gyro[]´æ·ÅÍÓÂÝÒÇµÄxyzÖµ(pitch,roll,yew)
·µ»Ø  Öµ£ºÎÞ
**************************************************************************/
void read6050(int accel[], int gyro[])
{
	int16_t ax, ay, az;
	int16_t gx, gy, gz;
	int AccelTemp[3];
	int GyroTemp[3];
	accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
	AccelTemp[0] = (int)ax;
	AccelTemp[1] = (int)ay;
	AccelTemp[2] = (int)az;
	GyroTemp[0] = (int)gx;
	GyroTemp[1] = (int)gy;
	GyroTemp[2] = (int)gz;
	accel[0] = AccelTemp[0];
	accel[1] = AccelTemp[1];
	accel[2] = AccelTemp[2];
	gyro[0] = GyroTemp[0];
	gyro[1] = GyroTemp[1];
	gyro[2] = GyroTemp[2];
}

/**************************************************************************
º¯Êý¹¦ÄÜ£ºÍ¨¹ý¼ÓËÙ¶È¼Æ¼ÆËã¸©Ñö½Ç¶È
Èë¿Ú²ÎÊý£ºint AccelY,YÖá¼ÓËÙ¶È;int AccelZ£¬ZÖá¼ÓËÙ¶È
·µ»Ø  Öµ£ºÎÞ
**************************************************************************/
float accelAngle(int AccelY, int AccelZ)
{
	return atan2((float)AccelY, (float)AccelZ) * 180 / PI; //¼ÆËãÇã½Ç
}
/**************************************************************************
º¯Êý¹¦ÄÜ£º»ñÈ¡½Ç¶È ÈýÖÖËã·¨¾­¹ýÎÒÃÇµÄµ÷Ð££¬¶¼·Ç³£ÀíÏë 
Èë¿Ú²ÎÊý£º»ñÈ¡½Ç¶ÈµÄËã·¨ 1£ºDMP  2£º¿¨¶ûÂü 3£º»¥²¹ÂË²¨
·µ»Ø  Öµ£ºÎÞ
**************************************************************************/
//void Get_Angle(u8 way)
//{
//	float Accel_Y, Accel_Angle, Accel_Z, Gyro_X, Gyro_Z;
//	Temperature = Read_Temperature(); //===¶ÁÈ¡MPU6050ÄÚÖÃÎÂ¶È´«¸ÐÆ÷Êý¾Ý£¬½üËÆ±íÊ¾Ö÷°åÎÂ¶È¡£
//	if (way == 1)											//===DMPµÄ¶ÁÈ¡ÔÚÊý¾Ý²É¼¯ÖÐ¶Ï¶ÁÈ¡£¬ÑÏ¸ñ×ñÑ­Ê±ÐòÒªÇó
//	{
//		Read_DMP();								 //===¶ÁÈ¡¼ÓËÙ¶È¡¢½ÇËÙ¶È¡¢Çã½Ç
//		Angle_Balance = -Roll;		 //===¸üÐÂÆ½ºâÇã½Ç
//		Gyro_Balance = -gyro[0];	 //===¸üÐÂÆ½ºâ½ÇËÙ¶È
//		Gyro_Turn = gyro[2];			 //===¸üÐÂ×ªÏò½ÇËÙ¶È
//		Acceleration_Z = accel[2]; //===¸üÐÂZÖá¼ÓËÙ¶È¼Æ
//	}
//	else
//	{
//		Gyro_X = (I2C_ReadOneByte(devAddr, MPU6050_RA_GYRO_XOUT_H) << 8) + I2C_ReadOneByte(devAddr, MPU6050_RA_GYRO_XOUT_L);		//¶ÁÈ¡YÖáÍÓÂÝÒÇ
//		Gyro_Z = (I2C_ReadOneByte(devAddr, MPU6050_RA_GYRO_ZOUT_H) << 8) + I2C_ReadOneByte(devAddr, MPU6050_RA_GYRO_ZOUT_L);		//¶ÁÈ¡ZÖáÍÓÂÝÒÇ
//		Accel_Y = (I2C_ReadOneByte(devAddr, MPU6050_RA_ACCEL_YOUT_H) << 8) + I2C_ReadOneByte(devAddr, MPU6050_RA_ACCEL_YOUT_L); //¶ÁÈ¡XÖá¼ÓËÙ¶È¼Æ
//		Accel_Z = (I2C_ReadOneByte(devAddr, MPU6050_RA_ACCEL_ZOUT_H) << 8) + I2C_ReadOneByte(devAddr, MPU6050_RA_ACCEL_ZOUT_L); //¶ÁÈ¡ZÖá¼ÓËÙ¶È¼Æ
//		if (Gyro_X > 32768)
//			Gyro_X -= 65536; //Êý¾ÝÀàÐÍ×ª»»  Ò²¿ÉÍ¨¹ýshortÇ¿ÖÆÀàÐÍ×ª»»
//		if (Gyro_Z > 32768)
//			Gyro_Z -= 65536; //Êý¾ÝÀàÐÍ×ª»»
//		if (Accel_Y > 32768)
//			Accel_Y -= 65536; //Êý¾ÝÀàÐÍ×ª»»
//		if (Accel_Z > 32768)
//			Accel_Z -= 65536;																//Êý¾ÝÀàÐÍ×ª»»
//		Gyro_Balance = Gyro_X;														//¸üÐÂÆ½ºâ½ÇËÙ¶È
//		Accel_Angle = atan2(Accel_Y, Accel_Z) * 180 / PI; //¼ÆËãÇã½Ç
//		Gyro_X = Gyro_X / 16.4;														//ÍÓÂÝÒÇÁ¿³Ì×ª»»
//		if (way == 2)
//			Kalman_Filter(Accel_Angle, Gyro_X); //¿¨¶ûÂüÂË²¨
//		else if (way == 3)
//			Yijielvbo(Accel_Angle, Gyro_X); //»¥²¹ÂË²¨
//		Angle_Balance = angle;						//¸üÐÂÆ½ºâÇã½Ç
//		Gyro_Turn = Gyro_Z;								//¸üÐÂ×ªÏò½ÇËÙ¶È
//		Acceleration_Z = Accel_Z;					//===¸üÐÂZÖá¼ÓËÙ¶È¼Æ
//	}
//}
