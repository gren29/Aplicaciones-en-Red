import java.io.ByteArrayInputStream;
import java.io.DataInputStream;
import java.net.DatagramPacket;
import java.net.DatagramSocket;

public class SPrimUDPB{
    public static void main(String[] args) {
        try {
            DatagramSocket s = new DatagramSocket(2002);
            System.out.println("Servidor Iniciado...");
            for(;;){
                DatagramPacket p = new DatagramPacket(new byte[2000], 2000);
                s.receive(p);
                System.out.println("Datagrama recibido desde "+p.getAddress()+":"+p.getPort());
                DataInputStream dis= new DataInputStream(new ByteArrayInputStream(p.getData()));

                //int x=dis.readInt();
                //float f=dis.readFloat();
                //Long l=dis.readLong();
                //System.out.println("Entero: "+x+"\nFlotante :"+f+"\nLargo: "+l+"\n");

                Long boleta = dis.readLong();
                String nombre = dis.readUTF();
                int edad = dis.readInt();
                Long tamaño = dis.readLong();
                Double valor = dis.readDouble();
                Boolean resultado =  dis.readBoolean();

                System.out.println("Boleta :"+boleta+"\nNombre: "+nombre+"\nEdad: "+edad+"\nTamaño: "+tamaño+"\nValor: "+valor+"\nResultado: "+resultado);

            } 
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}