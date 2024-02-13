import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PipedInputStream;
import java.io.PipedOutputStream;
import java.util.Scanner;

public class App {
    public static void main(String[] args) throws Exception {
        PipedOutputStream pos = new PipedOutputStream();
        PipedInputStream pis = new PipedInputStream(pos);

        RillevatoreAria ra = new RillevatoreAria(pos);
        String line;
        Scanner sc;
  
        ra.start();
        System.out.println("pollo1");
        BufferedReader br = new BufferedReader(new InputStreamReader(pis));
        System.out.println("pollo2");
        for(int i=0;i<8;i++){
            line=br.readLine();
            System.out.println("letto da pipe : " + line);
        }
        ra.fermatiRillevatoreDaria();
        ra.join();
    }
}
