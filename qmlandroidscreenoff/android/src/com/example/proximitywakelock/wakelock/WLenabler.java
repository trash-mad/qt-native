package com.example.proximitywakelock.wakelock;

import android.os.PowerManager;
import android.os.Bundle;
import android.app.Activity;

public class WLenabler extends org.qtproject.qt5.android.bindings.QtActivity
{
    public static PowerManager powerManager;
    public static PowerManager.WakeLock wakeLock;
    public static int field = 0x00000020;

    public WLenabler(){
    }


    private static String setWakelock(Activity a){
        try {
            field = PowerManager.class.getClass().getField("PROXIMITY_SCREEN_OFF_WAKE_LOCK").getInt(null);
        } catch (Throwable ignored) {
        }
        powerManager = (PowerManager) a.getSystemService(POWER_SERVICE);
        wakeLock = powerManager.newWakeLock(field, a.getLocalClassName());
        return "OK";
    }

    private static String startWakelock(Activity a){
        wakeLock.acquire();
        return "Wakelock is running now";
    }


    private static String stopWakelock(Activity a){
         wakeLock.release();
         return "Wakelock is disabled now";
    }


}
