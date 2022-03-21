/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package network_layer;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import javax.net.ssl.SSLSocket;
import javax.net.ssl.SSLSocketFactory;

/**
 *
 * @author Breaze
 */
public class TCPClient {
    private String server;
    private int port;
    //private Socket client;
    private SSLSocket client;
    private DataInputStream input;
    private DataOutputStream output;
    
    /*public TCPClient(String server, int port){
        this.server = server;
        this.port = port;
    }*/
    
    public String connect(String msg){
        String res = null;
        try {
            //this.client = new Socket(this.server, this.port);
            SSLSocketFactory sslSocketFactory = (SSLSocketFactory)SSLSocketFactory.getDefault();
            System.out.println("sdfads: "+server);
            this.client = (SSLSocket)sslSocketFactory.createSocket(this.server, this.port);

            this.input = new DataInputStream(this.client.getInputStream());
            this.output = new DataOutputStream(this.client.getOutputStream());
            this.output.writeUTF(msg);
            res = this.input.readUTF();
            //String update = this.input.readUTF();
            //System.out.println("changes"+update);
            this.client.close();
        } catch (IOException e) {
            res = e.getMessage();
        }
        return res;
    }

    public void setServer(String server) {
        this.server = server;
    }

    public void setPort(int port) {
        this.port = 9090;
    }
    
    
}
