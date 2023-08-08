#include "ltc2943.h"

using namespace std;

LTC2943::LTC2943(uint8_t rSense)
{
    _rSense = rSense;
    _prescalerM = 0xFFFF;
    _batteryCapacity = 22000; // Default value when M = 4096
}




void LTC2943::fillPortsInfo(QString portname)
{

    m_serialPort->setPortName(portname);
    m_serialPort->setBaudRate(QSerialPort::Baud19200);
    m_serialPort->setDataBits(QSerialPort::Data8);
    m_serialPort->setParity(QSerialPort::NoParity);
    m_serialPort->setStopBits(QSerialPort::TwoStop);
    m_serialPort->setFlowControl(QSerialPort::NoFlowControl);
    if(m_serialPort->open(QIODevice::ReadWrite)){
    } else {
        qDebug() << "Failed to connect COMx";
        //QMessageBox::critical(this, tr("Error"), m_serialPort->errorString());
    }
}
uint16_t LTC2943::readWordFromRegisters(uint8_t msbAddress)
{
    uint16_t value = 0;
    uint8_t msb = 0;
    uint8_t lsb = 0;

    msb = readByteFromRegister(msbAddress);

    //usleep(10000);

    lsb = readByteFromRegister(msbAddress+1);

    value = (msb << 8) | lsb;

    return value;

}
bool LTC2943::writeWordToRegisters(uint8_t msbAddress, uint16_t value)
{
    writeByteToRegister(msbAddress, (uint8_t)(value>>8));

    //usleep(10000);

    return writeByteToRegister(msbAddress+1, (uint8_t)(value));
}

bool LTC2943::writeByteToRegister(uint8_t address, uint8_t value)
{
    uint8_t writeflag;

//    QByteArray data;
//    data = data.append(I2C2USB_START);
//    data = data.append((LTC2944_ADDRESS<<1));
//    data = data.append(address);
//    data = data.append(DATA_1BYTE);
//    data = data.append(value);

//    m_serialPort->write(data);

//    QEventLoop loop;
//    QObject::connect(m_serialPort, SIGNAL(readyRead()), &loop, SLOT(quit()));
//    loop.exec();
//    bool ok;
//    writeflag = (uint8_t) m_serialPort->readLine().toHex().toInt(&ok, 16);

//    //fd = sbuf[0];
//    return writeflag;
    switch(address)
    {
    case REG_A_STATUS:
        writeflag = writeByteToFile("status", value);
        break;
    case REG_B_CONTROL:
        writeflag = writeByteToFile("control", value);
        break;
    case REG_C_ACC_CHG_MSB:
        writeflag = writeByteToFile("accumulated_charge_msb", value);
        break;
    case REG_D_ACC_CHG_LSB:
        writeflag = writeByteToFile("accumulated_charge_lsb", value);
        break;
    case REG_E_CHG_THR_H_MSB:
        writeflag = writeByteToFile("charge_threshold_high_msb", value);
        break;
    case REG_F_CHG_THR_H_LSB:
        writeflag = writeByteToFile("charge_threshold_high_lsb", value);
        break;
    case REG_G_CHG_THR_L_MSB:
        writeflag = writeByteToFile("charge_threshold_low_msb", value);
        break;
    case REG_H_CHG_THR_L_LSB:
        writeflag = writeByteToFile("charge_threshold_low_lsb", value);
        break;
    case REG_I_VOLTAGE_MSB:
        writeflag = writeByteToFile("voltage_msb", value);
        break;
    case REG_J_VOLTAGE_LSB:
        writeflag = writeByteToFile("voltage_lsb", value);
        break;
    case REG_K_VOLTAGE_THR_H_MSB:
        writeflag = writeByteToFile("voltage_threshold_high_msb", value);
        break;
    case REG_L_VOLTAGE_THR_H_LSB:
        writeflag = writeByteToFile("voltage_threshold_high_lsb", value);
        break;
    case REG_M_VOLTAGE_THR_L_MSB:
        writeflag = writeByteToFile("voltage_threshold_low_msb", value);
        break;
    case REG_N_VOLTAGE_THR_L_LSB:
        writeflag = writeByteToFile("voltage_threshold_low_lsb", value);
        break;
    case REG_O_CURRENT_MSB:
        writeflag = writeByteToFile("current_msb", value);
        break;
    case REG_P_CURRENT_LSB:
        writeflag = writeByteToFile("current_lsb", value);
        break;
    case REG_Q_CURRENT_THR_H_MSB:
        writeflag = writeByteToFile("current_threshold_high_msb", value);
        break;
    case REG_R_CURRENT_THR_H_LSB:
        writeflag = writeByteToFile("current_threshold_high_lsb", value);
        break;
    case REG_S_CURRENT_THR_L_MSB:
        writeflag = writeByteToFile("current_threshold_low_msb", value);
        break;
    case REG_T_CURRENT_THR_L_LSB:
        writeflag = writeByteToFile("current_threshold_low_lsb", value);
        break;
    case REG_U_TEMP_MSB:
        writeflag = writeByteToFile("temperature_msb", value);
        break;
    case REG_V_TEMP_LSB:
        writeflag = writeByteToFile("temperature_lsb", value);
        break;
    case REG_W_TEMP_THR_H:
        writeflag = writeByteToFile("temperature_threshold_high", value);
        break;
    case REG_X_TEMP_THR_L:
        writeflag = writeByteToFile("temperature_threshold_low", value);
        break;
    case 0x18:
        writeflag = writeByteToFile("test", value);
        break;
    default:
        break;
    }

    return writeflag;

}

