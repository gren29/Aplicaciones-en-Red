import java.net.*;
import java.io.*;
public class CEcoUDPB {
    public static void main(String[] args){
        try{
            DatagramSocket cl = new DatagramSocket();
            System.out.print("Cliente iniciado, escriba un mensaje de saludo:");
            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
            String mensaje = br.readLine();
            int numPaquetes = (int)Math.ceil(mensaje.length()/20)+1;
            String numPaquetesS = Integer.toString(numPaquetes);
            System.out.println("NumPaquetes: "+numPaquetes+"\n"+"NumPaquetes S: "+numPaquetesS+"\n");

            byte[] numPaquetesB = numPaquetesS.getBytes();
            String dst = "127.0.0.1";
            int pto = 2019;
            DatagramPacket numPaquetesP = new DatagramPacket(numPaquetesB,numPaquetesB.length, InetAddress.getByName(dst),pto);
            cl.send(numPaquetesP);

            int inicio = 0;
            int finals = 19;
            for(int i = 0; i < numPaquetes;i++){
                if(i == numPaquetes-1){
                    String subPaquete = mensaje.substring(inicio-1,mensaje.length());
                    byte[] numPaquetesB1 = subPaquete.getBytes();
                    String dst1 = "127.0.0.1";
                    DatagramPacket numPaquetesP1 = new DatagramPacket(numPaquetesB1,numPaquetesB1.length, InetAddress.getByName(dst1),pto);
                    cl.send(numPaquetesP1);
                    break;
                }
                else{
                    String subPaquete = mensaje.substring(inicio,finals);
                    byte[] numPaquetesB2 = subPaquete.getBytes();
                    String dst2 = "127.0.0.1";
                    DatagramPacket numPaquetesP2 = new DatagramPacket(numPaquetesB2,numPaquetesB2.length, InetAddress.getByName(dst2),pto);
                    cl.send(numPaquetesP2);
                    inicio +=20;
                    finals += 20;
                }
            }
            cl.close();
            // byte[] b = mensaje.getBytes();
            // String dst = "127.0.0.1";
            // int pto = 2014;
            // DatagramPacket p = new DatagramPacket(b,b.length, InetAddress.getByName(dst),pto);
            // cl.send(p);
            // cl.close();
        }catch(Exception e){
            e.printStackTrace();
        }//catch
    }//main
}

//Dividimos el mensaje entre 20