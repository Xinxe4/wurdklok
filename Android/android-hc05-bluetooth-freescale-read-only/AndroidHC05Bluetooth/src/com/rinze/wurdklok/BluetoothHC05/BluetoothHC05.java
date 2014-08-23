/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.rinze.wurdklok.BluetoothHC05;

import java.util.ArrayList;

import android.app.ActionBar;
import android.app.Activity;
import android.app.DialogFragment;
import android.app.Fragment;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.TabHost;
import android.widget.TextView;
import android.widget.Toast;

/**
 * This is the main Activity that displays the current chat session.
 */
public class BluetoothHC05 extends Activity {
	public static Context appContext;
	public static final String PREFS_NAME = "WurdklokPrefs";
	
	public static int height, width;
	public static BluetoothHC05 mSingleton;
	
	public static TabHost myTabs;
	public static int TempC;

    // Debugging
	protected static final String TAG = "BluetoothChat";
    protected static final boolean D = true;

    // Message types sent from the BluetoothChatService Handler
    public static final int MESSAGE_STATE_CHANGE = 1;
    public static final int MESSAGE_READ = 2;
    public static final int MESSAGE_WRITE = 3;
    public static final int MESSAGE_DEVICE_NAME = 4;
    public static final int MESSAGE_TOAST = 5;
    public static final int MESSAGE_DEVICE_ADDRESS = 6;
    
    static final String[] nrs = new String[] {"1","2","3","4","5","6","7","8","9","10","11","12" };
    
    private String receivedText = "";
    private ArrayList<String> cmdBuffer = new ArrayList<String>();
    
    // Return Intent extra
    public static final String EXTRA_DEVICE_ADDRESS = "device_address";

    // Key names received from the BluetoothChatService Handler
    public static final String DEVICE_ADDRESS = "device_mac";
    public static final String DEVICE_NAME = "device_name";
    public static final String TOAST = "toast";
    public static final String MESSAGE_TEXT = "message_text";
    
    public static final String LAST_CONNECTED_DEVICE = "lastConnectedDevice";

    // Intent request codes
    private static final int REQUEST_CONNECT_DEVICE = 1;
    private static final int REQUEST_ENABLE_BT = 2;

    private ArrayList<View> activeViews = new ArrayList<View>();
    
    // Layout Views
    private TextView mTitle;
    
    // Name of the connected device
    private String mConnectedDeviceName = null;   
    // Local Bluetooth adapter
    private BluetoothAdapter mBluetoothAdapter = null;
    // Member object for the chat services
    private BluetoothSerialService mChatService = null;


    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        if(D) Log.e(TAG, "+++ ON CREATE +++");

        mSingleton = this;
        // Set up the window layout
        setContentView(R.layout.main);

        //ActionBar gets initiated
        ActionBar actionbar = getActionBar();
        //Tell the ActionBar we want to use Tabs.
        actionbar.setNavigationMode(ActionBar.NAVIGATION_MODE_TABS);
        //initiating both tabs and set text to it.
        ActionBar.Tab MainTab = actionbar.newTab().setText("Main");
        ActionBar.Tab DrawingTab = actionbar.newTab().setText("Drawing");
        ActionBar.Tab TemperatureTab = actionbar.newTab().setText("Temperature");
        ActionBar.Tab PongTab = actionbar.newTab().setText("Pong");
        
        //create the two fragments we want to use for display content
        Fragment MainFragment = new MainFragment();
        Fragment DrawingFragment = new DrawingFragment();
        Fragment TemperatureFragment = new TemperatureFragment();
        Fragment PongFragment = new PongFragment();
        
        //set the Tab listener. Now we can listen for clicks.
        MainTab.setTabListener(new MyTabsListener(MainFragment, getApplicationContext()));
        DrawingTab.setTabListener(new MyTabsListener(DrawingFragment,getApplicationContext()));
        TemperatureTab.setTabListener(new MyTabsListener(TemperatureFragment,getApplicationContext()));
        PongTab.setTabListener(new MyTabsListener(PongFragment,getApplicationContext()));
        
