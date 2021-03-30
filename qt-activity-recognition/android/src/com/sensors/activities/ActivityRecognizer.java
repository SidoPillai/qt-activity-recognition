package com.sensors.activities;

import android.app.*;
import android.content.*;

import java.util.ArrayList;
import org.json.JSONObject;
import org.json.JSONArray;

import android.content.Context;
import android.util.Log;
import android.widget.Toast;
import android.os.Bundle;
import android.app.PendingIntent;
import android.content.Intent;
import androidx.annotation.NonNull;
import androidx.localbroadcastmanager.content.LocalBroadcastManager;

import com.google.android.gms.location.ActivityRecognitionClient;
import com.google.android.gms.location.DetectedActivity;
import com.google.android.gms.tasks.Task;
import com.google.android.gms.tasks.OnFailureListener;
import com.google.android.gms.tasks.OnSuccessListener;

import com.sensors.activities.DetectedActivityIntentService;

public class ActivityRecognizer
{
    protected static final String TAG = ActivityRecognizer.class.getSimpleName();
    private Context mContext;
    private ActivityRecognitionClient mActivityRecognitionClient;
    private static long g_Instance = 0;
    private Activity mActivity;
    private static final long DETECTION_INTERVAL_IN_MILLISECONDS = 30000;
    protected DetectedActivityReceiver mReceiver;

    //--------------------------------------------------------------------------

    ActivityRecognizer(Activity activity)
    {
        mActivity = activity;
        mReceiver = new DetectedActivityReceiver ();
    }

    //--------------------------------------------------------------------------

    public void init(Context context, long instance)
    {
        mContext = context;
        g_Instance = instance;
        mActivityRecognitionClient = new ActivityRecognitionClient(mContext);
    }

    //--------------------------------------------------------------------------

    public void start()
    {
        LocalBroadcastManager.getInstance(mContext).registerReceiver(mReceiver, new IntentFilter(DetectedActivityIntentService.BROADCAST_ACTION));

        Task<Void> task = mActivityRecognitionClient.requestActivityUpdates(
                DETECTION_INTERVAL_IN_MILLISECONDS,
                getDetectedActivityPendingIntent());

        task.addOnSuccessListener(new OnSuccessListener<Void>()
        {
            @Override
            public void onSuccess(Void result)
            {
                Toast.makeText(mContext,
                        "Activity Updates Enabled",
                        Toast.LENGTH_SHORT)
                        .show();
                setUpdatesRequestedState(0);
            }
        });

        task.addOnFailureListener(new OnFailureListener()
        {
            @Override
            public void onFailure(@NonNull Exception e)
            {
                Toast.makeText(mContext,
                        "Activity Updates Not Enabled",
                        Toast.LENGTH_SHORT)
                        .show();
                setUpdatesRequestedState(-1);
            }
        });
    }

    //--------------------------------------------------------------------------

    public void stop()
    {
        LocalBroadcastManager.getInstance(mContext).unregisterReceiver(mReceiver);
        Task<Void> task = mActivityRecognitionClient.removeActivityUpdates(
                getDetectedActivityPendingIntent());
        task.addOnSuccessListener(new OnSuccessListener<Void>()
        {
            @Override
            public void onSuccess(Void result)
            {
                Toast.makeText(mContext,
                        "Activity Updates Removed",
                        Toast.LENGTH_SHORT)
                        .show();
                setUpdatesRequestedState(1);
            }
        });

        task.addOnFailureListener(new OnFailureListener()
        {
            @Override
            public void onFailure(@NonNull Exception e)
            {
                Log.w(TAG, "Failed to enable activity recognition.");
                Toast.makeText(mContext,
                        "Activity Updates Not Removed",
                        Toast.LENGTH_SHORT).show();
                setUpdatesRequestedState(-1);
            }
        });
    }

    //--------------------------------------------------------------------------

    private PendingIntent getDetectedActivityPendingIntent()
    {
        Intent intent = new Intent(mActivity, DetectedActivityIntentService.class);

        // We use FLAG_UPDATE_CURRENT so that we get the same pending intent back when calling
        // requestActivityUpdates() and removeActivityUpdates().
        return PendingIntent.getService(mActivity, 0, intent, PendingIntent.FLAG_UPDATE_CURRENT);
    }

    //--------------------------------------------------------------------------

    private void setUpdatesRequestedState(int state)
    {
        updateStateChanged(state);
    }

    //--------------------------------------------------------------------------

    private class DetectedActivityReceiver extends BroadcastReceiver
    {
        protected final String TAG = "DetectedActivityReceiver";

        @Override
        public void onReceive(Context context, Intent intent)
        {
            Log.d(TAG, "Received activity update");
            ArrayList<DetectedActivity> updatedActivities = intent.getParcelableArrayListExtra(DetectedActivityIntentService.ACTIVITY_EXTRA);
            int resultsSize = updatedActivities.size();
            JSONObject json = new JSONObject();
            JSONArray array = new JSONArray();

            try
            {
                for ( int i = 0; i < resultsSize; i++ )
                {
                    JSONObject item = new JSONObject();
                    DetectedActivity da = updatedActivities.get(i);
                    item.put(getActivityString(da.getType()), da.getConfidence());
                    array.put(item);
                }
                json.put("detected", array);
                updateDetectedActivities(json.toString());
            }
            catch(Exception e)
            {
                e.printStackTrace();
            }
        }
    }

    //--------------------------------------------------------------------------

    public static String getActivityString(int detectedActivityType)
    {
        switch(detectedActivityType)
        {
        case DetectedActivity.IN_VEHICLE:
            return "IN_VEHICLE";
        case DetectedActivity.ON_BICYCLE:
            return "ON_BICYCLE";
        case DetectedActivity.ON_FOOT:
            return "ON_FOOT";
        case DetectedActivity.RUNNING:
            return "RUNNING";
        case DetectedActivity.STILL:
            return "STILL";
        case DetectedActivity.TILTING:
            return "TILTING";
        case DetectedActivity.UNKNOWN:
            return "UNKNOWN";
        case DetectedActivity.WALKING:
            return "WALKING";
        default:
            return "UNIDENTIFIABLE";
        }
    }

    //--------------------------------------------------------------------------

    private static native void updateDetectedActivities(String activities);
    private static native void updateStateChanged(int state);

    //--------------------------------------------------------------------------
}
