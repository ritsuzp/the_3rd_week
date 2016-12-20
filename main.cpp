//
// Created by ritsuzp on 12/20/16.
//

#ifndef TASK_TRAJECTORY_GENERATOR_NEWCMD_H
#define TASK_TRAJECTORY_GENERATOR_NEWCMD_H

#include<iostream>
#include<math.h>
using namespace std;

class newcmd
{
public:
    float speed;// m/s
    float target_location;//目标位置（增量），米
    float acceleration;// m/s^2
    float deceleration;
    bool Done;//到达标记
    float delta_t;//增量时长（毫秒）
    float delta_x;//增量位移（毫米）
	void set();
    void newset();
    void compute();//计算增量位移

private:
    float t_acc;//加速时长,毫秒
    float t_mid;
    float t_dec;
    float t_sum;//已用时长
    float v;//当前速度

};

void newcmd::set()
{
//	speed = 0;
//	target_location = 0;
//	acceleration = 0;
//	deceleration = 0;
	Done = false;
	delta_t = 10;
	delta_x = 0;
	t_sum = 0;
//	v = 0;

}

void newcmd::newset()
{
    cout<<"请输入目标速度、位移量、加速度、减速度："<<endl;
    cin>>speed;
    cin>>target_location;
    cin>>acceleration;
    cin>>deceleration;
    t_acc = 1000*speed/acceleration;
    t_dec = 1000*speed/deceleration;
    t_mid = 1000*(target_location - speed*speed/(2*acceleration) - speed*speed/(2*deceleration))/speed;
}

void newcmd::compute()
{
    t_sum = t_sum + delta_t;

    if (t_sum < t_acc)
	{
        v = t_sum * acceleration / 1000;
    }
    else if (t_sum < (t_acc + t_mid))
    {
        v = speed;
    }
    else
    {
        v = speed - deceleration * (t_sum - t_acc - t_mid)/1000;
    }
    delta_x = delta_t * v;

    if(t_sum == t_acc + t_mid + t_dec | t_sum > t_acc + t_mid + t_dec  )
    {
        Done = true;
    }
	cout<<"已用时"<<t_sum<<"ms"<<endl;
}


#endif //TASK_TRAJECTORY_GENERATOR_NEWCMD_H


int main() {
    newcmd n1;
	n1.set();
    n1.newset();
    while (n1.Done == false)
    {
        n1.compute();
        cout<<"输出位移"<<n1.delta_x<<"mm"<<endl;
    }
    cout<<"目标位置到达。"<<endl;
    return 0;
}