        //add the two tabs to the actionbar
        actionbar.addTab(MainTab);
        actionbar.addTab(DrawingTab);
        actionbar.addTab(TemperatureTab);
        actionbar.addTab(PongTab);
        
    	DisplayMetrics metrics = new DisplayMetrics();
    	getWindowManager().getDefaultDisplay().getMetrics(metrics);
    	height = metrics.heightPixels;
    	width  = metrics.widthPixels;
        
        // Get local Bluetooth adapter
        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();

        // If the adapter is null, then Bluetooth is not supported
        if (mBluetoothAdapter == null) {
            Toast.makeText(this, "Bluetooth is not available", Toast.LENGTH_LONG).show();
            finish();
            return;
        }
        
    }

    @Override
    public void onStart() {
        super.onStart();
        if(D) Log.e(TAG, "++ ON START ++");

        // If BT is not on, request that it be enabled.
        // setupChat() will then be called during onActivityResult
        if (!mBluetoothAdapter.isEnabled()) {
            Intent enableIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableIntent, REQUEST_ENABLE_BT);
        	Toast.makeText(this, "Warning: Bluetooth disabled!", Toast.LENGTH_SHORT).show();
        // Otherwise, setup the chat session
        } else {
            if (mChatService == null) setupChat();
            
        	SharedPreferences settings = getSharedPreferences(PREFS_NAME, 0);
            String lastAddress = settings.getString(LAST_CONNECTED_DEVICE, "");
            if(D) Log.i(TAG, "Last connected device: " + lastAddress);
            if (BluetoothAdapter.checkBluetoothAddress(lastAddress)) {
            	if(D) Log.i(TAG, "Last connected device valid");
            	Intent connect = new Intent();
            	connect.putExtra(EXTRA_DEVICE_ADDRESS, lastAddress);
                onActivityResult(REQUEST_CONNECT_DEVICE, Activity.RESULT_OK, connect);
            }
        }
    }

    @Override
    public synchronized void onResume() {
        super.onResume();
        if(D) Log.e(TAG, "+ ON RESUME +");

        // Performing this check in onResume() covers the case in which BT was
        // not enabled during onStart(), so we were paused to enable it...
        // onResume() will be called when ACTION_REQUEST_ENABLE activity returns.
        if (mChatService != null) {
            // Only if the state is STATE_NONE, do we know that we haven't started already
            if (mChatService.getState() == BluetoothSerialService.STATE_NONE) {
              // Start the Bluetooth chat services
              mChatService.start();
            }
        }
    }

    private void setupChat() {
        Log.d(TAG, "setupChat()");
        
        
        // Initialize the BluetoothChatService to perform bluetooth connections
        mChatService = new BluetoothSerialService(this, mHandler);
    }

    private void activateViews(ArrayList<View> a, Boolean b) {
    	for (int i = 0; i < a.size(); i++) {
    		a.get(i).setEnabled(b);
    	}
    	if(D) Log.i(TAG, "activateViews" + String.valueOf(b));
    }
    
    private void updateSettings() {
    	Log.i(TAG, "updateSettings");
    	activateViews(activeViews, true);
    	sendMessage("GM;");
    	//sendMessage("GB;");
    	//sendMessage("GA;");
    }
    
    @Override
    public synchronized void onPause() {
        super.onPause();
        if (mChatService != null) mChatService.stop();
        if(D) Log.e(TAG, "- ON PAUSE -");
    }

    @Override
    public void onStop() {
        super.onStop();
        if(D) Log.e(TAG, "-- ON STOP --");
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        // Stop the Bluetooth chat services
        if (mChatService != null) mChatService.stop();
        if(D) Log.e(TAG, "--- ON DESTROY ---");
    }

    private void ensureDiscoverable() {
        if(D) Log.d(TAG, "ensure discoverable");
        if (mBluetoothAdapter.getScanMode() !=
            BluetoothAdapter.SCAN_MODE_CONNECTABLE_DISCOVERABLE) {
            Intent discoverableIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_DISCOVERABLE);
            discoverableIntent.putExtra(BluetoothAdapter.EXTRA_DISCOVERABLE_DURATION, 300);
            startActivity(discoverableIntent);
        }
    }
    
    /**
     * Sends a message.
     * @param message  A string of text to send.
     */
    public void sendMessage(String message) {
        // Check that we're actually connected before trying anything
        if (mChatService.getState() != BluetoothSerialService.STATE_CONNECTED) {
            Toast.makeText(this, R.string.not_connected, Toast.LENGTH_SHORT).show();
            return;
        }

        // Check that there's actually something to send
        if (message.length() > 0) {
            // Get the message bytes and tell the BluetoothChatService to write
            byte[] send = message.getBytes();
            mChatService.write(send);
           	if(BluetoothHC05.D) Log.i(BluetoothHC05.TAG, "Sent: " + message);
        }
    }
    
    /**
     * Receives a message.
     * @param message  A string of text.
     */
    private void receiveMessage(String message) {
        if (message.length() > 0) {
        	boolean limCharFound = false;
        	try {
				receivedText = receivedText.concat(message);
				message = "";
				while (receivedText.contains(";")) {
					limCharFound = true;
					{
						message = message.concat(receivedText.substring(0, receivedText.indexOf(";")+1));
						receivedText = receivedText.substring(1+receivedText.indexOf(";"));
					}
				}
			} catch (Exception e) {
				// TODO Auto-generated catch block
				Log.e(TAG, e.toString());
			}
        	
        	if (limCharFound) { // At least 1 complete command received
    			if(D){Log.i(TAG, message);}
    			MainFragment.mReceivedMsg.setText(message);
        		while (message.contains(";")) {
        			String cmd = message.substring(0, message.indexOf(";"));
        			if (message.indexOf(";") != message.length()) {
        				message = message.substring(1+message.indexOf(";"));
        			}
        			cmdBuffer.add(cmd);      			
        		}
        		cmdBuffer.add(message);
        		
        		while (cmdBuffer.size() > 0) {
        			if(D){Log.i(TAG, "cmdBuffer.size: " + Integer.toString(cmdBuffer.size()));}
	        		if (cmdBuffer.size() > 0) {
	        			if(D){Log.i(TAG, "Decode: " + cmdBuffer.get(0));}
		    			if (cmdBuffer.get(0).contains("GM")) {
		    				if (cmdBuffer.size() > 1 && cmdBuffer.get(1)!="") {
		    					try {
			    					int man = Integer.parseInt(cmdBuffer.get(1).substring(0,1));
									MainFragment.mBrightnessSlider.setEnabled(man>0);
									MainFragment.mBrightnessToggle.setChecked(man<1);
								} catch (Exception e) {
									if(D){Log.e(TAG, "Failed to parse int");}
								}
								cmdBuffer.remove(1);
								cmdBuffer.remove(0);
								cmdBuffer.trimToSize();
								sendMessage("GB;");
		    				}
						} else if (cmdBuffer.get(0).contains("GB")) {
							if (cmdBuffer.size() > 1 && cmdBuffer.get(1)!="") {
		    					try {
									int man = Integer.parseInt(cmdBuffer.get(1).substring(0));
									MainFragment.mBrightnessSlider.setProgress(man);
								} catch (Exception e) {
									if(D){Log.e(TAG, "Failed to parse int");}
								}
								cmdBuffer.remove(1);
								cmdBuffer.remove(0);
								cmdBuffer.trimToSize();
							}
						} else if (cmdBuffer.get(0).contains("GT")) {
							if (cmdBuffer.size() > 1 && cmdBuffer.get(1)!="") {
								try {
									int T = Integer.parseInt(cmdBuffer.get(1).substring(0));
									TemperatureFragment.setTemperature(T);
								} catch (Exception e) {
									if(D){Log.e(TAG, "Failed to parse int");}
								}
								cmdBuffer.remove(1);
								cmdBuffer.remove(0);
								cmdBuffer.trimToSize();
							}
						} else if (cmdBuffer.get(0).contains("PS")) {
							if (cmdBuffer.size() > 1 && cmdBuffer.get(1)!="") {
								try {
									PongFragment.mScore.setText(cmdBuffer.get(1).substring(0));
								} catch (Exception e) {
									if(D){Log.e(TAG, "Failed to parse int");}
								}
								cmdBuffer.remove(1);
								cmdBuffer.remove(0);
								cmdBuffer.trimToSize();
							}
						} else if (cmdBuffer.get(0).contains("END")) {
								cmdBuffer.remove(0);
								cmdBuffer.trimToSize();
						} else {
							cmdBuffer.remove(0);
							cmdBuffer.trimToSize();
						}
	        		}
        		}
        	}
        }
    }

    // The Handler that gets information back from the BluetoothChatService
    private final Handler mHandler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            switch (msg.what) {
            case MESSAGE_STATE_CHANGE:
                if(D) Log.i(TAG, "MESSAGE_STATE_CHANGE: " + msg.arg1);
                switch (msg.arg1) {
                case BluetoothSerialService.STATE_CONNECTED:
                    getActionBar().setTitle(getResources().getString(R.string.title_connected_to) + mConnectedDeviceName);
                    //mTitle.append(mConnectedDeviceName);
                    updateSettings();
                    break;
                case BluetoothSerialService.STATE_CONNECTING:
                	getActionBar().setTitle(R.string.title_connecting);
                    break;
                case BluetoothSerialService.STATE_LISTEN:
                case BluetoothSerialService.STATE_NONE:
                	getActionBar().setTitle(R.string.title_not_connected);
                    break;
                }
                break;
            case MESSAGE_WRITE:
                break;
            case MESSAGE_READ:
            	String str = msg.getData().getString(MESSAGE_TEXT);
            	receiveMessage(str);
                break;
            case MESSAGE_DEVICE_NAME:
                // save the connected device's name
                mConnectedDeviceName = msg.getData().getString(DEVICE_NAME);
                Toast.makeText(getApplicationContext(), "Connected to "
                               + mConnectedDeviceName, Toast.LENGTH_SHORT).show();
                break;
            case MESSAGE_TOAST:
                Toast.makeText(getApplicationContext(), msg.getData().getString(TOAST),
                               Toast.LENGTH_SHORT).show();
                break;
	        case MESSAGE_DEVICE_ADDRESS:
	            SharedPreferences settings = getSharedPreferences(PREFS_NAME, 0);
	            SharedPreferences.Editor editor = settings.edit();
	            editor.putString(LAST_CONNECTED_DEVICE, msg.getData().getString(DEVICE_ADDRESS));
	            editor.commit();
	            break;
            }
        }
    };

    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        if(D) Log.d(TAG, "onActivityResult " + resultCode);
        switch (requestCode) {
        case REQUEST_CONNECT_DEVICE:
            // When DeviceListActivity returns with a device to connect
            if (resultCode == Activity.RESULT_OK) {
                // Get the device MAC address
                String address = data.getExtras().getString(DeviceListActivity.EXTRA_DEVICE_ADDRESS);
                // Get the BLuetoothDevice object
                BluetoothDevice device = mBluetoothAdapter.getRemoteDevice(address);
                // Attempt to connect to the device
                mChatService.connect(device);
            }
            break;
        case REQUEST_ENABLE_BT:
            // When the request to enable Bluetooth returns
            if (resultCode == Activity.RESULT_OK) {
                // Bluetooth is now enabled, so set up a chat session
                setupChat();
            } else {
                // User did not enable Bluetooth or an error occured
                Log.d(TAG, "BT not enabled");
                Toast.makeText(this, R.string.bt_not_enabled_leaving, Toast.LENGTH_SHORT).show();
                finish();
            }
        }
    }
    
	public void showTimePickerDialog(View v) {
	    DialogFragment newFragment = new TimePickerFragment();
	    newFragment.show(getFragmentManager(), "timePicker");
	}

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflater = getMenuInflater();
        //inflater.inflate(R.menu.option_menu, menu);
        inflater.inflate(R.menu.main_activity_actions, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
        case R.id.scan:
            // Launch the DeviceListActivity to see devices and do scan
            Intent serverIntent = new Intent(this, DeviceListActivity.class);
            startActivityForResult(serverIntent, REQUEST_CONNECT_DEVICE);
            return true;
        case R.id.discoverable:
            // Ensure this device is discoverable by others
            ensureDiscoverable();
            return true;
        }
        return false;
    }
}