bool LTC2943::writeByteToFile(QString fileName, uint8_t value)
{
    QString path = "/sys/class/power_supply/ltc2943/";
    QFile file(path+fileName);
    uint8_t ret;

    if(file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    {
        ret = file.write(QString::number(value).toLatin1());
        file.close();
        if(ret == 1)
        {
            return true;
        }
    }
    return false;

}


uint8_t LTC2943::readByteFromRegister(uint8_t address)
{
    uint8_t value;

//    QByteArray data;
//    data = data.append(I2C2USB_START);
//    data = data.append((LTC2944_ADDRESS<<1)+1);
//    data = data.append(address);
//    data = data.append(DATA_1BYTE);

//    m_serialPort->write(data);

//    QEventLoop loop;
//    QObject::connect(m_serialPort, SIGNAL(readyRead()), &loop, SLOT(quit()));
//    loop.exec();
//    bool ok;
//    value = (uint8_t) m_serialPort->readLine().toHex().toInt(&ok, 16);

    switch(address)
    {
    case REG_A_STATUS:
        value = readByteFromFile("status");
        break;
    case REG_B_CONTROL:
        value = readByteFromFile("control");
        break;
    case REG_C_ACC_CHG_MSB:
        value = readByteFromFile("accumulated_charge_msb");
        break;
    case REG_D_ACC_CHG_LSB:
        value = readByteFromFile("accumulated_charge_lsb");
        break;
    case REG_E_CHG_THR_H_MSB:
        value = readByteFromFile("charge_threshold_high_msb");
        break;
    case REG_F_CHG_THR_H_LSB:
        value = readByteFromFile("charge_threshold_high_lsb");
        break;
    case REG_G_CHG_THR_L_MSB:
        value = readByteFromFile("charge_threshold_low_msb");
        break;
    case REG_H_CHG_THR_L_LSB:
        value = readByteFromFile("charge_threshold_low_lsb");
        break;
    case REG_I_VOLTAGE_MSB:
        value = readByteFromFile("voltage_msb");
        break;
    case REG_J_VOLTAGE_LSB:
        value = readByteFromFile("voltage_lsb");
        break;
    case REG_K_VOLTAGE_THR_H_MSB:
        value = readByteFromFile("voltage_threshold_high_msb");
        break;
    case REG_L_VOLTAGE_THR_H_LSB:
        value = readByteFromFile("voltage_threshold_high_lsb");
        break;
    case REG_M_VOLTAGE_THR_L_MSB:
        value = readByteFromFile("voltage_threshold_low_msb");
        break;
    case REG_N_VOLTAGE_THR_L_LSB:
        value = readByteFromFile("voltage_threshold_low_lsb");
        break;
    case REG_O_CURRENT_MSB:
        value = readByteFromFile("current_msb");
        break;
    case REG_P_CURRENT_LSB:
        value = readByteFromFile("current_lsb");
        break;
    case REG_Q_CURRENT_THR_H_MSB:
        value = readByteFromFile("current_threshold_high_msb");
        break;
    case REG_R_CURRENT_THR_H_LSB:
        value = readByteFromFile("current_threshold_high_lsb");
        break;
    case REG_S_CURRENT_THR_L_MSB:
        value = readByteFromFile("current_threshold_low_msb");
        break;
    case REG_T_CURRENT_THR_L_LSB:
        value = readByteFromFile("current_threshold_low_lsb");
        break;
    case REG_U_TEMP_MSB:
        value = readByteFromFile("temperature_msb");
        break;
    case REG_V_TEMP_LSB:
        value = readByteFromFile("temperature_lsb");
        break;
    case REG_W_TEMP_THR_H:
        value = readByteFromFile("temperature_threshold_high");
        break;
    case REG_X_TEMP_THR_L:
        value = readByteFromFile("temperature_threshold_low");
        break;
    default:
        break;
    }

    return value;
}


uint8_t LTC2943::readByteFromFile(QString filename)
{
    QString path = "/sys/class/power_supply/ltc2943/";
    QFile file(path+filename);
    uint8_t ret;

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ret = file.readAll().toInt();
        file.close();
        if(ret>=0 && ret<=255)
        {
            return ret;
        }
    }
    return -1;
}


