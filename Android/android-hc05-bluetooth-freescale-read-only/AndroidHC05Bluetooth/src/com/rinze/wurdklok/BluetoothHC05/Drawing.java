package com.rinze.wurdklok.BluetoothHC05;

import android.app.Activity;
import android.os.Bundle;
import android.support.v4.app.NavUtils;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ArrayAdapter;
import android.widget.GridView;
import android.widget.TextView;
import android.widget.Toast;

public class Drawing extends Activity {
	
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
		"91","92","93","94","95","96","97","98","99","100"};//,
		//"101","102","103","104","105","106","107","108","109","110",
		//"111","112","113","114","115","116","117","118","119","120",
		//"121","122","123","124","125","126","127","128","129","130",
		//"131","132","133","134","135","136","137","138","139","140",
		//"141","142","143","144","145","146","147","148","149","150"};
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
 
		setContentView(R.layout.drawing);
 
		mMatrix = (GridView) findViewById(R.id.gridView1);
 
		ArrayAdapter<String> adapter = new ArrayAdapter<String>(this,
				android.R.layout.simple_list_item_1, numbers);
 
		mMatrix.setAdapter(adapter);
 
		mMatrix.setOnItemClickListener(new OnItemClickListener() {
			public void onItemClick(AdapterView<?> parent, View v,int position, long id) {
			   Toast.makeText(getApplicationContext(),((TextView) v).getText(), Toast.LENGTH_SHORT).show();
			}
		});
		
		
		getActionBar().setDisplayHomeAsUpEnabled(true);
	}
 
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
        case android.R.id.home:
            NavUtils.navigateUpFromSameTask(this);
            return true;
        default:
            return super.onOptionsItemSelected(item);
        }
    }
    
}