
package com.sensors.activities;

import android.app.IntentService;
import android.content.Intent;
import android.util.Log;

import androidx.localbroadcastmanager.content.LocalBroadcastManager;

import com.google.android.gms.location.ActivityRecognitionResult;
import com.google.android.gms.location.DetectedActivity;

import java.util.ArrayList;

public class DetectedActivityIntentService extends IntentService
{
    protected static final String TAG = DetectedActivityIntentService.class.getSimpleName();
    protected static final String PACKAGE_NAME = DetectedActivityIntentService.class.getPackage().getName();
    protected static final String ACTIVITY_EXTRA = PACKAGE_NAME + ".ACTIVITY_EXTRA";
    protected static final String BROADCAST_ACTION = PACKAGE_NAME + ".BROADCAST_ACTION";

    //--------------------------------------------------------------------------

    public DetectedActivityIntentService()
    {
        super( TAG );
    }

    //--------------------------------------------------------------------------

    @Override
    public void onCreate()
    {
        super.onCreate();
    }

    //--------------------------------------------------------------------------

    @Override
    protected void onHandleIntent( Intent intent )
    {
        ActivityRecognitionResult result = ActivityRecognitionResult.extractResult( intent );
        ArrayList<DetectedActivity> detectedActivities = (ArrayList) result.getProbableActivities();
        Intent localIntent = new Intent(BROADCAST_ACTION);
        localIntent.putExtra( ACTIVITY_EXTRA, detectedActivities );
        LocalBroadcastManager.getInstance(this).sendBroadcast( localIntent );
    }

    //--------------------------------------------------------------------------
}
