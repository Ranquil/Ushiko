package com.nvidia.pentak;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;

import java.io.File;

public class LaunchProxy extends Activity {
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        File libraryOverrideDir = new File("/data/data/com.siika2D/lib_override");
        if (libraryOverrideDir.exists()) {
            File[] libraries = libraryOverrideDir.listFiles();
            for (int i = 0; i < libraries.length; i++) {
                System.load(libraries[i].getAbsolutePath());
            }
        }

        Intent intent = new Intent();
        intent.setClassName("com.siika2D", "android.app.NativeActivity");
        startActivity(intent);
    }
}
