package com.example.stepcounter;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import java.util.Timer;
import java.util.TimerTask;
import android.os.Handler;

public class TmeCounter extends AppCompatActivity {

    SensorManager sm;
    Sensor sensor;
    float LastX;
    float LastY;
    float LastZ;
    long LastTime;
    TextView t0;
    int i = 0;
    private double lstValue = 0;  //上次的值
    private double curValue = 0;  //当前值
    private boolean motiveState = true;   //是否处于运动状态
    private double amax;//波峰绝对值
    private double amin;//波谷绝对值

    private EditText inputet;
    private Button gettime,starttime,stoptime,cleartime;
    private TextView time;
    private int j = 0;
    private Timer timer = null;
    private TimerTask timerTask;
    Handler handler = new Handler();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_tme_counter);

        t0 = (TextView) findViewById(R.id.t0);

        initView();
        //取得感应服务使用权限
        sm = (SensorManager) this.getSystemService(Context.SENSOR_SERVICE);
        sensor = sm.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
        sm.registerListener(SL, sensor, SensorManager.SENSOR_DELAY_GAME);
    }

    private void initView(){
        inputet = (EditText) findViewById(R.id.inputtime);
        gettime = (Button)findViewById(R.id.gettime);
        starttime = (Button)findViewById(R.id.starttime);
        stoptime = (Button)findViewById(R.id.stoptime);
        cleartime = (Button)findViewById(R.id.cleartime);
        time = (TextView)findViewById(R.id.time);

        gettime.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //设置倒计时时间 秒
                    time.setText(inputet.getText().toString());
                    j = Integer.parseInt(inputet.getText().toString());
                }
        });
        starttime.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //步数清0,重头开始计数
                i = 0;
                t0.setText(String.valueOf(i));

                //开启线程刷新,从而在子线程中更新ui线程，实现倒计时
                handler = new Handler();
                timer = new Timer();
                timer.schedule(new TimerTask() {
                    @Override
                    public void run() {
                        handler.post(new Runnable() {
                            @Override
                            public void run() {
                                if(j>0)
                                {
                                    j--;
                                    time.setText(String.valueOf(j));
                                }
                            }
                        });
                    }
                },1000,1000);
            }
        });
        stoptime.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                timer.cancel();//关闭定时器
                handler.removeCallbacksAndMessages(null);
            }
        });
        cleartime.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                j = 0;
                time.setText(String.valueOf(j));
            }
        });

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
}