package com.libmailcore;

import android.os.Handler;
import android.os.Looper;
import android.util.Log;
import java.util.HashMap;
import android.os.HandlerThread;

public class MainThreadUtils {
    // private static volatile MainThreadUtils instance = new MainThreadUtils();
    private static volatile MainThreadUtils mInstance;
    private Handler handler;
    private HashMap<Long, Runnable> runnablesForIdentifiers = new HashMap<Long, Runnable>();
    
    static MainThreadUtils singleton() {
        // return Instance;
        return mInstance;

    }

    public static synchronized MainThreadUtils mSingleton(Handler mHandler) {
        if (mInstance == null) {
            mInstance = new MainThreadUtils(mHandler);
        }
        return mInstance;
    }

    private MainThreadUtils(Handler mHandler){
        System.loadLibrary("MailCore");
        System.loadLibrary("c++_shared");
        // handler = new Handler(Looper.getMainLooper());

        handler = mHandler;
        // HandlerThread handlerThread = new HandlerThread("MailCore-Handler-Thread");
        // handlerThread.start();
        // handler = new Handler(handlerThread.getLooper());

        // Looper.prepare();
        // handler = new Handler();
        // Looper.loop();
        setupNative();
    }
    // private constructor
    private MainThreadUtils() {
        System.loadLibrary("MailCore");
        System.loadLibrary("c++_shared");
        handler = new Handler(Looper.getMainLooper());
        // HandlerThread handlerThread = new HandlerThread("MailCore-Handler-Thread");
        // handlerThread.start();
        // handler = new Handler(handlerThread.getLooper());
        // Looper.prepare();
        // handler = new Handler();
        // Looper.loop();
        setupNative();
    }

    private native void setupNative();

    private native void runIdentifier(long identifier);
    private native void runIdentifierAndNotify(long identifier);

    private void runOnMainThread(final long identifier) {
        handler.post(new Runnable() {
            @Override
            public void run() {
                runIdentifier(identifier);
            }
        });
    }

    private void runOnMainThreadAndWait(final long identifier) {
        handler.post(new Runnable() {
            @Override
            public void run() {
                runIdentifierAndNotify(identifier);
            }
        });
    }

    private void runAfterDelay(final long identifier, int milliseconds) {
        Runnable runnable = new Runnable() {
                    @Override
                    public void run() {
                        runnablesForIdentifiers.remove(new Long(identifier));
                        runIdentifier(identifier);
                    }
                };
        runnablesForIdentifiers.put(new Long(identifier), runnable);
        handler.postDelayed(runnable, milliseconds);
    }
    
    private void cancelDelayedRun(final long identifier) {
        Runnable runnable = runnablesForIdentifiers.get(new Long(identifier));
        runnablesForIdentifiers.remove(new Long(identifier));
        handler.removeCallbacks(runnable);
    }
}
