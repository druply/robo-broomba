#include "mpu9250_drv.hpp"

#include "sys_logger.hpp"
#include <wiringPi.h>
#include <wiringPiI2C.h>


/* Communications interface */
Interface iface_;    
int conn_;
uint32_t spi_clock_;

/* Configuration */
AccelRange accel_range_;
GyroRange gyro_range_;
DlpfBandwidth dlpf_bandwidth_;
//uint8_t srd_;

/* Data */
float accel_scale_, gyro_scale_, mag_scale_[3];
const float temp_scale_ = 333.87f;

//float accel_mps2_[3];
//float gyro_radps_[3];
//float mag_ut_[3];
//float die_temperature_c_;

/*
inline AccelRange accel_range()  {return accel_range_;}
inline GyroRange gyro_range()  {return gyro_range_;}
inline DlpfBandwidth dlpf()  {return dlpf_bandwidth_;}
inline uint8_t srd()  {return srd_;}
*/

/*
float accel_x_mps2(void) {return accel_mps2_[0];}
float accel_y_mps2(void)  {return accel_mps2_[1];}
float accel_z_mps2(void)  {return accel_mps2_[2];}
float gyro_x_radps(void)  {return gyro_radps_[0];}
float gyro_y_radps(void)  {return gyro_radps_[1];}
float gyro_z_radps(void)  {return gyro_radps_[2];}
float mag_x_ut(void)  {return mag_ut_[0];}
float mag_y_ut(void)  {return mag_ut_[1];}
float mag_z_ut(void)  {return mag_ut_[2];}
float die_temperature_c(void)  {return die_temperature_c_;}
*/

imu_T imu_data;

bool WriteRegister(uint8_t reg, uint8_t data) {
    int res;
    //if (sizeof(data) == size(uint8_t)) {
        //std::cout << std::hex << int(data) << std::endl;
        res = wiringPiI2CWriteReg8(conn_, reg, data);
    //} else {
    //    res = wiringPiI2CWrite (conn_, data);
    //}
    if(res < 0) {
        return false;
    } else {
        return true;
    }

}

bool ReadRegisters(uint8_t reg, uint8_t count, uint8_t *data) {
  
  *data = wiringPiI2CReadReg8(conn_, reg);

  return true;    
    
}

bool ReadAk8963Registers(uint8_t reg, uint8_t count, uint8_t *data) {
  if (!WriteRegister(I2C_SLV0_ADDR_, AK8963_I2C_ADDR_ | I2C_READ_FLAG_)) {
    return false;
  }
  if (!WriteRegister(I2C_SLV0_REG_, reg)) {
    return false;
  }
  if (!WriteRegister(I2C_SLV0_CTRL_, I2C_SLV0_EN_ | count)) {
    return false;
  }
  delay(1);
  return ReadRegisters(EXT_SENS_DATA_00_, count, data);
}


bool WriteAk8963Register(uint8_t reg, uint8_t data) {
  uint8_t ret_val;
  if (!WriteRegister(I2C_SLV0_ADDR_, AK8963_I2C_ADDR_)) {
    return false;
  }
  if (!WriteRegister(I2C_SLV0_REG_, reg)) {
    return false;
  }
  if (!WriteRegister(I2C_SLV0_DO_, data)) {
    return false;
  }
  if (!WriteRegister(I2C_SLV0_CTRL_, I2C_SLV0_EN_ | sizeof(data))) {
    return false;
  }
  if (!ReadAk8963Registers(reg, sizeof(ret_val), &ret_val)) {
    return false;
  }
  if (data == ret_val) {
    return true;
  } else {
    return false;
  }
}



bool ConfigAccelRange(const AccelRange range) {
  AccelRange requested_range;
  float requested_scale;
  spi_clock_ = 1000000;
  /* Check input is valid and set requested range and scale */
  switch (range) {
    case ACCEL_RANGE_2G: {
      requested_range = range;
      requested_scale = 2.0f / 32767.5f;
      break;
    }
    case ACCEL_RANGE_4G: {
      requested_range = range;
      requested_scale = 4.0f / 32767.5f;
      break;
    }
    case ACCEL_RANGE_8G: {
      requested_range = range;
      requested_scale = 8.0f / 32767.5f;
      break;
    }
    case ACCEL_RANGE_16G: {
      requested_range = range;
      requested_scale = 16.0f / 32767.5f;
      break;
    }
    default: {
      return false;
    }
  }
  /* Try setting the requested range */
  if (!WriteRegister(ACCEL_CONFIG_, requested_range)) {
    return false;
  }
  /* Update stored range and scale */
  accel_range_ = requested_range;
  accel_scale_ = requested_scale;
  return true;
}


