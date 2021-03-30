#include "IOSActivityRecognition.h"

#import <AVFoundation/AVFoundation.h>
#import <CoreMotion/CoreMotion.h>

#include <QPointer>

//------------------------------------------------------------------------------

static QPointer<IOSActivityRecognition> g_Instance;

//------------------------------------------------------------------------------

@interface ActivityRecognition : NSObject
{
    CMMotionActivityManager *motionActivityManager;
}

- (void) start;
- (void) stop;

@end

//------------------------------------------------------------------------------

@implementation ActivityRecognition

- (id) init
{
    if ( [CMMotionActivityManager isActivityAvailable] )
    {
        motionActivityManager = [[CMMotionActivityManager alloc] init];
    }

    return self;
}

- (void) start
{
    if ( motionActivityManager == nil )
    {
        g_Instance->setState(-1);
        emit g_Instance->error("Error Unknown");
        return;
    }

    CMMotionActivityHandler motionActivityHandler = ^(CMMotionActivity *activity)
    {
        NSString* act = [self generateAct:activity];
        g_Instance->setActivities(QString::fromNSString(act));
        emit g_Instance->activityDetected();
    };

    if ( motionActivityManager )
    {
        [motionActivityManager startActivityUpdatesToQueue:[NSOperationQueue mainQueue]
                                                            withHandler:motionActivityHandler];
        g_Instance->setState(0);
    }
}

- (NSString *)generateAct: (CMMotionActivity *) activity
{
    if (activity.stationary)
    {
        return @"STATIONARY";
    }

    if (activity.walking)
    {
        return @"WALKING";
    }

    if (activity.running)
    {
        return @"RUNNING";
    }

    if (activity.automotive)
    {
        return @"AUTOMOTIVE";
    }

    if (activity.cycling)
    {
        return @"CYCLING";
    }

    return @"UNKNOWN";
}

- (void) stop
{
    if ( motionActivityManager == nil )
    {
        Q_EMIT g_Instance->error("Unknown error");
        g_Instance->setState(-1);
        return;
    }

    if ( motionActivityManager )
    {
        [motionActivityManager stopActivityUpdates];
        g_Instance->setState(1);
    }
}

@end

//------------------------------------------------------------------------------

static ActivityRecognition *activityRecognition;

//------------------------------------------------------------------------------

IOSActivityRecognition::IOSActivityRecognition()
{
    g_Instance = this;
    activityRecognition = [[ActivityRecognition alloc] init];
}

//------------------------------------------------------------------------------

void IOSActivityRecognition::start()
{
    if ( ![[NSBundle mainBundle] objectForInfoDictionaryKey:@"NSMotionUsageDescription"] )
    {
        emit error("Missing NSMotionUsageDescription");
        return;
    }

    if ( ![CMMotionActivityManager isActivityAvailable] )
    {
        emit error("CMMotionActivityManager not available");
        return;
    }

    [activityRecognition start];
}

//------------------------------------------------------------------------------

void IOSActivityRecognition::stop()
{
    [activityRecognition stop];
}

//------------------------------------------------------------------------------
