/*********************************************************************
 *
 * $Id: yocto_power.cpp 10245 2013-03-11 13:35:54Z seb $
 *
 * Implements yFindPower(), the high-level API for Power functions
 *
 * - - - - - - - - - License information: - - - - - - - - - 
 *
 * Copyright (C) 2011 and beyond by Yoctopuce Sarl, Switzerland.
 *
 * 1) If you have obtained this file from www.yoctopuce.com,
 *    Yoctopuce Sarl licenses to you (hereafter Licensee) the
 *    right to use, modify, copy, and integrate this source file
 *    into your own solution for the sole purpose of interfacing
 *    a Yoctopuce product with Licensee's solution.
 *
 *    The use of this file and all relationship between Yoctopuce 
 *    and Licensee are governed by Yoctopuce General Terms and 
 *    Conditions.
 *
 *    THE SOFTWARE AND DOCUMENTATION ARE PROVIDED 'AS IS' WITHOUT
 *    WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING 
 *    WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS 
 *    FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO
 *    EVENT SHALL LICENSOR BE LIABLE FOR ANY INCIDENTAL, SPECIAL,
 *    INDIRECT OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, 
 *    COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR 
 *    SERVICES, ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT 
 *    LIMITED TO ANY DEFENSE THEREOF), ANY CLAIMS FOR INDEMNITY OR
 *    CONTRIBUTION, OR OTHER SIMILAR COSTS, WHETHER ASSERTED ON THE
 *    BASIS OF CONTRACT, TORT (INCLUDING NEGLIGENCE), BREACH OF
 *    WARRANTY, OR OTHERWISE.
 *
 * 2) If your intent is not to interface with Yoctopuce products,
 *    you are not entitled to use, read or create any derived
 *    material from this source file.
 *
 *********************************************************************/


#define _CRT_SECURE_NO_DEPRECATE //do not use windows secure crt
#include "yocto_power.h"
#include "yapi/yjson.h"
#include "yapi/yapi.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//--- (YPower implementation)

const string YPower::LOGICALNAME_INVALID = "!INVALID!";
const string YPower::ADVERTISEDVALUE_INVALID = "!INVALID!";
const string YPower::UNIT_INVALID = "!INVALID!";
const double YPower::CURRENTVALUE_INVALID = -DBL_MAX;
const double YPower::LOWESTVALUE_INVALID = -DBL_MAX;
const double YPower::HIGHESTVALUE_INVALID = -DBL_MAX;
const double YPower::CURRENTRAWVALUE_INVALID = -DBL_MAX;
const double YPower::RESOLUTION_INVALID = -DBL_MAX;
const string YPower::CALIBRATIONPARAM_INVALID = "!INVALID!";
const double YPower::COSPHI_INVALID = -DBL_MAX;
const double YPower::METER_INVALID = -DBL_MAX;

std::map<string,YPower*> YPower::_PowerCache;

