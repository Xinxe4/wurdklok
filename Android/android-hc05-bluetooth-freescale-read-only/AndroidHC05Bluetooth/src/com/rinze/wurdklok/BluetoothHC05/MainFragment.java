package com.rinze.wurdklok.BluetoothHC05;

import java.util.Calendar;

import android.app.DialogFragment;
import android.app.Fragment;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.SeekBar;
import android.widget.SeekBar.OnSeekBarChangeListener;
import android.widget.TextView;
import android.widget.ToggleButton;

public class MainFragment extends Fragment {

    private Button mSendButtonText;
    private TextView mMessage;
    private Button mSetTime;
    private Button mSetDate;
    private Button mShowDate;
    private Button mShowTime;
    private Button mSetAlarm;
    public static ToggleButton mAlarmToggle;
    public static ToggleButton mBrightnessToggle;
    public static SeekBar mBrightnessSlider;
    public static TextView mAlarmText;
    public static TextView mReceivedMsg;
    public static boolean alarmTimeRead = false;
    
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View v = inflater.inflate(R.layout.mainfragment, container, false);
        
        mMessage = (TextView) v.findViewById(R.id.text_message);
        mReceivedMsg = (TextView) v.findViewById(R.id.text_status);
        
        mSendButtonText = (Button) v.findViewById(R.id.button_send);
        mSendButtonText.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
                // Send a message using content of the edit text widget
            	String msg = mMessage.getText().toString();
                BluetoothHC05.mSingleton.sendMessage(msg);
            }
        });

        mSetAlarm = (Button) v.findViewById(R.id.btn_set_alarm);     
        
        mSetTime = (Button) v.findViewById(R.id.button_setcurrenttime);
        mSetTime.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
            	if(BluetoothHC05.D) Log.i(BluetoothHC05.TAG, "Send current time");
                Calendar c = Calendar.getInstance();
                int hr = c.get(Calendar.HOUR_OF_DAY);
                int mi = c.get(Calendar.MINUTE);
                int se = c.get(Calendar.SECOND);
            	String msg = "P ST " + Integer.toString(hr) + " " + Integer.toString(mi) + " " + Integer.toString(se) + ";";
            	BluetoothHC05.mSingleton.sendMessage(msg);
            }
        });
        
        mSetDate = (Button) v.findViewById(R.id.button_setcurrentdate);
        mSetDate.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
            	if(BluetoothHC05.D) Log.i(BluetoothHC05.TAG, "Send current date");
                Calendar c = Calendar.getInstance();
                int da = c.get(Calendar.DAY_OF_MONTH);
                int mo = c.get(Calendar.MONTH)+1;
                int ye = c.get(Calendar.YEAR);
            	String msg = "P SD " + Integer.toString(da) + " " + Integer.toString(mo) + " " + Integer.toString(ye) + ";";
            	BluetoothHC05.mSingleton.sendMessage(msg);
            }
        });
        
        mShowDate = (Button) v.findViewById(R.id.btn_showdate);
        mShowDate.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
            	if(BluetoothHC05.D) Log.i(BluetoothHC05.TAG, "Show current date");
            	String msg = "P MD 5;";
            	BluetoothHC05.mSingleton.sendMessage(msg);
            }
        });
        
        mShowTime = (Button) v.findViewById(R.id.btn_showtime);
        mShowTime.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
            	if(BluetoothHC05.D) Log.i(BluetoothHC05.TAG, "Show current time");
            	String msg = "P MD 1;";
            	BluetoothHC05.mSingleton.sendMessage(msg);
            }
        });
        
        mAlarmText = (TextView) v.findViewById(R.id.alarm_time);
        mAlarmToggle = (ToggleButton) v.findViewById(R.id.toggleAlarmButton);
        mAlarmToggle.setOnClickListener(new OnClickListener() {
			public void onClick(View v) {
				ToggleButton mTB = (ToggleButton) v;
				if(mTB.isChecked()) {
					BluetoothHC05.mSingleton.sendMessage("P TA 1;");
					BluetoothHC05.mSingleton.sendMessage("AA;");
				} else {
					BluetoothHC05.mSingleton.sendMessage("P TA 0;");
					BluetoothHC05.mSingleton.sendMessage("AA;");
				}
			}
		});
        
        mBrightnessSlider = (SeekBar) v.findViewById(R.id.brightness_slider);
        mBrightnessSlider.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {
			public void onStopTrackingTouch(SeekBar seekBar) {
				String str = "P SB " + Integer.toString(seekBar.getProgress()) + ";";
				BluetoothHC05.mSingleton.sendMessage(str);
			}
			public void onStartTrackingTouch(SeekBar seekBar) {	
			}
			public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
			}
		});
        
        mBrightnessToggle = (ToggleButton) v.findViewById(R.id.toggleBrightnessButton);
        mBrightnessToggle.setOnClickListener(new OnClickListener() {
			public void onClick(View v) {
				ToggleButton mTB = (ToggleButton) v;
				if(mTB.isChecked()) {
  					//mBrightnessSlider.setEnabled(true);
          			//mBrightnessToggle.setChecked(false);
					BluetoothHC05.mSingleton.sendMessage("P SM 0;");
					BluetoothHC05.mSingleton.sendMessage("GM;");
				} else {
  					//mBrightnessSlider.setEnabled(false);
          			//mBrightnessToggle.setChecked(true);
					BluetoothHC05.mSingleton.sendMessage("P SM 1;");
					BluetoothHC05.mSingleton.sendMessage("GM;");
				}
			}
		});
        
        return v;
    }

	@Override
	public void onResume() {
		super.onResume();
		if (BluetoothHC05.mSingleton.mChatService != null && BluetoothHC05.mSingleton.mChatService.getState() == BluetoothSerialService.STATE_CONNECTED) {
			if(BluetoothHC05.D) Log.i(BluetoothHC05.TAG, "Resume Mainfragment");
			BluetoothHC05.mSingleton.sendMessage("GM;");
			BluetoothHC05.mSingleton.sendMessage("AA;");
			BluetoothHC05.mSingleton.sendMessage("GB;");
			BluetoothHC05.mSingleton.sendMessage("GA;");
			BluetoothHC05.mSingleton.sendMessage("P MD 1;");
		}
	}
    
	public void setAlarmText(String str) {
		mAlarmText.setText(str);
	}
} 