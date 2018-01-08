/** 
 * @file ServiceException.cpp
 * @author Philippe-Henri Gosselin
 * @date 9 décembre 2015
 * @copyright CNRS
 */

#include "ServiceException.hpp"
#include "ServiceException.h"

using namespace server;

ServiceException::ServiceException (HttpStatus status, std::string msg) 
    : httpStatus(status),msg(msg) {    
}

HttpStatus ServiceException::status () const {
    return httpStatus;
}

const char* ServiceException::what () const {
    return msg.c_str();
    //return msg;
}

HttpStatus ServiceException::getHttpStatus() const{return httpStatus;}

void ServiceException::setHttpStatus(HttpStatus httpStatus){this->httpStatus = httpStatus;}

const std::string& ServiceException::getMsg() const{return msg;}

void ServiceException::setMsg(const std::string& msg){this->msg = msg;}

