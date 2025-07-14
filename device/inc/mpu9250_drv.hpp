#ifndef INCLUDE_MPU9250_DRV_H_
#define INCLUDE_MPU9250_DRV_H_

#include "datatypes.hpp"
#include "device_types.hpp"


//make data structure available
extern imu_T imu_data;

enum DlpfBandwidth : uint8_t {
  DLPF_BANDWIDTH_184HZ = 0x01,
  DLPF_BANDWIDTH_92HZ = 0x02,
  DLPF_BANDWIDTH_41HZ = 0x03,
  DLPF_BANDWIDTH_20HZ = 0x04,
  DLPF_BANDWIDTH_10HZ = 0x05,
  DLPF_BANDWIDTH_5HZ = 0x06
};
enum AccelRange : uint8_t {
  ACCEL_RANGE_2G = 0x00,
  ACCEL_RANGE_4G = 0x08,
  ACCEL_RANGE_8G = 0x10,
  ACCEL_RANGE_16G = 0x18
};
enum GyroRange : uint8_t {
  GYRO_RANGE_250DPS = 0x00,
  GYRO_RANGE_500DPS = 0x08,
  GYRO_RANGE_1000DPS = 0x10,
  GYRO_RANGE_2000DPS = 0x18
};

enum Interface {
  SPI,
  I2C
};


/* Communications interface */
static constexpr uint32_t I2C_CLOCK_ = 400000;
static constexpr uint8_t SPI_READ_ = 0x80;

/* Configuration */

static constexpr uint8_t WHOAMI_MPU9250_ = 0x71;
static constexpr uint8_t WHOAMI_MPU9255_ = 0x73;
static constexpr uint8_t WHOAMI_AK8963_ = 0x48;

/* Registers */
static constexpr uint8_t PWR_MGMNT_1_ = 0x6B;
static constexpr uint8_t H_RESET_ = 0x80;
static constexpr uint8_t CLKSEL_PLL_ = 0x01;
static constexpr uint8_t WHOAMI_ = 0x75;
static constexpr uint8_t ACCEL_CONFIG_ = 0x1C;
static constexpr uint8_t GYRO_CONFIG_ = 0x1B;
static constexpr uint8_t ACCEL_CONFIG2_ = 0x1D;
static constexpr uint8_t CONFIG_ = 0x1A;
static constexpr uint8_t SMPLRT_DIV_ = 0x19;
static constexpr uint8_t INT_PIN_CFG_ = 0x37;
static constexpr uint8_t INT_ENABLE_ = 0x38;
static constexpr uint8_t INT_DISABLE_ = 0x00;
static constexpr uint8_t INT_PULSE_50US_ = 0x00;
static constexpr uint8_t INT_RAW_RDY_EN_ = 0x01;
static constexpr uint8_t INT_STATUS_ = 0x3A;
static constexpr uint8_t RAW_DATA_RDY_INT_ = 0x01;
static constexpr uint8_t USER_CTRL_ = 0x6A;
static constexpr uint8_t I2C_MST_EN_ = 0x20;
static constexpr uint8_t I2C_MST_CLK_ = 0x0D;
static constexpr uint8_t I2C_MST_CTRL_ = 0x24;
static constexpr uint8_t I2C_SLV0_ADDR_ = 0x25;
static constexpr uint8_t I2C_SLV0_REG_ = 0x26;
static constexpr uint8_t I2C_SLV0_CTRL_ = 0x27;
static constexpr uint8_t I2C_SLV0_DO_ = 0x63;
static constexpr uint8_t I2C_READ_FLAG_ = 0x80;
static constexpr uint8_t I2C_SLV0_EN_ = 0x80;
static constexpr uint8_t EXT_SENS_DATA_00_ = 0x49;
static constexpr uint8_t ST2_HOFL = 0x08;

static constexpr uint8_t ACCEL_XOUT_H = 0x3B;
static constexpr uint8_t ACCEL_XOUT_L = 0x3C;
static constexpr uint8_t ACCEL_YOUT_H = 0x3D;
static constexpr uint8_t ACCEL_YOUT_L = 0x3E;
static constexpr uint8_t ACCEL_ZOUT_H = 0x3F;
static constexpr uint8_t ACCEL_ZOUT_L = 0x40;  
static constexpr uint8_t TEMP_OUT_H = 0x41;
static constexpr uint8_t TEMP_OUT_L = 0x42;
static constexpr uint8_t GYRO_XOUT_H = 0x43;
static constexpr uint8_t GYRO_XOUT_L = 0x44;
static constexpr uint8_t GYRO_YOUT_H = 0x45;
static constexpr uint8_t GYRO_YOUT_L = 0x46;
static constexpr uint8_t GYRO_ZOUT_H = 0x47;
static constexpr uint8_t GYRO_ZOUT_L = 0x48;

static constexpr uint8_t MAG_XOUT_H = 0x04;
static constexpr uint8_t MAG_XOUT_L = 0x03;
static constexpr uint8_t MAG_YOUT_H = 0x06;
static constexpr uint8_t MAG_YOUT_L = 0x05;
static constexpr uint8_t MAG_ZOUT_H = 0x08;
static constexpr uint8_t MAG_ZOUT_L = 0x07;

   
/* AK8963 registers */
static constexpr uint8_t AK8963_I2C_ADDR_ = 0x0C;
static constexpr uint8_t AK8963_ST1_ = 0x02;
static constexpr uint8_t AK8963_ST2_ = 0x09;
static constexpr uint8_t AK8963_HXL_ = 0x03;
static constexpr uint8_t AK8963_CNTL1_ = 0x0A;
static constexpr uint8_t AK8963_PWR_DOWN_ = 0x00;
static constexpr uint8_t AK8963_CNT_MEAS1_ = 0x12;
static constexpr uint8_t AK8963_CNT_MEAS2_ = 0x16;
static constexpr uint8_t AK8963_FUSE_ROM_ = 0x0F;
static constexpr uint8_t AK8963_CNTL2_ = 0x0B;
static constexpr uint8_t AK8963_RESET_ = 0x01;
static constexpr uint8_t AK8963_ASA_ = 0x10;
static constexpr uint8_t AK8963_WHOAMI_ = 0x00;


drivers_response_E mpu9250Init(void);
void mpu9250Step(void);


#endif  // INCLUDE_MPU9250_DRV_H_