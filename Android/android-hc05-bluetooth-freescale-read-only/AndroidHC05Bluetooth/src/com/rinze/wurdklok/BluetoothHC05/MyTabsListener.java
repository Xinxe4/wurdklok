package com.rinze.wurdklok.BluetoothHC05;

import android.app.ActionBar;
import android.app.ActionBar.Tab;
import android.app.Fragment;
import android.app.FragmentTransaction;
import android.content.Context;
import android.widget.Toast;


class MyTabsListener implements ActionBar.TabListener {
    public Fragment fragment;
    public Context context;

    public MyTabsListener(Fragment fragment, Context context) {
                this.fragment = fragment;
                this.context = context;
    }
     
    public void onTabReselected(Tab tab, FragmentTransaction ft) {
    	Toast.makeText(BluetoothHC05.appContext, "Reselected!", Toast.LENGTH_LONG).show();
    }

    public void onTabSelected(Tab tab, FragmentTransaction ft) {
    	ft.replace(R.id.fragment_container, fragment);
    }

    public void onTabUnselected(Tab tab, FragmentTransaction ft) {
    	ft.remove(fragment);
    }

    }  