bool ConfigGyroRange(const GyroRange range) {
  GyroRange requested_range;
  float requested_scale;
  spi_clock_ = 1000000;
  /* Check input is valid and set requested range and scale */
  switch (range) {
    case GYRO_RANGE_250DPS: {
      requested_range = range;
      requested_scale = 250.0f / 32767.5f;
      break;
    }
    case GYRO_RANGE_500DPS: {
      requested_range = range;
      requested_scale = 500.0f / 32767.5f;
      break;
    }
    case GYRO_RANGE_1000DPS: {
      requested_range = range;
      requested_scale = 1000.0f / 32767.5f;
      break;
    }
    case GYRO_RANGE_2000DPS: {
      requested_range = range;
      requested_scale = 2000.0f / 32767.5f;
      break;
    }
    default: {
      return false;
    }
  }
  /* Try setting the requested range */
  if (!WriteRegister(GYRO_CONFIG_, requested_range)) {
    return false;
  }
  /* Update stored range and scale */
  gyro_range_ = requested_range;
  gyro_scale_ = requested_scale;
  return true;
}


bool ConfigSrd(const uint8_t srd) {
  spi_clock_ = 1000000;
  /* Changing the SRD to allow us to set the magnetometer successfully */
  if (!WriteRegister(SMPLRT_DIV_, 19)) {
    return false;
  }
  /* Set the magnetometer sample rate */
  if (srd > 9) {
    /* Set AK8963 to power down */
    WriteAk8963Register(AK8963_CNTL1_, AK8963_PWR_DOWN_);
    delay(100);  // long wait between AK8963 mode changes
    /* Set AK8963 to 16 bit resolution, 8 Hz update rate */
    if (!WriteAk8963Register(AK8963_CNTL1_, AK8963_CNT_MEAS1_)) {
      return false;
    }
    delay(100);  // long wait between AK8963 mode changes
    /* Instruct the MPU9250 to get 7 bytes from the AK8963 at the sample rate */
    uint8_t mag_data[7];
    if (!ReadAk8963Registers(AK8963_HXL_, sizeof(mag_data), mag_data)) {
      return false;
    }
  } else {
    /* Set AK8963 to power down */
    WriteAk8963Register(AK8963_CNTL1_, AK8963_PWR_DOWN_);
    delay(100);  // long wait between AK8963 mode changes
    /* Set AK8963 to 16 bit resolution, 100 Hz update rate */
    if (!WriteAk8963Register(AK8963_CNTL1_, AK8963_CNT_MEAS2_)) {
      return false;
    }
    delay(100);  // long wait between AK8963 mode changes
    /* Instruct the MPU9250 to get 7 bytes from the AK8963 at the sample rate */
    uint8_t mag_data[7];
    if (!ReadAk8963Registers(AK8963_HXL_, sizeof(mag_data), mag_data)) {
      return false;
    }
  }
  /* Set the IMU sample rate */
  if (!WriteRegister(SMPLRT_DIV_, srd)) {
    return false;
  }
  //srd_ = srd;
  return true;
}


bool ConfigDlpf(const DlpfBandwidth dlpf) {
  DlpfBandwidth requested_dlpf;
  spi_clock_ = 1000000;
  /* Check input is valid and set requested dlpf */
  switch (dlpf) {
    case DLPF_BANDWIDTH_184HZ: {
      requested_dlpf = dlpf;
      break;
    }
    case DLPF_BANDWIDTH_92HZ: {
      requested_dlpf = dlpf;
      break;
    }
    case DLPF_BANDWIDTH_41HZ: {
      requested_dlpf = dlpf;
      break;
    }
    case DLPF_BANDWIDTH_20HZ: {
      requested_dlpf = dlpf;
      break;
    }
    case DLPF_BANDWIDTH_10HZ: {
      requested_dlpf = dlpf;
      break;
    }
    case DLPF_BANDWIDTH_5HZ: {
      requested_dlpf = dlpf;
      break;
    }
    default: {
      return false;
    }
  }
  /* Try setting the dlpf */
  if (!WriteRegister(ACCEL_CONFIG2_, requested_dlpf)) {
    return false;
  }
  if (!WriteRegister(CONFIG_, requested_dlpf)) {
    return false;
  }
  /* Update stored dlpf */
  dlpf_bandwidth_ = requested_dlpf;
  return true;
}


