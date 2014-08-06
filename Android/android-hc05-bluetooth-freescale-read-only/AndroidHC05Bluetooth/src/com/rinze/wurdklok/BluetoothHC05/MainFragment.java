package com.rinze.wurdklok.BluetoothHC05;

import java.text.DecimalFormat;
import java.util.Calendar;

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
    private ToggleButton mAlarmToggle;
    public static ToggleButton mBrightnessToggle;
    public static SeekBar mBrightnessSlider;
    private TextView mAlarmText;
    
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View v = inflater.inflate(R.layout.mainfragment, container, false);
        
        mMessage = (TextView) v.findViewById(R.id.text_message);
        
        mSendButtonText = (Button) v.findViewById(R.id.button_send);
        mSendButtonText.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
                // Send a message using content of the edit text widget
            	String msg = mMessage.getText().toString();
                BluetoothHC05.mSingleton.sendMessage(msg);
            }
        });

        mSetTime = (Button) v.findViewById(R.id.button_setcurrenttime);
        mSetTime.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
            	if(BluetoothHC05.D) Log.i(BluetoothHC05.TAG, "Send current time");
                Calendar c = Calendar.getInstance();
                int hr = c.get(Calendar.HOUR_OF_DAY);
                int mi = c.get(Calendar.MINUTE);
                DecimalFormat d = new DecimalFormat("00");
            	String msg = "ST" + d.format(hr) + d.format(mi) + ";";
            	BluetoothHC05.mSingleton.sendMessage(msg);
                if(BluetoothHC05.D) Log.i(BluetoothHC05.TAG, "Sent:" + msg);
            }
        });
        
        mAlarmText = (TextView) v.findViewById(R.id.alarm_time);
        mAlarmToggle = (ToggleButton) v.findViewById(R.id.toggleAlarmButton);
        mBrightnessSlider = (SeekBar) v.findViewById(R.id.brightness_slider);
        mBrightnessSlider.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {
			public void onStopTrackingTouch(SeekBar seekBar) {
				String str = "SB" + String.format("%03d", seekBar.getProgress()) + ";";
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
					BluetoothHC05.mSingleton.sendMessage("SM0;");
				} else {
  					//mBrightnessSlider.setEnabled(false);
          			//mBrightnessToggle.setChecked(true);
					BluetoothHC05.mSingleton.sendMessage("SM1;");
				}
			}
		});
        
        mAlarmText = (TextView) v.findViewById(R.id.text_status);
        
        return v;
    }

	@Override
	public void onResume() {
		super.onResume();
	}
    
	public void setAlarmText(String str) {
		mAlarmText.setText(str);
	}

} 