//main functions//


void LTC2943::setADCMode(uint8_t mode)
{
    if (mode > ADC_MODE_AUTO) {
        return;
    }

    uint8_t value = readByteFromRegister(REG_B_CONTROL);
    value &= ADC_MODE_MASK;
    value |= (mode << B_ADC_MODE_OFFSET);
    writeByteToRegister(REG_B_CONTROL, value);
}

void LTC2943::setPrescalerM(uint16_t m)
{
    if (m < 1 || m > 4096) {
        return;
    }

    // Updates instance variable to avoid unnecessary access to register
    _prescalerM = m;
    m = findExponentOfPowerOfTwo(m);

    uint8_t value = readByteFromRegister(REG_B_CONTROL);
    value &= PRESCALER_M_MASK;
    value |= (m << B_PRESCALER_M_OFFSET);
    writeByteToRegister(REG_B_CONTROL, value);
}

uint8_t LTC2943::findExponentOfPowerOfTwo(uint16_t value) { //返回对应B[5:3]的值
    if (value > 1024) {
        return 6;
    }

    for (uint8_t i = 0; i < 6; i++) {
        if ((value >> (i * 2)) & 1) {
            return i;
        }
    }
}
//setAnalog pass
void LTC2943::configureALCC(uint8_t mode)
{
    if (mode >= ALCC_MODE_NOT_ALLOWED) {
        return;
    }

    uint8_t value = readByteFromRegister(REG_B_CONTROL);
    value &= ALCC_CONFIG_MASK;
    value |= (mode << B_ALCC_CONFIG_OFFSET);
    writeByteToRegister(REG_B_CONTROL, value);
}

//void LTC2943::setVoltageThresholds(float high, float low)
//{
//    uint32_t _high = high * 0xFFFF / 23.6;
//    uint32_t _low = low * 0xFFFF / 23.6;
//    if(_high > 0xFFFF){
//        _high = 0xFFFF;
//    }else if(_high < 0){
//        _high = 0;
//    }
//    if(_low > 0xFFFF){
//        _low = 0xFFFF;
//    }else if(_low < 0){
//        _low = 0;
//    }
//    writeWordToRegisters(REG_K_VOLTAGE_THR_H_MSB, (uint16_t) _high);
//    writeWordToRegisters(REG_M_VOLTAGE_THR_L_MSB, (uint16_t) _low);
//}

