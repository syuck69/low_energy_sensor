#ifndef __SHT3X_TINY_I2C_H__
#define __SHT3X_TINY_I2C_H__

/*********** REGISTERS ADDRESSES ************/
#define SHT3X_REG_CS_EN             (0x2C)
#define SHT3X_REG_CS_DIS            (0x24)

#define SHT3X_REG_SOFT_RST           (0x30)
#define SHT3X_REG_READSR             (0xF3)
#define SHT3X_REG_CLEARSR            (0x30)
/**************** COMMAND *******************/
#define SHT3X_CMD_CS_EN_LOW          (0x06)
#define SHT3X_CMD_CS_EN_MED          (0x0D)
#define SHT3X_CMD_CS_EN_HIGH         (0x10)
#define SHT3X_CMD_CS_DIS_LOW         (0x00)
#define SHT3X_CMD_CS_DIS_MED         (0x0B)
#define SHT3X_CMD_CS_DIS_HIGH        (0x16)
#define SHT3X_CMD_SOFT_RST           (0xA2)
#define SHT3X_CMD_READSR             (0x2D)
#define SHT3X_CMD_CLEARSR            (0x41)
/**************** LENGTH ********************/
#define SHT3X_T_H_DATA_LEN     (6)
/**************** MACROS ********************/

/*********** CALIBRATION DATAS **************/

/************* SENSOR VALUES ****************/
typedef struct {
  float  temperature; //   T =-45+175.temperature /(2exp16-1)
  int16_t humidity;    //  RH =100.humidity/(2exp16-1)
  
} SHT3X;

/******************** API *******************/
uint8_t sht3x_read_sensor(SHT3X*);
uint8_t sht3x_init(SHT3X*);

#endif
