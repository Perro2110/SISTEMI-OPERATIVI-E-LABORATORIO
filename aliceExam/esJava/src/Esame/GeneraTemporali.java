package Esame;

import java.io.IOException;
import java.io.ObjectOutputStream;
import java.io.PipedOutputStream;
import java.util.Random;
import java.util.concurrent.atomic.AtomicBoolean;

public class GeneraTemporali extends Thread {
    AtomicBoolean isRunning = new AtomicBoolean();
    private PipedOutputStream pos;
    Random rd=new Random();
    float val;
    String giorno=null;

    public GeneraTemporali(PipedOutputStream pos) {
        this.isRunning.set(false);
        ;
        this.pos = pos;
    }

    @Override
    public void run() {
        isRunning.set(true);
        try (ObjectOutputStream oos = new ObjectOutputStream(pos)) {
            int i=0;
            while(isRunning.get()){
                try {
                    Thread.sleep(3000);
                } catch (InterruptedException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
                if(i==0){
                    giorno="lunedi";
                    i++;
                }
                else if(i==1){
                    giorno="martedi";
                    i++;
                }
                else if(i==2){
                    giorno="mercoledi";
                    i++;
                }
                else if(i==3){
                    giorno="giovedi";
                    i++;
                }
                else if(i==4){
                    giorno="venerdi";
                    i++;
                }
                else if(i==5){
                    giorno="sabato";
                    i++;
                }   
                else if(i==6){
                    giorno="domenica";
                    i=0;
                }
                val=rd.nextFloat()*(9-0)+0;

                Temporale oggetto_messaggio = new Temporale(val, giorno);
                oos.writeObject(oggetto_messaggio);
                oos.flush();
            }
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

    }

    public void terminaTemporali() {
        this.isRunning.set(false);
        Thread.interrupted();
    }

}