float LTC2943::getVoltage(bool oneShot) {
    if (oneShot) {
        setADCMode(ADC_MODE_MANUAL);
        //delay(10);
        usleep(10000);
    }
    uint16_t value = readWordFromRegisters(REG_I_VOLTAGE_MSB);
    return 23.6 * ((float) value / 0xFFFF) - 0.03; // V callibration: -0.5V
}

int LTC2943::getRawAccumulatedCharge() {

//    uint8_t status = readByteFromRegister(REG_A_STATUS);
    int AC = readWordFromRegisters(REG_C_ACC_CHG_MSB);
    int AC_int;

    //overFlow underflow
   /* if((status&0b00100000)<<5)
    {
        if((status&0b00000100)<<2)
        {
            AC_int = 65535-AC;
            return -AC_int;
        } else {
            AC_int = 65535+AC;
            return AC_int;
        }
    }*/
    return AC;
}

float LTC2943::getCurrent(bool oneShot) {
    if (oneShot) {
        setADCMode(ADC_MODE_MANUAL);
        //delay(10);
        usleep(10000);
    }
    int x;
    uint16_t value = readWordFromRegisters(REG_O_CURRENT_MSB);
    int Rsense = 15;
    float value2;
    if(value >= 32767){
        value = value-32767;
        x=0;
    } else {
        value = 32767-value;
        x=1;
    }
    value2 = ((value * 60.0) / 32767.0 );
    value2 = value2 / Rsense;

    if(x==0)    value2 = value2;
    else        value2 = -value2;

//    if(value2<=0.100 && value2 >=-0.100){
//        value2 = 0;
//    }//100mA 이하 전류 무시

    return value2;
   // return ((float) value / 0x7FFF - 1) * 64 / _rSense; // A
}

void LTC2943::setChargeThresholdH(uint16_t high) {
    writeWordToRegisters(REG_E_CHG_THR_H_MSB, high);
}

void LTC2943::setChargeThresholdL(uint16_t low) {
    writeWordToRegisters(REG_G_CHG_THR_L_MSB, low);
}

void LTC2943::setRawAccumulatedCharge(uint16_t charge) {
    writeWordToRegisters(REG_C_ACC_CHG_MSB, charge);
}


void LTC2943::startMeasurement() {
    uint8_t value = readByteFromRegister(REG_B_CONTROL);
    value &= SHUTDOWN_MASK;
    writeByteToRegister(REG_B_CONTROL, value);
}

uint16_t LTC2943::getPersent(uint16_t AC)
{
    uint16_t ACT_H;
    uint16_t ACT_L;
    uint32_t ACT_Persent;
    uint32_t AC_data;

    ACT_H = readWordFromRegisters(REG_E_CHG_THR_H_MSB);
    ACT_L = readWordFromRegisters(REG_G_CHG_THR_L_MSB);

    ACT_Persent = ((ACT_H-AC_MARGIN)-(ACT_L+AC_MARGIN));

    if(AC>=(ACT_H - AC_MARGIN))        AC_data = ((ACT_H - AC_MARGIN)-(ACT_L + AC_MARGIN))*10000;
    else if(AC > (ACT_L + AC_MARGIN))  AC_data = (AC - (ACT_L + AC_MARGIN))*10000;
    else if(AC <= (ACT_L + AC_MARGIN)) AC_data = 0;


    if(ACT_Persent!=0)  ACT_Persent = AC_data/ACT_Persent;
    else {
//        qDebug() << "devider is 0";
        return ACT_Persent;
    }

    return ACT_Persent;
}


void LTC2943::setChargeThresholds(uint16_t high, uint16_t low) {
    writeWordToRegisters(REG_E_CHG_THR_H_MSB, high);
    writeWordToRegisters(REG_G_CHG_THR_L_MSB, low);
}

