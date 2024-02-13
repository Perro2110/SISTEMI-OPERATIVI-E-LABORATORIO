import java.io.Serializable;

public class Message implements Serializable{
    int num;
    float val;
    String mess;

    public Message(int num, float val) {
        this.num = num;
        this.val = val;
        if(val < 0)
        this.mess= "Errore "+Integer.toString(num) +" "+ Float.toString(val);
        else
        this.mess= "Ok "+Integer.toString(num) +" " +Float.toString(val);
    }

    public String getMess() {
        return mess;
    }
}
