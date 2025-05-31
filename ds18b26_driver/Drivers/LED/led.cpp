//
// Created by RinChord on 25-5-30.
//

#include "led.h"

LED::LED() : state(false) {
    // 初始化LED状态为关闭
}
bool LED::turnON() {
    this->state = true;  // 设置状态为开启
    return true;  // 返回成功
}

bool LED::turnOFF() {
    this->state = false;  // 设置状态为关闭
    return true;  // 返回成功
}


bool LED::getState() const {
    return this->state;  // 返回当前LED状态
}