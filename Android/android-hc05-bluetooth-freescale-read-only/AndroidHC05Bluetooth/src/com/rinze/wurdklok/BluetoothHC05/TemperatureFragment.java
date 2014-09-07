package com.rinze.wurdklok.BluetoothHC05;

import java.text.DecimalFormat;

import android.app.Activity;
import android.app.Fragment;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;

public class TemperatureFragment extends Fragment {

	private static TextView mTemp;
	
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
    	
        // Inflate the layout for this fragment
        View v = inflater.inflate(R.layout.temperaturefragment, container, false);
        v.setMinimumHeight(BluetoothHC05.height/10);
        v.setMinimumWidth(BluetoothHC05.width/10);

    	mTemp = (TextView) v.findViewById(R.id.text_temp);
		
    	BluetoothHC05.mSingleton.sendMessage("P MD 3;");
    	
    	Button mBtnRefresh = (Button) v.findViewById(R.id.button_refresh);
    	mBtnRefresh.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
            	if(BluetoothHC05.D) Log.i(BluetoothHC05.TAG, "Refresh temperature");
            	BluetoothHC05.mSingleton.sendMessage("GT;");
            	setTemperature(BluetoothHC05.TempC);
            }
        });
    	
    	Button mBtnMaxmin = (Button) v.findViewById(R.id.button_maxmin);
    	mBtnMaxmin.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
            	if(BluetoothHC05.D) Log.i(BluetoothHC05.TAG, "Maxmin temperature");
            	BluetoothHC05.mSingleton.sendMessage("P MD 4;");
            	setTemperature(BluetoothHC05.TempC);
            }
        });
    	
        return v;
    }
    
    @Override
    public void onAttach(Activity act) {
    	super.onAttach(act);
    }
    
    @Override
    public void onResume() {
    	super.onResume();
    	BluetoothHC05.mSingleton.sendMessage("GT;");
    	setTemperature(BluetoothHC05.TempC);
    }
    
    public static void setTemperature(int T) {
    	BluetoothHC05.TempC = T;
    	double Td = T/10.0;
    	DecimalFormat d = new DecimalFormat("#0.0");
    	String msg = d.format(Td) + " C";
    	mTemp.setText(msg);
    }

} 