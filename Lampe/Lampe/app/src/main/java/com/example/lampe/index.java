package com.example.lampe;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

public class index extends AppCompatActivity implements View.OnClickListener {

    private Button btnColor1;
    private Button btnColor2;
    private Button btnColor3;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_index);


        btnColor1 = (Button) findViewById(R.id.btnColor1);
        btnColor1.setOnClickListener(this);

        btnColor2 = (Button) findViewById(R.id.btnColor2);
        btnColor2.setOnClickListener(this);

        btnColor3 = (Button) findViewById(R.id.btnColor3);
        btnColor3.setOnClickListener(this);

        Log.i("TAG", "onCreate()");
    }

    @Override
    protected void onStart() {
        super.onStart();
        Log.i("TAG1", "onStart()");
    }

    @Override
    protected void onResume() {
        super.onResume();
        Log.i("TAG2", "onResume()");
    }

    @Override
    protected void onPause() {
        super.onPause();
        Log.i("TAG3", "onPause()");
    }

    @Override
    protected void onStop() {
        super.onStop();
        Log.i("TAG4", "onStop()");
    }

    @Override
    protected void onRestart() {
        super.onRestart();
        Log.i("TAG5", "onRestart()");
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        Log.i("TAG6", "onDestroy()");
    }

    public void onClick(View v) {
        Intent intent = new Intent(this, MainActivity.class);
        switch (v.getId()) {
            case R.id.btnColor1:
                intent.putExtra("b", 255);
                startActivity(intent);
                break;
            case R.id.btnColor2:
                intent.putExtra("r", 255);
                startActivity(intent);
                break;
            case R.id.btnColor3:
                intent.putExtra("v", 255);
                startActivity(intent);
            default:
                System.out.println("Un problème a été détecter sur le button");
                break;
        }
    }
}