int YPower::_parse(yJsonStateMachine& j)
{
    if(yJsonParse(&j) != YJSON_PARSE_AVAIL || j.st != YJSON_PARSE_STRUCT) {
    failed:
        return -1;
    }
    while(yJsonParse(&j) == YJSON_PARSE_AVAIL && j.st == YJSON_PARSE_MEMBNAME) {
        if(!strcmp(j.token, "logicalName")) {
            if(yJsonParse(&j) != YJSON_PARSE_AVAIL) return -1;
            _logicalName =  _parseString(j);
        } else if(!strcmp(j.token, "advertisedValue")) {
            if(yJsonParse(&j) != YJSON_PARSE_AVAIL) return -1;
            _advertisedValue =  _parseString(j);
        } else if(!strcmp(j.token, "unit")) {
            if(yJsonParse(&j) != YJSON_PARSE_AVAIL) return -1;
            _unit =  _parseString(j);
        } else if(!strcmp(j.token, "currentValue")) {
            if(yJsonParse(&j) != YJSON_PARSE_AVAIL) return -1;
            _currentValue =  floor(atof(j.token)/65.536+.5) / 1000;
        } else if(!strcmp(j.token, "lowestValue")) {
            if(yJsonParse(&j) != YJSON_PARSE_AVAIL) return -1;
            _lowestValue =  floor(atof(j.token)/65.536+.5) / 1000;
        } else if(!strcmp(j.token, "highestValue")) {
            if(yJsonParse(&j) != YJSON_PARSE_AVAIL) return -1;
            _highestValue =  floor(atof(j.token)/65.536+.5) / 1000;
        } else if(!strcmp(j.token, "currentRawValue")) {
            if(yJsonParse(&j) != YJSON_PARSE_AVAIL) return -1;
            _currentRawValue =  atof(j.token)/65536.0;
        } else if(!strcmp(j.token, "resolution")) {
            if(yJsonParse(&j) != YJSON_PARSE_AVAIL) return -1;
            _resolution =  1.0 / floor(65536.0/atof(j.token)+.5);
        } else if(!strcmp(j.token, "calibrationParam")) {
            if(yJsonParse(&j) != YJSON_PARSE_AVAIL) return -1;
            _calibrationParam =  _parseString(j);
        } else if(!strcmp(j.token, "cosPhi")) {
            if(yJsonParse(&j) != YJSON_PARSE_AVAIL) return -1;
            _cosPhi =  floor(atof(j.token)/655.36+.5) / 100;
        } else if(!strcmp(j.token, "meter")) {
            if(yJsonParse(&j) != YJSON_PARSE_AVAIL) return -1;
            _meter =  floor(atof(j.token)/65.536+.5) / 1000;
        } else if(!strcmp(j.token, "meterTimer")) {
            if(yJsonParse(&j) != YJSON_PARSE_AVAIL) return -1;
            _meterTimer =  atoi(j.token);
        } else {
            // ignore unknown field
            yJsonSkip(&j, 1);
        }
    }
    if(j.st != YJSON_PARSE_STRUCT) goto failed;
    return 0;
}

/**
 * Returns the logical name of the electrical power sensor.
 * 
 * @return a string corresponding to the logical name of the electrical power sensor
 * 
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
string YPower::get_logicalName(void)
{
    if(_cacheExpiration <= YAPI::GetTickCount()) {
        if(YISERR(load(YAPI::DefaultCacheValidity))) return Y_LOGICALNAME_INVALID;
    }
    return _logicalName;
}

/**
 * Changes the logical name of the electrical power sensor. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 * 
 * @param newval : a string corresponding to the logical name of the electrical power sensor
 * 
 * @return YAPI_SUCCESS if the call succeeds.
 * 
 * On failure, throws an exception or returns a negative error code.
 */
int YPower::set_logicalName(const string& newval)
{
    string rest_val;
    rest_val = newval;
    return _setAttr("logicalName", rest_val);
}

/**
 * Returns the current value of the electrical power sensor (no more than 6 characters).
 * 
 * @return a string corresponding to the current value of the electrical power sensor (no more than 6 characters)
 * 
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
string YPower::get_advertisedValue(void)
{
    if(_cacheExpiration <= YAPI::GetTickCount()) {
        if(YISERR(load(YAPI::DefaultCacheValidity))) return Y_ADVERTISEDVALUE_INVALID;
    }
    return _advertisedValue;
}

/**
 * Returns the measuring unit for the measured value.
 * 
 * @return a string corresponding to the measuring unit for the measured value
 * 
 * On failure, throws an exception or returns Y_UNIT_INVALID.
 */
string YPower::get_unit(void)
{
    if(_unit == Y_UNIT_INVALID) {
        if(YISERR(load(YAPI::DefaultCacheValidity))) return Y_UNIT_INVALID;
    }
    return _unit;
}

/**
 * Returns the current measured value.
 * 
 * @return a floating point number corresponding to the current measured value
 * 
 * On failure, throws an exception or returns Y_CURRENTVALUE_INVALID.
 */
double YPower::get_currentValue(void)
{
    if(_cacheExpiration <= YAPI::GetTickCount()) {
        if(YISERR(load(YAPI::DefaultCacheValidity))) return Y_CURRENTVALUE_INVALID;
    }
    double res = YAPI::_applyCalibration(_currentRawValue, _calibrationParam, _calibrationOffset, _resolution);
    if(res != Y_CURRENTVALUE_INVALID) return res;
    return _currentValue;
}

/**
 * Changes the recorded minimal value observed.
 * 
 * @param newval : a floating point number corresponding to the recorded minimal value observed
 * 
 * @return YAPI_SUCCESS if the call succeeds.
 * 
 * On failure, throws an exception or returns a negative error code.
 */
