package com.example.stepcounter;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.Intent;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    private double oriValue = 0;  //原始值
    private double lstValue = 0;  //上次的值
    private double curValue = 0;  //当前值
    private boolean motiveState = true;   //是否处于运动状态
    private double amax;//波峰绝对值
    private double amin;//波谷绝对值

    SensorManager sm;
    Sensor sensor;
    float LastX;
    float LastY;
    float LastZ;

    long LastTime;
    TextView t0,t1,tv;
    int i = 0;//步数

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button on = findViewById(R.id.on);
        Button stop = findViewById(R.id.stop);
        Button off = findViewById(R.id.off);
        //点击事件
        on.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //第二步：通过SensorManager实例对象获得想要的传感器对象:参数决定获取哪个传感器
                sensor = sm.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);//加速度传感器
                //注册数值变化监听器
                sm.registerListener(SL, sensor, SensorManager.SENSOR_DELAY_GAME);
            }
        });

        stop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sm.unregisterListener(SL);
            }
        });

        off.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tv.setText(null);
                i = 0;
                t0.setText(String.valueOf(i));
                t1.setText(null);
            }
        });

        t0 = (TextView)findViewById(R.id.t0);
        t1 = (TextView)findViewById(R.id.t1);
        tv = (TextView)findViewById(R.id.tv);

        //取得感应服务使用权限
        //第一步：通过getSystemService获得SensorManager实例对象
        sm = (SensorManager)this.getSystemService(Context.SENSOR_SERVICE);
        //后面步骤在点击启动按钮后实现
    }

    //SL为感应器触发事件
    private SensorEventListener SL = new SensorEventListener() {
        @Override
        public void onSensorChanged(SensorEvent event) {

            double range = 25;//设定一个精度范围避免微小扰动
            float x = event.values[0];//分别获取xyz轴的加速度
            float y = event.values[1];
            float z = event.values[2];
            //当前加速度xyz 减去 上次加速度xyz
            float DX = x-LastX;
            float DY = y-LastY;
            float DZ = z-LastZ;
            float[] value = event.values;

            long CurrentTime = System.currentTimeMillis();  //取得当下时间:毫秒 自1970-1-01 00:00:00.000 到当前时刻的时间距离
            long xTime = CurrentTime-LastTime;
            if(xTime<300) return;//计步时间间隔不能太小

            //计算当前的模
            curValue = Math.sqrt(Math.pow(value[0],2)+Math.pow(value[1],2)+Math.pow(value[2],2));
            //取波峰和波谷的值
            //向上加速的状态
            if (motiveState == true) {
                if (curValue >= lstValue) lstValue = curValue;
                else {
                    //检测到一次峰值
                    if (Math.abs(curValue - lstValue) >= range) {
                        LastTime = CurrentTime;
                        amax = Math.abs(curValue);
                        motiveState = false;
                    }
                }
            }
            //向下加速的状态
            if (motiveState == false) {
                if (curValue <= lstValue) lstValue = curValue;
                else {
                    if (Math.abs(curValue - lstValue) >= range) {
                        //检测到一次峰值
                        amin = Math.abs(curValue);
                        if(Math.abs(curValue)>=(amax+amin)*0.5){
                            i++;  //步数 + 1
                            t0.setText(String.valueOf(i));//读数更新
                            tv.setText("初加速度：\n"+x+","+y+","+z+"\n"+"末加速度：\n"+DX+","+DY+","+DZ);
                            t1.setText("触发间隔(ms)："+xTime);
                            motiveState = true;
                        }
                    }
                }
            }
            LastX = x;
            LastY = y;
            LastZ = z;
        }

        @Override
        public void onAccuracyChanged(Sensor sensor, int accuracy) {

        }
    };

    //为程序关闭时移除感应触发事件
    protected void onDestory(){
        super.onDestroy();
        sm.unregisterListener(SL);

    }

    //跳转页面
    public void toTmeCounter(View view) {
        Intent intent = new Intent(this,TmeCounter.class);
        startActivity(intent);
    }
}