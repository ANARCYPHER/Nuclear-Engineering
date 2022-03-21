/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package network_layers;

import controllers.NuclearPowerPlantController;
import helpers.PropertiesManager;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.net.ssl.SSLServerSocket;
import javax.net.ssl.SSLServerSocketFactory;
import javax.net.ssl.SSLSocket;

/**
 *
 * @author Breaze
 */
public class TCPServer {
    //private ServerSocket server;
    private SSLServerSocket server;
    private Socket client;
    private int port;
    private NuclearPowerPlantController controller;
    private ArrayList<Socket> connections;
    
    
    public void TCPServer(){
        this.server = null;
        this.connections = new ArrayList<>();
    }
    public void runServer(){
        this.readPort();
        try{
            //this.server = new ServerSocket(this.port);
            SSLServerSocketFactory sslServerSocketFactory = (SSLServerSocketFactory)SSLServerSocketFactory.getDefault();
            this.server = (SSLServerSocket)sslServerSocketFactory.createServerSocket(this.port);
            System.out.println("Listening...");
            this.controller = new NuclearPowerPlantController();
            while(true){
                //this.client = this.server.accept();
                this.client = (SSLSocket) this.server.accept();
                System.out.println("Client connected");
                if(this.controller==null)
                    System.out.println("nulo");
                ServerThread sh = new ServerThread(this.client, this.controller, this);
                
                //this.connections.add(new ServerThread(this.client, this.controller, this));
                sh.start();
                //this.connections.get(this.connections.size()-1).start();
                //System.out.println("Client disconnected");
                
            }
        }catch(IOException e){
            System.out.println(e.getMessage());
        }
    }
    
    public void readPort(){
        PropertiesManager pm = new PropertiesManager();
        int serverPort = pm.getServerPort();
        this.port = serverPort;
    }
    
    //TODO: updtateClients()
    /**
     *  for(connections) //
     *  update //input controller.getReactorInfo();
     */
    
}