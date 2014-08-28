package com.rinze.wurdklok.BluetoothHC05;

import java.util.Calendar;

import android.app.Dialog;
import android.app.DialogFragment;
import android.app.TimePickerDialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.text.format.DateFormat;
import android.util.Log;
import android.widget.TimePicker;

public class TimePickerFragment extends DialogFragment implements TimePickerDialog.OnTimeSetListener {

	int callCount = 0;   //To track number of calls to onTimeSet()
	
	@Override
	public Dialog onCreateDialog(Bundle savedInstanceState) {
		int hour, minute;
		if(MainFragment.alarmTimeRead){
			String almTime = MainFragment.mAlarmText.getText().toString();
			try {
				hour = Integer.valueOf(almTime.substring(0,almTime.indexOf(":")));
				minute = Integer.valueOf(almTime.substring(almTime.indexOf(":")+1));
			} catch (Exception e) {
				if(BluetoothHC05.D) Log.i(BluetoothHC05.TAG, "almTime not read");
				e.printStackTrace();
				hour = 0;
				minute = 0;
			}
		} else {
			// Use the current time as the default values for the picker
			final Calendar c = Calendar.getInstance();
			hour = c.get(Calendar.HOUR_OF_DAY);
			minute = c.get(Calendar.MINUTE);
		}
		
		// Create a new instance of TimePickerDialog and return it
		TimePickerDialog mTPD = new TimePickerDialog(getActivity(), this, hour, minute, DateFormat.is24HourFormat(getActivity()));
		mTPD.setTitle("Stel de tiid yn:");
		return mTPD;
	}
	
	
	public void onTimeSet(TimePicker view, int hourOfDay, int minute) {
		  callCount++;    // Incrementing call count
		  if(callCount > 1) {   // On second call
			  if(BluetoothHC05.D) Log.i(BluetoothHC05.TAG, "Alarm timepicker set");
			  BluetoothHC05.mSingleton.sendMessage("P SA "+Integer.toString(hourOfDay)+" "+Integer.toString(minute)+";");
			  BluetoothHC05.mSingleton.sendMessage("GA;");
		  }
		}

}