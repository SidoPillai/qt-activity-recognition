# qt-activity-recognition
Demonstration of Activity Recognition in Qt using native components 

# api

```
ActivityRecognition {
   id: activityRecognition
    
   onActivityDetected: {
       console.log(activityDetected)
   }
   
   onError: {
      console.log(errorMessage)
   }
}
```

## Methods
start()
stop()

## Results


### Android
IN_VEHICLE, ON_BICYCLE, ON_FOOT, RUNNING, STILL, TILTING, UNKNOWN, WALKING, UNIDENTIFIABLE

### iOS
STATIONARY, WALKING, RUNNING, AUTOMOTIVE, CYCLING, UNKNOWN
