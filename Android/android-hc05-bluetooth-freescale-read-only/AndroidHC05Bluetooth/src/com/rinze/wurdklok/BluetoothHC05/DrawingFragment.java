package com.rinze.wurdklok.BluetoothHC05;

import java.text.DecimalFormat;

import android.app.Activity;
import android.app.Fragment;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ArrayAdapter;
import android.widget.GridView;

public class DrawingFragment extends Fragment {
	
	private GridView mMatrix;
	
	static String[] numbers = new String[] { 
		"1","2","3","4","5","6","7","8","9","10",
		"11","12","13","14","15","16","17","18","19","20",
		"21","22","23","24","25","26","27","28","29","30",
		"31","32","33","34","35","36","37","38","39","40",
		"41","42","43","44","45","46","47","48","49","50",
		"51","52","53","54","55","56","57","58","59","60",
		"61","62","63","64","65","66","67","68","69","70",
		"71","72","73","74","75","76","77","78","79","80",
		"81","82","83","84","85","86","87","88","89","90",
		"91","92","93","94","95","96","97","98","99","100",
		"101","102","103","104","105"};//,"106","107","108","109","110",
		//"111","112","113","114","115","116","117","118","119","120",
		//"121","122","123","124","125","126","127","128","129","130",
		//"131","132","133","134","135","136","137","138","139","140",
		//"141","142","143","144","145","146","147","148","149","150"};
	
	
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
    	
        // Inflate the layout for this fragment
        View v = inflater.inflate(R.layout.drawingfragment, container, false);
        v.setMinimumHeight(BluetoothHC05.height/10);
        v.setMinimumWidth(BluetoothHC05.width/10);
        
    	if(BluetoothHC05.D) Log.i(BluetoothHC05.TAG, "Open matrix");

    	GridView mMatrix = (GridView) v.findViewById(R.id.gridView1);
		
    	ArrayAdapter<String> adapter = new ArrayAdapter<String>(v.getContext(),R.layout.grid_item_label, numbers);
    	BluetoothHC05.mSingleton.sendMessage("MD02;");
		
		mMatrix.setAdapter(adapter);
		
		mMatrix.setOnItemClickListener(new OnItemClickListener() {
			public void onItemClick(AdapterView<?> parent, View v,int position, long id) {
			   DecimalFormat d = new DecimalFormat("000");
           	   String msg = "SS" + d.format(position) + ";";
           	   BluetoothHC05.mSingleton.sendMessage(msg);
           	if(BluetoothHC05.D) Log.i(BluetoothHC05.TAG, "Sent: " + msg);
			}
		});	
		
        return v;
    }
    
    @Override
    public void onAttach(Activity act) {
    	super.onAttach(act);
    }
    
    

} 