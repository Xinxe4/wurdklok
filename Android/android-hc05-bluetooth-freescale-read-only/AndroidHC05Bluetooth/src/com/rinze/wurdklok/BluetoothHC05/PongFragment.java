package com.rinze.wurdklok.BluetoothHC05;

import android.app.Activity;
import android.app.Fragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;

public class PongFragment extends Fragment {
	
	public static TextView mScore;
	
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
    	
        // Inflate the layout for this fragment
        View v = inflater.inflate(R.layout.pongfragment, container, false);
        v.setMinimumHeight(BluetoothHC05.height/10);
        v.setMinimumWidth(BluetoothHC05.width/10);

    	mScore = (TextView) v.findViewById(R.id.text_score);
		
    	BluetoothHC05.mSingleton.sendMessage("P MD 6;");
    	
    	Button mBtnDown = (Button) v.findViewById(R.id.button_down);
    	mBtnDown.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
            	BluetoothHC05.mSingleton.sendMessage("P MB 1;");
            }
        });
    	
    	Button mBtnUp = (Button) v.findViewById(R.id.button_up);
    	mBtnUp.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
            	BluetoothHC05.mSingleton.sendMessage("P MB 0;");
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
    }

} 