void LTC2943::presetAC(uint32_t VOLT, uint16_t VoltT_H, uint16_t VoltT_L)
{
    uint32_t volt_data[3];
    uint32_t ACL_data[3];

    uint16_t ACT_H, ACT_L;

    ACT_H = readWordFromRegisters(REG_E_CHG_THR_H_MSB);
    ACT_L = readWordFromRegisters(REG_G_CHG_THR_L_MSB);
    //qDebug() << ACT_H<<ACT_L;
    if(VOLT<= VoltT_L)  VOLT = VoltT_L;
    if(VOLT>= VoltT_H)  VOLT = VoltT_H;

    volt_data[0] = VoltT_H - VoltT_L;
    volt_data[1] = VOLT - VoltT_L;
    volt_data[2] = (volt_data[1]*10000)/volt_data[0];
    //qDebug() << VoltT_H<<VOLT<<VoltT_L;
    ACL_data[0] = ACT_H-ACT_L;
    ACL_data[1] = (ACL_data[0]*volt_data[2]) + (ACT_L*10000);
    ACL_data[2] = ACL_data[1]/10000;

    //qDebug() << ACL_data[2];
    if(ACL_data[2]>=60000)      ACL_data[2]=60000;
    writeWordToRegisters(REG_C_ACC_CHG_MSB, ACL_data[2]);
}


uint16_t LTC2943::getACThresholdH()
{
    return readWordFromRegisters(REG_E_CHG_THR_H_MSB);
}

uint16_t LTC2943::getACThresholdL()
{
    return readWordFromRegisters(REG_G_CHG_THR_L_MSB);
}

void LTC2943::getPrescalerM() {
    if (_prescalerM == 0xFFFF) {
        // Needs to obtain M from register B
        uint8_t value = readByteFromRegister(REG_B_CONTROL);
        value &= ~PRESCALER_M_MASK;
        _prescalerM = value >> B_PRESCALER_M_OFFSET;
        if (_prescalerM > 6) {
            _prescalerM = 6;
        }
        _prescalerM = 1 << (_prescalerM << 1);
    }
}


void LTC2943::getValues()
{
    //get raw values
    m_volt = getVoltage();
    m_AC = getRawAccumulatedCharge();
    m_current = getCurrent();
    m_bat_persent = getPersent(m_AC);


}

void LTC2943::filterValues()
{
    //moving average filter
    voltFilter.insertIntoRawArray(m_volt);
    currentFilter.insertIntoRawArray(m_current);
    ACFilter.insertIntoRawArray(m_AC);
    ACPersentFilter.insertIntoRawArray(m_bat_persent);

    m_filteredVolt = voltFilter.movingAverageFilter();
    m_filteredCurrent = currentFilter.movingAverageFilter();
    m_filteredAC = ACFilter.movingAverageFilter();
    m_filteredBat_persent = ACPersentFilter.movingAverageFilter();
}


void LTC2943::setVoltageThresholds(float high, float low) {
    uint32_t _high = high * 0xFFFF / 23.6;
    uint32_t _low = low * 0xFFFF / 23.6;
    if(_high > 0xFFFF){
        _high = 0xFFFF;
    }else if(_high < 0){
        _high = 0;
    }
    if(_low > 0xFFFF){
        _low = 0xFFFF;
    }else if(_low < 0){
        _low = 0;
    }
    writeWordToRegisters(REG_K_VOLTAGE_THR_H_MSB, (uint16_t) _high);
    writeWordToRegisters(REG_M_VOLTAGE_THR_L_MSB, (uint16_t) _low);
}


float LTC2943::getVoltageThresholdHigh()
{
    uint16_t value = readWordFromRegisters(REG_K_VOLTAGE_THR_H_MSB);
    return 23.6 * ((float) value / 0xFFFF); // V
}

float LTC2943::getVoltageThresholdLow()
{
    uint16_t value = readWordFromRegisters(REG_M_VOLTAGE_THR_L_MSB);
    return 23.6 * ((float) value / 0xFFFF); // V
}



