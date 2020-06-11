import java.net.*;
import java.io.*;

public class SEcoUDPB {
    public static void main(String[] args){
        try{

            DatagramSocket s = new DatagramSocket(2019);
            System.out.println("Servidor iniciado, esperando cliente");
            for(;;){
                // DatagramPacket p = new DatagramPacket(new byte[2000],2000);
                // s.receive(p);
                // System.out.println("Datagrama recibido desde" + p.getAddress()+":"+p.getPort());
                // String msj = new String(p.getData(),0,p.getLength());
                // System.out.println("Con el mensaje:"+ msj);
                String mensajeCompleto = "";
                DatagramPacket p = new DatagramPacket(new byte[2000],2000);
                s.receive(p);
                System.out.println("Datagrama recibido desde" + p.getAddress()+":"+p.getPort());
                String msj = new String(p.getData(),0,p.getLength());
                System.out.println("Numero de paquetes"+ msj);
                int numPaquetes = Integer.parseInt(msj);  
                for(int i = 0;i < numPaquetes;i++){
                    DatagramPacket p1 = new DatagramPacket(new byte[2000],2000);
                    s.receive(p1);
                    String msjPaquete = new String(p1.getData(),0,p1.getLength());
                    mensajeCompleto += msjPaquete;
                }
                System.out.println("Mensaje Completo: "+ mensajeCompleto);
            }//for
            //s.close()
        }catch(Exception e){
            e.printStackTrace();
        }//catch
    }//main
}
