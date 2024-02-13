import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PipedInputStream;
import java.io.PipedOutputStream;
import java.util.Scanner;

public class App {
    public static void main(String[] args) throws Exception {
        PipedOutputStream pos = new PipedOutputStream();
        PipedInputStream pis = new PipedInputStream(pos);
        RillevatoreNotizie rilN = new RillevatoreNotizie(pos);
        String line = null;
        int count = 0;
        rilN.start();

        BufferedReader br = new BufferedReader(new InputStreamReader(pis));

        for (int i = 0; i < 8; i++) {
            line = br.readLine();
            Scanner sc = new Scanner(line);
            int num = sc.nextInt();
            if (num < 20) {
                System.out.println("Bufala " + line);
                count++;
            } else if (num <= 300) {
                System.out.println("Attendibile " + line);
                count--;
            } else {
                System.out.println("Tendenza "+line);
                count--;
            }
            if(count == 3){
                System.out.println("Attenzione tre bufale");
                count=0;
            }
        }
        rilN.fermaRillevatoreNotizie();
        rilN.join();
    }
}
