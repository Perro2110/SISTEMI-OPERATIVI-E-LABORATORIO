import java.io.Serializable;

public class Message implements Serializable {
    int num=0;
    float val=0;
    public int getNum() {
        return num;
    }
    public float getVal() {
        return val;
    }
    public Message(int num, float val) {
        this.num = num;
        this.val = val;
    }
    
    @Override
    public String toString() {
        return "val: "+val+"num: "+num;
    }

}
