import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class CPrimUDPB{
    public static void main(String[] args) {
        try{
            int pto = 2002;
            InetAddress dst = InetAddress.getByName("127.0.0.1");
            DatagramSocket cl = new DatagramSocket();
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            DataOutputStream dos = new DataOutputStream(baos);

            /*dos.writeInt(4);
            dos.flush();
            dos.writeFloat(4.1f);
            dos.flush();
            dos.writeLong(72);
            dos.flush();
            */

            dos.writeLong(2014031280L);
            dos.flush();
            dos.writeUTF("Raul Sanchez Rico");
            dos.flush();
            dos.writeInt(22);
            dos.flush();
            dos.writeLong(180);
            dos.flush();
            dos.writeDouble(10.0d);
            dos.flush();
            dos.writeBoolean(true);
            dos.flush();
            byte[] b = baos.toByteArray();
            DatagramPacket p = new DatagramPacket(b,b.length, dst, pto);
            cl.send(p);
            cl.close();
        }catch(Exception e){
            e.printStackTrace();
        }
    }
}