int YPower::set_lowestValue(double newval)
{
    string rest_val;
    char buf[32]; sprintf(buf,"%d", (int)floor(newval*65536.0 +0.5)); rest_val = string(buf);
    return _setAttr("lowestValue", rest_val);
}

/**
 * Returns the minimal value observed.
 * 
 * @return a floating point number corresponding to the minimal value observed
 * 
 * On failure, throws an exception or returns Y_LOWESTVALUE_INVALID.
 */
double YPower::get_lowestValue(void)
{
    if(_cacheExpiration <= YAPI::GetTickCount()) {
        if(YISERR(load(YAPI::DefaultCacheValidity))) return Y_LOWESTVALUE_INVALID;
    }
    return _lowestValue;
}

/**
 * Changes the recorded maximal value observed.
 * 
 * @param newval : a floating point number corresponding to the recorded maximal value observed
 * 
 * @return YAPI_SUCCESS if the call succeeds.
 * 
 * On failure, throws an exception or returns a negative error code.
 */
int YPower::set_highestValue(double newval)
{
    string rest_val;
    char buf[32]; sprintf(buf,"%d", (int)floor(newval*65536.0 +0.5)); rest_val = string(buf);
    return _setAttr("highestValue", rest_val);
}

/**
 * Returns the maximal value observed.
 * 
 * @return a floating point number corresponding to the maximal value observed
 * 
 * On failure, throws an exception or returns Y_HIGHESTVALUE_INVALID.
 */
double YPower::get_highestValue(void)
{
    if(_cacheExpiration <= YAPI::GetTickCount()) {
        if(YISERR(load(YAPI::DefaultCacheValidity))) return Y_HIGHESTVALUE_INVALID;
    }
    return _highestValue;
}

/**
 * Returns the uncalibrated, unrounded raw value returned by the sensor.
 * 
 * @return a floating point number corresponding to the uncalibrated, unrounded raw value returned by the sensor
 * 
 * On failure, throws an exception or returns Y_CURRENTRAWVALUE_INVALID.
 */
double YPower::get_currentRawValue(void)
{
    if(_cacheExpiration <= YAPI::GetTickCount()) {
        if(YISERR(load(YAPI::DefaultCacheValidity))) return Y_CURRENTRAWVALUE_INVALID;
    }
    return _currentRawValue;
}

/**
 * Returns the resolution of the measured values. The resolution corresponds to the numerical precision
 * of the values, which is not always the same as the actual precision of the sensor.
 * 
 * @return a floating point number corresponding to the resolution of the measured values
 * 
 * On failure, throws an exception or returns Y_RESOLUTION_INVALID.
 */
double YPower::get_resolution(void)
{
    if(_resolution == Y_RESOLUTION_INVALID) {
        if(YISERR(load(YAPI::DefaultCacheValidity))) return Y_RESOLUTION_INVALID;
    }
    return _resolution;
}

string YPower::get_calibrationParam(void)
{
    if(_cacheExpiration <= YAPI::GetTickCount()) {
        if(YISERR(load(YAPI::DefaultCacheValidity))) return Y_CALIBRATIONPARAM_INVALID;
    }
    return _calibrationParam;
}

int YPower::set_calibrationParam(const string& newval)
{
    string rest_val;
    rest_val = newval;
    return _setAttr("calibrationParam", rest_val);
}

/**
 * Configures error correction data points, in particular to compensate for
 * a possible perturbation of the measure caused by an enclosure. It is possible
 * to configure up to five correction points. Correction points must be provided
 * in ascending order, and be in the range of the sensor. The device will automatically
 * perform a lineat interpolatation of the error correction between specified
 * points. Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 * 
 * For more information on advanced capabilities to refine the calibration of
 * sensors, please contact support@yoctopuce.com.
 * 
 * @param rawValues : array of floating point numbers, corresponding to the raw
 *         values returned by the sensor for the correction points.
 * @param refValues : array of floating point numbers, corresponding to the corrected
 *         values for the correction points.
 * 
 * @return YAPI_SUCCESS if the call succeeds.
 * 
 * On failure, throws an exception or returns a negative error code.
 */
int YPower::calibrateFromPoints(vector<double> rawValues,vector<double> refValues)
{
    string rest_val;
    rest_val = this->_encodeCalibrationPoints(rawValues,refValues,_resolution,_calibrationOffset,_calibrationParam);
    return _setAttr("calibrationParam", rest_val);
}

