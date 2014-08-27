package com.rinze.wurdklok.BluetoothHC05;

import java.util.Calendar;

import android.app.Dialog;
import android.app.DialogFragment;
import android.app.TimePickerDialog;
import android.os.Bundle;
import android.text.format.DateFormat;
import android.util.Log;
import android.widget.TimePicker;

public class TimePickerFragment extends DialogFragment implements TimePickerDialog.OnTimeSetListener {

	@Override
	public Dialog onCreateDialog(Bundle savedInstanceState) {
		// Use the current time as the default values for the picker
		final Calendar c = Calendar.getInstance();
		int hour = c.get(Calendar.HOUR_OF_DAY);
		int minute = c.get(Calendar.MINUTE);
		
		// Create a new instance of TimePickerDialog and return it
		return new TimePickerDialog(getActivity(), this, hour, minute,
		DateFormat.is24HourFormat(getActivity()));
	}
	
	public void onTimeSet(TimePicker view, int hourOfDay, int minute) {
		  if(BluetoothHC05.D) Log.i(BluetoothHC05.TAG, "Alarm timepicker set");
		  BluetoothHC05.mSingleton.sendMessage("P SA "+Integer.toString(hourOfDay)+" "+Integer.toString(minute)+";");
		  BluetoothHC05.mSingleton.sendMessage("GA;");
		}
}