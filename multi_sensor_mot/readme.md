# 多传感器融合  
## 时间同步  
### 统一时钟源  
目前主流时间同步方案是以GNSS时间为基准时间，采用PTP/gPTP时钟同步协议来完成各传感器之间的时间同步，PTP 前提是需要交换机支持PTP协议，才能实现高精度同步。PTP是在硬件级别实现时间同步，而NTP是在应用层级别实现的，相对于NTP，PTP适用于精度要求高的数据采集设备之间的时间同步。  
为什么有了GNSS授时，还需要加上PTP授时？  
PPS是无屏蔽的单线脉冲信号，极易受到车内恶劣电磁环境的干扰，届时根本无法区分出是干扰脉冲还是同步脉冲。  
卫星信号容易受到楼宇、天气等因素的影响，GNSS时钟源丢失的时候，所有需要时间同步的设备都将无法获取时间数据。  
### 硬同步  
如果**传感器支持硬件触发**的情况下，可以采用GPS时间戳作为基准进行硬件触发，这时传感器给出的数据中包含的时间戳即为全局时间戳（GPS时间戳）而非传感器时间戳。GNSS传感器自带秒脉冲发生器，所以可以直接使用。  
以lidar和camera为例，在到达指定GPS时间后，同时触发数据采集信号。方式是以PPS信号为触发信号，实现lidar和camera均在PPS信号上升沿的时候采集数据，且打上各自时钟的时间戳。由于PPS的频率只有1Hz，所以通常需要一个设备把PPS信号转发为任意频率、但是跟PPS信号同相位的方波，这样就可以控制camera的采集频率了。  
lidar制造商想出了一个相位锁定功能，也就是输入PPS，当PPS上升沿到来时，lidar的激光束恰好旋转到一定的角度。例如设置lidar的相位锁定角度为camera视野中央，如果camera视野朝着车辆正前方，lidar的坐标系也是朝着车辆正前方的话，相位锁定角度应该是0度。那么问题就这样解决了，每当lidar的激光束旋转到0度位置，也就是camera视野正中央（下图X轴方向），PPS上升沿刚好到来，camera也因此触发，就这样就实现了lidar和camera的同步采集。