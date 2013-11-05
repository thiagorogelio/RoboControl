/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package robocontrol;

import java.io.IOException;
import java.io.PrintStream;
import java.net.Socket;
import java.util.Scanner;
import robocontrol.graphinterface.graphAlert;

/**
 *
 * @author maxx
 */
public class Connection {
    public String ip;
    public int port;
    public Boolean connected;
    public Connection(){
        this.ip = "192.168.1.10";
        this.port = 1000;
        this.connected = false;
    }
    
    public Boolean connect(){
        try{ 
            this.client = new Socket(this.ip, this.port);
            saida = new PrintStream(client.getOutputStream());
            this.connected = true;
            entrada = new Scanner(client.getInputStream());
            //if(ask("robo?").contains("claro!"))
            this.connected = true;
            //else {
                //desconnect();
            return true;
        }catch(IOException e){  
            return false;
        }
    }
    
    public void desconnect(){
        try{ 
                 saida.close();
                 client.close();
                 connected = false;
        }catch(IOException e){  

        }
    }
    public void send(String msg){
            if(this.connected)
                 saida.println(msg);
    }
    public String ask(String msg){
        String leit = null;
            if(this.connected){
                 saida.println(msg);
                 leit = entrada.nextLine();
            }
        return leit;
    }
    private Scanner entrada;
    private Socket client;
    private PrintStream saida;
}
