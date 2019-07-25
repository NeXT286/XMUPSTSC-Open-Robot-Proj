/*
功能函数
	void getGyroOffset(int gyroOffset[])
	功能：获取角速度零偏
	输入参数：
		gyroOffset[]：
			功能：用于存放三轴角速度零偏的数组
	输出参数：无

	void read6050(int accel[], int gyro[])
	功能：获取三轴加速度和角速度的原始值
	输入参数：
		accel[]：
			功能：用于存放三轴加速度的数组
		gyroOffset[]：
			功能：用于存放三轴角速度的数组
	输出参数：无

	float accelAngle(int AccelY, int AccelZ)
	功能：通过加速度计算倾角
	输入参数：
		AccelY：
			功能：前进方向加速度
		AccelZ：
			功能：垂直方向加速度
	输出参数：
			计算出的倾角
*/


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


float accelAngle(int AccelY, int AccelZ)
{
	return atan2((float)AccelY, (float)AccelZ) * 180 / PI; //¼ÆËãÇã½Ç
}
