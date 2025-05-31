//
// Created by RinChord on 25-5-30.
//
#pragma once

class LED {
private:

    // LED状态
    bool state;
    // LED灯泡的GPIO引脚（假设为某个具体的引脚）



public:
    /**
     * 实例化LED类
     */
    LED();

    /**
     * 点亮LED灯泡
     * @return 成功点亮返回true
     */
    bool turnON();

    /**
     * 关闭LED灯泡
     * @return
     */
    bool turnOFF();

    /**
     * 获取LED开关状态
     * @return 当前LED状态
     */
    bool getState() const;

};
