
    //region import

    package com.example.lampe;

    import android.content.Intent;
    import android.graphics.Color;
    import android.os.AsyncTask;
    import android.support.v7.app.AppCompatActivity;
    import android.os.Bundle;
    import android.util.Log;
    import android.view.View;
    import android.widget.Button;
    import android.widget.TextView;

    import java.io.BufferedReader;
    import java.io.IOException;
    import java.io.InputStreamReader;
    import java.io.PrintWriter;
    import java.net.Socket;
    import java.net.UnknownHostException;

    import static android.graphics.Color.rgb;

    //endregion

public class MainActivity extends AppCompatActivity implements
        View.OnClickListener{

    //region Variable

    private TextView affichage1;
    private TextView affichage2;

    private Button btnPlusRouge;
    private Button btnMoinsRouge;
    private Button btnPlusVert;
    private Button btnMoinsVert;
    private Button btnPlusBleu;
    private Button btnMoinsBleu;
    private Button btnColor;

    public String envoieserv;

    int tabr[] = {255,255,255,50 ,0  ,0  ,75 };
    int tabg[] = {0  ,144,215,205,191,0  ,0  };
    int tabb[] = {0  ,0  ,0  ,50 ,255,255,130};

    public int r = 0;
    public int g = 0;
    public int b = 0;

    //endregion

    //region Thread
    private class WaitingThread2 extends Thread {

    public String requete;
    public int valeur;

    WaitingThread2(String requete, int valeur){
        this.requete = requete;
        this.valeur = valeur;
    }

        public void run() {
            if(valeur == 1){
                Socket socket = null;
                try {
                    Log.e("e1","on es dedans 2");
                    socket = new Socket("http://chadok.info/~ckeller", 9998);
                    PrintWriter writer = new PrintWriter(socket.getOutputStream(), true);
                    writer.println(requete);
                    BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                    Log.i("msgServ",reader.readLine());
                    socket.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }

            }
        }
    }
    //endregion

    //region Asyntask

    private class WaitingThread extends AsyncTask<Void, Integer, Integer> {
        private TextView affichage;
        private int num;

        private final int wait = 1000;
        private final int number = 7;

        WaitingThread(int n) {
            num = n;
        }

        @Override
        protected void onPreExecute() {
            System.out.println("Lancement mode 1");

        }

        @Override
        protected Integer doInBackground(Void... voids) {

            if (num == 1){ // arc en ciel mais fini

                btnMoinsBleu.setEnabled(false);
                btnMoinsRouge.setEnabled(false);
                btnMoinsVert.setEnabled(false);
                btnPlusBleu.setEnabled(false);
                btnPlusRouge.setEnabled(false);
                btnPlusVert.setEnabled(false);

                for (int i = 0; i < number ; i++){
                    r = tabr[i];
                    b = tabb[i];
                    g = tabg[i];

                    chargerEcran();
                    try {
                        Thread.sleep(wait);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }

            if (num == 2){ // raimbow et infini
                while(true){

                    for (int i = 0; i < number ; i++){

                        r = tabr[i];
                        b = tabb[i];
                        g = tabg[i];

                        String res = Integer.toHexString(r);
                        String ges = Integer.toHexString(g);
                        String bes = Integer.toHexString(b);

                        if (res.length() == 1){
                            res = "0" + res;
                        }

                        if (ges.length() == 1){
                            ges = "0" + ges;
                        }

                        if (bes.length() == 1){
                            bes = "0" + bes;
                        }

                        for ( int y = 1 ; y < 10 ; y++){
                            System.out.println("test : " + "0" + y + res + ges + bes);
                            envoieserv = "0" + y + res + ges + bes;

                            Log.e("e1","on es dedans 1");
                            new WaitingThread2(envoieserv,1).start();
                            /*
                            Socket socket = new Socket("91.121.242.52", 9998);
                            PrintWriter writer = new PrintWriter(socket.getOutputStream(), true);
                            writer.println("0" + y + res + ges + bes);
                            socket.close();
                            */
                        }


                        //writer.println("06ff00ff");
                        chargerEcran();

                        try {
                            Thread.sleep(wait);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }
                }

            }
            return number;
        }

        @Override
        protected void onProgressUpdate(Integer... counts) {
        }

        @Override
        protected void onPostExecute(Integer res) {
            btnMoinsBleu.setEnabled(true);
            btnMoinsRouge.setEnabled(true);
            btnMoinsVert.setEnabled(true);
            btnPlusBleu.setEnabled(true);
            btnPlusRouge.setEnabled(true);
            btnPlusVert.setEnabled(true);
        }
    }

    //endregion

    //region fonction

    @Override
    protected void onSaveInstanceState (Bundle outState) {
        super.onSaveInstanceState(outState);
        outState.putInt("r",r);
        outState.putInt("g",g);
        outState.putInt("b",b);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        btnPlusRouge = (Button) findViewById(R.id.btnPlusRouge);
        btnPlusRouge.setOnClickListener(this);

        btnMoinsRouge = (Button) findViewById(R.id.btnMoinsRouge);
        btnMoinsRouge.setOnClickListener(this);

        btnPlusVert = (Button) findViewById(R.id.btnPlusVert);
        btnPlusVert.setOnClickListener(this);

        btnMoinsVert = (Button) findViewById(R.id.btnMoinsVert);
        btnMoinsVert.setOnClickListener(this);

        btnPlusBleu = (Button) findViewById(R.id.btnPlusBleu);
        btnPlusBleu.setOnClickListener(this);

        btnMoinsBleu = (Button) findViewById(R.id.btnMoinsBleu);
        btnMoinsBleu.setOnClickListener(this);

        btnColor = (Button) findViewById(R.id.btnColor);
        btnColor.setOnClickListener(this);

        Intent intent = getIntent();
        r = intent.getIntExtra("r", 0);
        g = intent.getIntExtra("v", 0);
        b = intent.getIntExtra("b", 0);

        if (savedInstanceState != null) {
            r = savedInstanceState.getInt("r");
            g = savedInstanceState.getInt("g");
            b = savedInstanceState.getInt("b");
        }

        affichage1 = (TextView) findViewById(R.id.btnColor);
        affichage2 = (TextView) findViewById(R.id.btnColor);

        chargerEcran();


    }

    public void chargerEcran(){
        int color = Color.rgb(r,g,b);
        btnColor.setBackgroundColor(color);
    }

    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.btnPlusRouge:
                if (r <= 239){
                    r+=16;
                    chargerEcran();
                }
                break;
            case R.id.btnMoinsRouge:
                if (r >= 16){
                    r-=16;
                    chargerEcran();
                }
                break;
            case R.id.btnPlusVert:
                if (g <= 239){
                    g+=16;
                    chargerEcran();
                }
                break;
            case R.id.btnMoinsVert:
                if (g >= 16){
                    g-=16;
                    chargerEcran();
                }
                break;
            case R.id.btnPlusBleu:
                if (b <= 239){
                    b+=16;
                    chargerEcran();
                }
                break;
            case R.id.btnMoinsBleu:
                if (b >= 16){
                    b-=16;
                    chargerEcran();
                }
                break;
            case R.id.btnColor:
                WaitingThread mTask = new WaitingThread(2);
                mTask.execute();
                break;
            default:
                System.out.println("Un problème a été détecter sur le button");
                break;
        }
    }
    //endregion
}