int YPower::loadCalibrationPoints(vector<double> rawValues,vector<double> refValues)
{
    if(_cacheExpiration <= YAPI::GetTickCount()) {
        if(YISERR(load(YAPI::DefaultCacheValidity))) return _lastErrorType;
    }
    return this->_decodeCalibrationPoints(_calibrationParam,rawValues,refValues,_resolution,_calibrationOffset);
}

/**
 * Returns the power factor (the ratio between the real power consumed,
 * measured in W, and the apparent power provided, measured in VA).
 * 
 * @return a floating point number corresponding to the power factor (the ratio between the real power consumed,
 *         measured in W, and the apparent power provided, measured in VA)
 * 
 * On failure, throws an exception or returns Y_COSPHI_INVALID.
 */
double YPower::get_cosPhi(void)
{
    if(_cacheExpiration <= YAPI::GetTickCount()) {
        if(YISERR(load(YAPI::DefaultCacheValidity))) return Y_COSPHI_INVALID;
    }
    return _cosPhi;
}

int YPower::set_meter(double newval)
{
    string rest_val;
    char buf[32]; sprintf(buf,"%d", (int)floor(newval*65536.0 +0.5)); rest_val = string(buf);
    return _setAttr("meter", rest_val);
}

/**
 * Returns the energy counter, maintained by the wattmeter by integrating the power consumption over time.
 * Note that this counter is reset at each start of the device.
 * 
 * @return a floating point number corresponding to the energy counter, maintained by the wattmeter by
 * integrating the power consumption over time
 * 
 * On failure, throws an exception or returns Y_METER_INVALID.
 */
double YPower::get_meter(void)
{
    if(_cacheExpiration <= YAPI::GetTickCount()) {
        if(YISERR(load(YAPI::DefaultCacheValidity))) return Y_METER_INVALID;
    }
    return _meter;
}

/**
 * Returns the elapsed time since last energy counter reset, in seconds.
 * 
 * @return an integer corresponding to the elapsed time since last energy counter reset, in seconds
 * 
 * On failure, throws an exception or returns Y_METERTIMER_INVALID.
 */
unsigned YPower::get_meterTimer(void)
{
    if(_cacheExpiration <= YAPI::GetTickCount()) {
        if(YISERR(load(YAPI::DefaultCacheValidity))) return Y_METERTIMER_INVALID;
    }
    return _meterTimer;
}

YPower *YPower::nextPower(void)
{
    string  hwid;
    
    if(YISERR(_nextFunction(hwid)) || hwid=="") {
        return NULL;
    }
    return yFindPower(hwid);
}

void YPower::registerValueCallback(YPowerUpdateCallback callback)
{
    if (callback != NULL) {
        _registerFuncCallback(this);
        yapiLockFunctionCallBack(NULL);
        YAPI::_yapiFunctionUpdateCallbackFwd(this->functionDescriptor(), this->get_advertisedValue().c_str());
        yapiUnlockFunctionCallBack(NULL);
    } else {
        _unregisterFuncCallback(this);
    }
    _callback = callback;
}

void YPower::advertiseValue(const string& value)
{
    if (_callback != NULL) {
        _callback(this, value);
    }
}


YPower* YPower::FindPower(const string& func)
{
    if(YPower::_PowerCache.find(func) != YPower::_PowerCache.end())
        return YPower::_PowerCache[func];
    
    YPower *newPower = new YPower(func);
    YPower::_PowerCache[func] = newPower;
    
    return newPower;
}

YPower* YPower::FirstPower(void)
{
    vector<YFUN_DESCR>   v_fundescr;
    YDEV_DESCR             ydevice;
    string              serial, funcId, funcName, funcVal, errmsg;
    
    if(YISERR(YapiWrapper::getFunctionsByClass("Power", 0, v_fundescr, sizeof(YFUN_DESCR), errmsg)) ||
       v_fundescr.size() == 0 ||
       YISERR(YapiWrapper::getFunctionInfo(v_fundescr[0], ydevice, serial, funcId, funcName, funcVal, errmsg))) {
        return NULL;
    }
    return YPower::FindPower(serial+"."+funcId);
}

//--- (end of YPower implementation)

//--- (Power functions)
//--- (end of Power functions)