bool ImuBegin(void) {  
  
  SystemLog("IMU: clock selection");

  /* Select clock source to gyro */
  if (!WriteRegister(PWR_MGMNT_1_, CLKSEL_PLL_)) {
    SystemLog("IMU: clock selection error");
    return false;
  }
  
  delay(20);
  SystemLog("IMU: Select clock source");  
  
  SystemLog("IMU: Enable I2C master mode");
  /* Enable I2C master mode */
  if (!WriteRegister(USER_CTRL_, I2C_MST_EN_)) {
    SystemLog("IMU: error selecting master mode");
    return false;
  }
  delay(20);
  
  /* Set the I2C bus speed to 400 kHz */
  if (!WriteRegister(I2C_MST_CTRL_, I2C_MST_CLK_)) {
    SystemLog("IMU: I2C bus speed error");
    return false;
  }
  delay(20);
  
  SystemLog("IMU: Set the I2C bus speed");
  
  /* Set AK8963 to power down */
  WriteAk8963Register(AK8963_CNTL1_, AK8963_PWR_DOWN_);
  delay(20);  
  SystemLog("IMU: Set AK8963 to power down");

  /* Reset the MPU9250 */
  WriteRegister(PWR_MGMNT_1_, H_RESET_);
  delay(20);  
  SystemLog("IMU: Reset the MPU9250");

  /* Wait for MPU-9250 to come back up */
  delay(20);
  /* Reset the AK8963 */
  WriteAk8963Register(AK8963_CNTL2_, AK8963_RESET_);  
  SystemLog("IMU: Reset the AK8963");

  /* Wait for MPU-9250 to come back up */
  delay(20);
  /* Select clock source to gyro */
  if (!WriteRegister(PWR_MGMNT_1_, CLKSEL_PLL_)) {
    SystemLog("IMU: error Select clock source to gyro");
    return false;
  }
  delay(20);  
  SystemLog("IMU: Select clock source to gyro");

  /* Check the WHO AM I byte */
  uint8_t who_am_i = 0;
  if (!ReadRegisters(WHOAMI_, sizeof(who_am_i), &who_am_i)) {
    SystemLog("IMU: Check the WHO AM I error");
    return false;
  }
  delay(20);
  SystemLog("IMU: Check the WHO AM I");
  
  if ((who_am_i != WHOAMI_MPU9250_) && (who_am_i != WHOAMI_MPU9255_)) {
    SystemLog("IMU: I am not MPU9250 nor MPU9255");
    return false;
  }  
  SystemLog("IMU: I am MPU9250");

  delay(1);
  /* Enable I2C master mode */
  if (!WriteRegister(USER_CTRL_, I2C_MST_EN_)) {
    SystemLog("IMU: Enable I2C master mode error");
    return false;
  }
  delay(20);  
  SystemLog("IMU: Enable I2C master mode");
  
  /* Set the I2C bus speed to 400 kHz */
  if (!WriteRegister(I2C_MST_CTRL_, I2C_MST_CLK_)) {
    SystemLog("IMU: Set the I2C bus speed error");
    return false;
  }
  delay(20);  
  SystemLog("IMU: Set the I2C bus speed");

  /* Check the AK8963 WHOAMI */
  if (!ReadAk8963Registers(AK8963_WHOAMI_, sizeof(who_am_i), &who_am_i)) {
    return false;
  }
  delay(20);  
  SystemLog("IMU: Check the AK8963 WHOAMI");
  
  if (who_am_i != WHOAMI_AK8963_) {
    SystemLog("IMU: Check the AK8963 WHOAMI error");
    return false;
  }
  
  /* Get the magnetometer calibration */
  /* Set AK8963 to power down */
  if (!WriteAk8963Register(AK8963_CNTL1_, AK8963_PWR_DOWN_)) {
    return false;
  }
  delay(100);  // long wait between AK8963 mode changes
  /* Set AK8963 to FUSE ROM access */
  if (!WriteAk8963Register(AK8963_CNTL1_, AK8963_FUSE_ROM_)) {
    return false;
  }
  delay(100);  // long wait between AK8963 mode changes
  /* Read the AK8963 ASA registers and compute magnetometer scale factors */
  uint8_t asa_buff1;
  if (!ReadAk8963Registers(AK8963_ASA_, sizeof(asa_buff1), &asa_buff1)) {
    return false;
  }
  mag_scale_[0] = ((static_cast<float>(asa_buff1) - 128.0f)
    / 256.0f + 1.0f) * 4912.0f / 32760.0f;

  uint8_t asa_buff2;
  if (!ReadAk8963Registers(AK8963_ASA_, sizeof(asa_buff2), &asa_buff2)) {
    return false;
  }
  mag_scale_[1] = ((static_cast<float>(asa_buff2) - 128.0f)
    / 256.0f + 1.0f) * 4912.0f / 32760.0f;

  
  uint8_t asa_buff3;
  if (!ReadAk8963Registers(AK8963_ASA_, sizeof(asa_buff3), &asa_buff3)) {
    return false;
  }
  mag_scale_[2] = ((static_cast<float>(asa_buff3) - 128.0f)
    / 256.0f + 1.0f) * 4912.0f / 32760.0f;
  /* Set AK8963 to power down */
  if (!WriteAk8963Register(AK8963_CNTL1_, AK8963_PWR_DOWN_)) {
    return false;
  }
  /* Set AK8963 to 16 bit resolution, 100 Hz update rate */
  if (!WriteAk8963Register(AK8963_CNTL1_, AK8963_CNT_MEAS2_)) {
    return false;
  }
  delay(100);  // long wait between AK8963 mode changes
  /* Select clock source to gyro */
  if (!WriteRegister(PWR_MGMNT_1_, CLKSEL_PLL_)) {
    return false;
  }
  /* Instruct the MPU9250 to get 7 bytes from the AK8963 at the sample rate */
  uint8_t mag_data[7];
  if (!ReadAk8963Registers(AK8963_HXL_, sizeof(mag_data), mag_data)) {
    return false;
  }
  /* Set the accel range to 16G by default */
  if (!ConfigAccelRange(ACCEL_RANGE_16G)) {
    return false;
  }
  /* Set the gyro range to 2000DPS by default*/
  if (!ConfigGyroRange(GYRO_RANGE_2000DPS)) {
    return false;
  }
  /* Set the DLPF to 20HZ by default */
  if (!ConfigDlpf(DLPF_BANDWIDTH_20HZ)) {
    return false;
  }
  /* Set the SRD to 0 by default */
  if (!ConfigSrd(0)) {
    return false;
  }
  
  //imu_data.status = ready;

  return true;
}


