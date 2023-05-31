#ifndef LTC2943_H
#define LTC2943_H

#include <QCoreApplication>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
//#include <termios.h>
#include <error.h>

#include <QtSerialPort/QSerialPort>
#include <QDebug>
#include <QMessageBox>

// sys includes
//#include <termios.h>
#include <errno.h>
#include <unistd.h>
#include <ctype.h>
//#include <sys/ioctl.h>
//#include <sys/termios.h>
#include <sys/time.h>
#include <sys/types.h>
//#include <sys/select.h>
#include <fcntl.h>

// cpp includes
#include <iostream>

// qt includes
#include <QGuiApplication>
#include <QSettings>
#include <QFile>
#include <QDir>
#include <QEvent>
#include <QFileInfo>
#include <QRegExp>
#include <QKeyEvent>
#include <QResizeEvent>
#include <QTextStream>
#include <QProcess>
#include <QSocketNotifier>
#include <QTimer>
#include <QDateTime>

#include <QtWidgets/QComboBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QProgressDialog>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextBrowser>

#include <qserialportinfo.h>
#include "filter.h"

#define LTC2944_ADDRESS			0x64

#define I2C2USB_START           0x55
#define DATA_1BYTE              0x01

/* Register Map */

#define REG_A_STATUS			0x00 // Status (R)
#define REG_B_CONTROL			0x01 // Control (R/W)
#define REG_C_ACC_CHG_MSB		0x02 // Accumulated Charge MSB (R/W)
#define REG_D_ACC_CHG_LSB		0x03 // Accumulated Charge LSB (R/W)
#define REG_E_CHG_THR_H_MSB		0x04 // Charge Threshold High MSB (R/W)
#define REG_F_CHG_THR_H_LSB		0x05 // Charge Threshold High LSB (R/W)
#define REG_G_CHG_THR_L_MSB		0x06 // Charge Threshold Low MSB (R/W)
#define REG_H_CHG_THR_L_LSB		0x07 // Charge Threshold Low LSB (R/W)
#define REG_I_VOLTAGE_MSB		0x08 // Voltage MSB (R)
#define REG_J_VOLTAGE_LSB		0x09 // Voltage LSB (R)
#define REG_K_VOLTAGE_THR_H_MSB	0x0A // Voltage Threshold High MSB (R/W)
#define REG_L_VOLTAGE_THR_H_LSB	0x0B // Voltage Threshold High LSB (R/W)
#define REG_M_VOLTAGE_THR_L_MSB	0x0C // Voltage Threshold Low MSB (R/W)
#define REG_N_VOLTAGE_THR_L_LSB	0x0D // Voltage Threshold Low LSB (R/W)
#define REG_O_CURRENT_MSB		0x0E // Current MSB (R)
#define REG_P_CURRENT_LSB		0x0F // Current LSB (R)
#define REG_Q_CURRENT_THR_H_MSB	0x10 // Current Threshold High MSB (R/W)
#define REG_R_CURRENT_THR_H_LSB	0x11 // Current Threshold High LSB (R/W)
#define REG_S_CURRENT_THR_L_MSB	0x12 // Current Threshold Low MSB (R/W)
#define REG_T_CURRENT_THR_L_LSB	0x13 // Current Threshold Low LSB (R/W)
#define REG_U_TEMP_MSB			0x14 // Temperature MSB (R)
#define REG_V_TEMP_LSB			0x15 // Temperature LSB (R)
#define REG_W_TEMP_THR_H		0x16 // Temperature Threshold High (R/W)
#define REG_X_TEMP_THR_L		0x17 // Temperature Threshold Low (R/W)

/* Status Register (A) */

#define A_CHIP_ID_OFFSET		7 // Default 0
#define CHIP_ID_LTC2944			0
#define CHIP_ID_LTC2943			1
// Bits below are cleared after register is read
#define A_CURRENT_ALERT_OFFSET	6 // Default 0
#define A_ACC_CHG_OF_UF_OFFSET	5 // Default 0
#define A_TEMP_ALERT_OFFSET		4 // Default 0
#define A_CHG_ALERT_H_OFFSET	3 // Default 0
#define A_CHG_ALERT_L_OFFSET	2 // Default 0
#define A_VOLTAGE_ALERT_OFFSET	1 // Default 0
#define A_UV_LOCK_ALERT_OFFSET	0

