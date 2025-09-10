/**
 * \par Copyright (C), 2012-2016, MakeBlock
 * \class MeUltrasonicSensor
 * \brief   Driver for Me ultrasonic sensor device.
 * @file    MeUltrasonicSensor.h
 * @author  MakeBlock
 * @version V1.0.1
 * @date    2016/06/25
 * @brief   Header for for MeUltrasonicSensor.cpp module
 *
 * \par Copyright
 * This software is Copyright (C), 2012-2016, MakeBlock. Use is subject to license \n
 * conditions. The main licensing options available are GPL V2 or Commercial: \n
 *
 * \par Open Source Licensing GPL V2
 * This is the appropriate option if you want to share the source code of your \n
 * application with everyone you distribute it to, and you also want to give them \n
 * the right to share who uses it. If you wish to use this software under Open \n
 * Source Licensing, you must contribute all your source code to the open source \n
 * community in accordance with the GPL Version 2 when your application is \n
 * distributed. See http://www.gnu.org/copyleft/gpl.html
 *
 * \par Copyright
 * This software is Copyright (C), 2012-2015, MakeBlock. Use is subject to license \n
 * conditions. The main licensing options available are GPL V2 or Commercial: \n
 *
 * \par Open Source Licensing GPL V2
 * This is the appropriate option if you want to share the source code of your \n
 * application with everyone you distribute it to, and you also want to give them \n
 * the right to share who uses it. If you wish to use this software under Open \n
 * Source Licensing, you must contribute all your source code to the open source \n
 * community in accordance with the GPL Version 2 when your application is \n
 * distributed. See http://www.gnu.org/copyleft/gpl.html
 *
 * \par Description
 * This file is a drive for Me ultrasonic sensor device, It supports ultrasonic sensor
 * V3.0 provided by the MakeBlock.
 *
 * \par Method List:
 *
 *    1. void MeUltrasonicSensor::setpin(uint8_t SignalPin)
 *    2. double MeUltrasonicSensor::distanceCm(uint16_t MAXcm)
 *    3. double MeUltrasonicSensor::distanceInch(uint16_t MAXinch)
 *    4. long MeUltrasonicSensor::measure(unsigned long timeout)
 *
 * \par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Mark Yan         2015/09/04     1.0.0            Rebuild the old lib.
 * Mark Yan         2016/06/25     1.0.2            Modify Read mechanism of ultrasonic waves.
 * </pre>
 */
#ifndef MeUltrasonicSensor_H
#define MeUltrasonicSensor_H

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include "MeConfig.h"

#ifdef ME_PORT_DEFINED
#include "MePort.h"
#endif // ME_PORT_DEFINED

/**
 * Class: MeUltrasonicSensor
 * \par Description
 * Declaration of Class MeUltrasonicSensor.
 */
#ifndef ME_PORT_DEFINED
class MeUltrasonicSensor
#else // !ME_PORT_DEFINED
class MeUltrasonicSensor : public MePort
#endif // !ME_PORT_DEFINED
{
public:
#ifdef ME_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the ultrasonic sensor to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
 */
  MeUltrasonicSensor(void);

/**
 * Alternate Constructor which can call your own function to map the ultrasonic Sensor to arduino port
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
  MeUltrasonicSensor(uint8_t port);
#else // ME_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the ultrasonic Sensor to arduino port,
 * it will assigned the signal pin.
 * \param[in]
 *   port - arduino port(should analog pin)
 */
  MeUltrasonicSensor(uint8_t port);
#endif // ME_PORT_DEFINED

/**
 * \par Function
 *   setpin
 * \par Description
 *   Reset the ultrasonic Sensor available PIN by its arduino port.
 * \param[in]
 *   SignalPin - arduino port for sensor read(should analog pin)
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
  void setpin(uint8_t SignalPin);
  
/**
 * \par Function
 *   distanceCm
 * \par Description
 *   Centimeters return the distance
 * \param[in]
 *   MAXcm - The Max centimeters can be measured, the default value is 400.
 * \par Output
 *   None
 * \return
 *   The distance measurement in centimeters
 * \par Others
 *   None
 */
  double distanceCm(uint16_t = 400);

/**
 * \par Function
 *   distanceInch
 * \par Description
 *   Inch return the distance
 * \param[in]
 *   MAXinch - The Max inch can be measured, the default value is 180.
 * \par Output
 *   None
 * \return
 *   The distance measurement in inch
 * \par Others
 *   None
 */
  double distanceInch(uint16_t = 180);

/**
 * \par Function
 *   measure
 * \par Description
 *   To get the duration of the ultrasonic sensor
 * \param[in]
 *   timeout - This value is used to define the measurement range, The
 *   default value is 30000.
 * \par Output
 *   None
 * \return
 *   The duration value associated with distance
 * \par Others
 *   None
 */
  long measure(unsigned long = 30000);


  //TODO: ADDED FAST VERSION
  /**
   * \par Function
   *   distanceCmFast
   * \par Description
   *   Ultra-fast centimeters measurement with no safety checks or rate limiting
   * \param[in]
   *   MAXcm - The Max centimeters for timeout calculation (recommended: 10-50cm for best speed)
   * \par Output
   *   None
   * \return
   *   The distance measurement in centimeters, or MAXcm if timeout/no object
   * \par Others
   *   RESTRICTIONS:
   *   - No rate limiting: Can be called continuously but may stress sensor
   *   - No input validation: MAXcm should be 5-200cm (outside range may cause issues)  
   *   - No caching: Every call triggers new measurement (high CPU usage if called rapidly)
   *   - Blocking: Will block for up to (MAXcm * 70)μs waiting for echo
   *   - Thread safety: Not thread-safe, don't call from multiple tasks simultaneously
   *   PERFORMANCE: Optimized for MAXcm ≤ 40cm (sub-3ms measurements)
   */
  double distanceCmFast(uint16_t MAXcm = 40);


    /**
   * \par Function
   *   measureFast  
   * \par Description
   *   Ultra-fast ultrasonic measurement with calculated timeout, no safety checks
   * \param[in]
   *   timeout - Timeout in microseconds (recommended: distance_cm * 70μs)
   * \par Output
   *   None
   * \return
   *   The duration value in microseconds, 0 if timeout
   * \par Others
   *   RESTRICTIONS:
   *   - No rate limiting: Measures immediately every call (can stress sensor)
   *   - No timeout validation: Values <500μs or >50000μs may cause undefined behavior
   *   - Blocking operation: Will block thread for up to 'timeout' microseconds  
   *   - Hardware dependent: Assumes s2 pin is properly configured
   *   - No error handling: Hardware failures return 0 (indistinguishable from timeout)
   *   PERFORMANCE: Direct hardware access, minimal overhead (~10μs + measurement time)
   */
  long measureFast(unsigned long timeout);

private:
  volatile uint8_t  _SignalPin;
  volatile bool _measureFlag;
  volatile long _lastEnterTime;
  volatile float _measureValue;
};

#endif 