drivers_response_E mpu9250Init(void) {

  bool res_tmp;
  drivers_response_E res;
  const int addr = 0x68;


  conn_ = wiringPiI2CSetup(addr);
  if (conn_ < 0) {
    SystemLog("I2C connection error");
    
  }
  else {
    res_tmp = ImuBegin();
  }

  if (res_tmp == true) {
      res = drivers_response_E::ok;
  }
  else {
    res = drivers_response_E::init_error;
    SystemLog("failed to initialize mpu9250");
  }

  return res;
}


bool imuRead(void) {
  //spi_clock_ = 20000000;

  /* Read the data registers */

  uint8_t data_buff;
  // read data buffer
  if (!ReadRegisters(INT_STATUS_, sizeof(data_buff), &data_buff)) {
    return false;
  }

  // check if data is ready
  bool data_ready = (data_buff & RAW_DATA_RDY_INT_);
  if (!data_ready) {
    return false;
  }

  // Read accelerometer x data
  int16_t accel_counts[3], gyro_counts[3], temp_counts, mag_counts[3];
  uint8_t acc_x_h;
  uint8_t acc_x_l;
  if (!ReadRegisters(ACCEL_XOUT_H, sizeof(acc_x_h), &acc_x_h)) {
    return false;
  }
   
   if (!ReadRegisters(ACCEL_XOUT_L, sizeof(acc_x_l), &acc_x_l)) {
    return false;
  }
  accel_counts[0] = int16_t(((uint16_t)acc_x_h  << 8) | (uint16_t)acc_x_l);

  // Read accelerometer y data
  uint8_t acc_y_h;
  uint8_t acc_y_l;
  if (!ReadRegisters(ACCEL_YOUT_H, sizeof(acc_y_h), &acc_y_h)) {
    return false;
  }
   
   if (!ReadRegisters(ACCEL_YOUT_L, sizeof(acc_y_l), &acc_y_l)) {
    return false;
  }
  accel_counts[1] = int16_t(((uint16_t)acc_y_h  << 8) | (uint16_t)acc_y_l);

  // Read accelerometer z data
  uint8_t acc_z_h;
  uint8_t acc_z_l;
  if (!ReadRegisters(ACCEL_ZOUT_H, sizeof(acc_z_h), &acc_z_h)) {
    return false;
  }
   
   if (!ReadRegisters(ACCEL_ZOUT_L, sizeof(acc_z_l), &acc_z_l)) {
    return false;
  }
  accel_counts[2] = int16_t(((uint16_t)acc_z_h  << 8) | (uint16_t)acc_z_l);


  /* Convert to float values and rotate the accel / gyro axis */
  
  //accel_mps2_[0] = static_cast<float>(accel_counts[0]) * accel_scale_ *
  //                 9.80665f;
  imu_data.acc_x =  static_cast<axis_T>(accel_counts[0]) * static_cast<axis_T>(accel_scale_);// *(axis_T)9.80665;      

  //accel_mps2_[2] = static_cast<float>(accel_counts[2]) * accel_scale_ *
  //                 -9.80665f;

  imu_data.acc_z = static_cast<axis_T>(accel_counts[2]) * static_cast<axis_T>(accel_scale_);// * (axis_T)9.80665;

  //accel_mps2_[1] = static_cast<float>(accel_counts[1]) * accel_scale_ *
  //                 9.80665f;

  imu_data.acc_y = static_cast<axis_T>(accel_counts[1]) * static_cast<axis_T>(accel_scale_);//* (axis_T)9.80665;

  // Read gyrometer x data
  uint8_t gyro_x_h;
  uint8_t gyro_x_l;
  if (!ReadRegisters(GYRO_XOUT_H, sizeof(gyro_x_h), &gyro_x_h)) {
    return false;
  }
   
   if (!ReadRegisters(GYRO_XOUT_L, sizeof(gyro_x_l), &gyro_x_l)) {
    return false;
  }
  gyro_counts[0] = int16_t(((uint16_t)gyro_x_h  << 8) | (uint16_t)gyro_x_l);

  // Read gyrometer y data
  uint8_t gyro_y_h;
  uint8_t gyro_y_l;
  if (!ReadRegisters(GYRO_YOUT_H, sizeof(gyro_y_h), &gyro_y_h)) {
    return false;
  }
   
   if (!ReadRegisters(GYRO_YOUT_L, sizeof(gyro_y_l), &gyro_y_l)) {
    return false;
  }
  gyro_counts[1] = int16_t(((uint16_t)gyro_y_h  << 8) | (uint16_t)gyro_y_l);

  // Read gyrometer z data
  uint8_t gyro_z_h;
  uint8_t gyro_z_l;
  if (!ReadRegisters(GYRO_ZOUT_H, sizeof(gyro_z_h), &gyro_z_h)) {
    return false;
  }
   
   if (!ReadRegisters(GYRO_ZOUT_L, sizeof(gyro_z_l), &gyro_z_l)) {
    return false;
  }
  gyro_counts[2] = int16_t(((uint16_t)gyro_z_h  << 8) | (uint16_t)gyro_z_l);



  //gyro_radps_[0] = static_cast<float>(gyro_counts[0]) * gyro_scale_ *
  //                 3.14159265358979323846f / 180.0f;

  imu_data.gyr_x = static_cast<axis_T>(gyro_counts[0]) * static_cast<axis_T>(gyro_scale_);// *  (axis_T)(3.14159265358979323846 / 180.0);

  //gyro_radps_[1] = static_cast<float>(gyro_counts[1]) * gyro_scale_ *
  //                 3.14159265358979323846f / 180.0f;
  
  imu_data.gyr_y = static_cast<axis_T>(gyro_counts[1]) * static_cast<axis_T>(gyro_scale_);// * (axis_T)(3.14159265358979323846 / 180.0);

  //gyro_radps_[2] = static_cast<float>(gyro_counts[2]) * gyro_scale_ *
  //                 -1.0f * 3.14159265358979323846f / 180.0f;
  
  imu_data.gyr_z = static_cast<axis_T>(gyro_counts[2]) * static_cast<axis_T>(gyro_scale_);// * (axis_T)(3.14159265358979323846 / 180.0);


  uint8_t temp_l;
  uint8_t temp_h;
  if (!ReadRegisters(TEMP_OUT_H, sizeof(temp_h), &temp_h)) {
    return false;
  }

    if (!ReadRegisters(TEMP_OUT_L, sizeof(temp_l), &temp_l)) {
    return false;
  }

  temp_counts =  int16_t(((uint16_t)temp_h  << 8) | (uint16_t)temp_l);


  imu_data.temperature = ((axis_T)temp_counts - (axis_T)21.0) / (axis_T)temp_scale_ + (axis_T)21.0;


  // check if dno overflow has occurred
  uint8_t status2;
  if (!ReadAk8963Registers(AK8963_ST2_, sizeof(status2), &status2)) {
    std::cout << "error reading st2" << std::endl;
    return false;
  }

  bool overflow_st = ((status2&ST2_HOFL)==0x08);

  if(overflow_st) {
    std::cout << "overflow occured.." << std::endl;
    return false;
  }

  uint8_t mag_x_h;
  uint8_t mag_x_l;
  if (!ReadAk8963Registers(MAG_XOUT_H, sizeof(mag_x_h), &mag_x_h)) {
    return false;
  }
   
   if (!ReadAk8963Registers(MAG_XOUT_L, sizeof(mag_x_l), &mag_x_l)) {
    return false;
  }
  mag_counts[0] = int16_t(((uint16_t)mag_x_h  << 8) | (uint16_t)mag_x_l);


  uint8_t mag_y_h;
  uint8_t mag_y_l;
  if (!ReadAk8963Registers(MAG_YOUT_H, sizeof(mag_y_h), &mag_y_h)) {
    return false;
  }
   
   if (!ReadAk8963Registers(MAG_XOUT_L, sizeof(mag_y_l), &mag_y_l)) {
    return false;
  }
  mag_counts[1] = int16_t(((uint16_t)mag_y_h  << 8) | (uint16_t)mag_y_l);


  uint8_t mag_z_h;
  uint8_t mag_z_l;
  if (!ReadAk8963Registers(MAG_ZOUT_H, sizeof(mag_z_h), &mag_z_h)) {
    return false;
  }
   
   if (!ReadAk8963Registers(MAG_ZOUT_L, sizeof(mag_z_l), &mag_z_l)) {
    return false;
  }
  mag_counts[2] = int16_t(((uint16_t)mag_z_h  << 8) | (uint16_t)mag_z_l);



  // mag_ut_[0] =   static_cast<float>(mag_counts[0]) * mag_scale_[0];
  imu_data.mag_x = (axis_T)mag_counts[0] * (axis_T)mag_scale_[0];
  
  //mag_ut_[1] =   static_cast<float>(mag_counts[1]) * mag_scale_[1];
  imu_data.mag_y = (axis_T)mag_counts[1] * (axis_T)mag_scale_[1];

  //mag_ut_[2] =   static_cast<float>(mag_counts[2]) * mag_scale_[2];
  imu_data.mag_z = (axis_T)mag_counts[2] * (axis_T)mag_scale_[2];




  return true;
}



void mpu9250Step(void) {
  
  imu_data.status = sensor_status_E::busy;

  if (imuRead() == true) {
      imu_data.status = sensor_status_E::ready;
  }
  else {
    imu_data.status = sensor_status_E::error;
  }
}