/* Control Register (B) */

#define B_ADC_MODE_OFFSET		6 // Default [00]
#define ADC_MODE_MASK			0b00111111
#define ADC_MODE_AUTO			0b11
#define ADC_MODE_SCAN			0b10
#define ADC_MODE_MANUAL			0b01
#define ADC_MODE_SLEEP			0b00

#define B_PRESCALER_M_OFFSET	3 // Default [111], M = 2^(4 * B[5] + 2 * B[4] + B[3])
#define PRESCALER_M_MASK		0b11000111

#define B_ALCC_CONFIG_OFFSET	1 // Default [10]
#define ALCC_CONFIG_MASK		0b11111001
#define ALCC_MODE_ALERT			0b10
#define ALCC_MODE_CHG_COMPLETE	0b01
#define ALCC_MODE_DISABLED		0b00
#define ALCC_MODE_NOT_ALLOWED	0b11

#define SHUTDOWN_MASK			0b11111110

#define P_ERROR -1

#define AC_MARGIN               500


class LTC2943 {
    public:
        LTC2943(uint8_t rSense = 15);
        bool begin();
        void startMeasurement();
        void stopMeasurement();
        uint8_t getStatus();
        uint8_t findExponentOfPowerOfTwo(uint16_t value);
        uint16_t roundUpToPowerOfTwo(uint16_t value);
        void setPrescalerM(uint16_t m);
        void getPrescalerM();
        void setADCMode(uint8_t mode);
        void configureALCC(uint8_t mode);
        int getRawAccumulatedCharge();
        float getRemainingCapacity();
        float getVoltage(bool oneShot = false);
        float getTemperature(bool oneShot = true);
        float getCurrent(bool oneShot = false);
        void setBatteryCapacity(uint16_t mAh);
        void setBatteryToFull();
        void setRawAccumulatedCharge(uint16_t charge);
        void setChargeThresholds(uint16_t high, uint16_t low);
        void setVoltageThresholds(float high, float low);
        void setTemperatureThresholds(float high, float low);
        void setCurrentThresholds(float high, float low);
        //custom function
        uint16_t getPersent(uint16_t AC);
        void setChargeThresholdH(uint16_t high);
        void setChargeThresholdL(uint16_t low);
        void presetAC(uint32_t VOLT, uint16_t VoltT_H, uint16_t VoltT_L);
        uint16_t getACThresholdH();
        uint16_t getACThresholdL();
        float getVoltageThresholdHigh();
        float getVoltageThresholdLow();
        //---
        uint16_t readWordFromRegisters(uint8_t msbAddress);
        bool writeWordToRegisters(uint8_t msbAddress, uint16_t value);
        uint8_t readByteFromRegister(uint8_t address);
        bool writeByteToRegister(uint8_t address, uint8_t value);
        uint8_t readByteFromFile(QString filename);
        bool writeByteToFile(QString fileName, uint8_t value);
        //---
        void getValues();
        void filterValues();
        //struct termios options;
        unsigned char sbuf[10];
        int fd;								// file descriptor of open port
        bool sendByte(char c, unsigned int delay);

        int openPort(void);
        void closePort(int fd);
        void writeData(int fd, int nbytes);
        void readData(int fd, int nbytes);

        void fillPortsInfo(QString portname);

        //init values
//        uint16_t curVolt;
//        int curCurrent;
//        uint16_t curAC;
        uint16_t ACT_H_default = 25718;
        uint16_t ACT_L_default = 5000;
        uint16_t Volt_H_default = 12500;
        uint16_t Volt_L_default = 9500;

        //moving-average-filtered values
        double m_filteredVolt;
        double m_filteredBat_persent;
        double m_filteredCurrent;
        int m_filteredAC;

        //raw values
        double m_volt;
        double m_bat_persent;
        double m_current;
        double m_temp;
        int m_AC;

        //moving average filter

        filter voltFilter = filter();
        filter currentFilter = filter();
        filter ACFilter = filter();
        filter ACPersentFilter = filter();

        bool m_bACChangeFlag = true;

        uint8_t m_status;
        uint8_t m_control;


        QSerialPort *m_serialPort;

        bool isDataReady = false;

        uint16_t _prescalerM;

    private:
        uint8_t _rSense;
        uint16_t _batteryCapacity;
};

#endif // LTC2943_H
