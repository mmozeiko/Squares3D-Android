package lv.bubu.Squares3D;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.app.Activity;
import android.content.Context;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.MotionEvent;

import java.lang.System;
import java.io.InputStream;
import android.content.res.AssetManager;

public class Game extends Activity
{
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        mGLView = new GameView(this);
        setContentView(mGLView);

        Native.ass = getAssets();
    }

    @Override
    protected void onPause()
    {
        super.onPause();
        mGLView.onPause();
        System.exit(0);
    }

    @Override
    protected void onResume()
    {
        super.onResume();
        mGLView.onResume();
    }

    private GLSurfaceView mGLView;
}

class GameView extends GLSurfaceView implements GLSurfaceView.Renderer
{
    public GameView(Context context)
    {
        super(context);
        setEGLConfigChooser(5, 6, 5, 0, 16, 0);
        setRenderer(this);
    }

    @Override
    public boolean onTouchEvent(MotionEvent event)
    {
        super.onTouchEvent(event);

        int action = event.getAction() & MotionEvent.ACTION_MASK;
        ;
        if (action == MotionEvent.ACTION_DOWN)
        {
            int id = event.getPointerId(0);
            Native.touchBegin(id, event.getX(id), event.getY(id));
        }
        else if (action == MotionEvent.ACTION_UP)
        {
            int id = event.getPointerId(0);
            Native.touchEnd(id);
        }
        else if (action == MotionEvent.ACTION_POINTER_DOWN)
        {
            int id = event.getAction() >> MotionEvent.ACTION_POINTER_ID_SHIFT;
            Native.touchBegin(id, event.getX(id), event.getY(id));
        }
        else if (action == MotionEvent.ACTION_POINTER_UP)
        {
            int id = event.getAction() >> MotionEvent.ACTION_POINTER_ID_SHIFT;
            Native.touchEnd(id);
        }
        else if (action == MotionEvent.ACTION_MOVE)
        {
            for (int i=0; i<event.getPointerCount(); i++)
            {
                int id = event.getPointerId(i);
                Native.touchMove(id, event.getX(id), event.getY(id));
            }
        }

        return true;
    }

    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        Native.begin();
    }

    public void onSurfaceChanged(GL10 gl, int w, int h) {
        Native.resize(w, h);
    }

    public void onDrawFrame(GL10 gl) {
        Native.render();
    }
}

class Native
{
    public static native int begin();
    public static native void resize(int w, int h);
    public static native void render();
    public static native void touchBegin(int id, float x, float y);
    public static native void touchMove(int id, float x, float y);
    public static native void touchEnd(int id);
    public static native void end();

    public static AssetManager ass;

    public static byte[] getAsset(String name)
    {
        byte[] data = null;
        try
        {
            InputStream is = ass.open(name.substring(1));
            int length = is.available();
            data = new byte[length];
            is.read(data);
            is.close();
        }
        catch (java.io.IOException e)
        {
        }

        return data;
    }

    static
    {
        System.loadLibrary("openal-soft");
        System.loadLibrary("Squares3D");
    }
}
