/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package network_layers;

/**
 *
 * @author Breaze
 */
public class TCPThread extends Thread{
    @Override
    public void run(){
        TCPServer server = new TCPServer();
        server.runServer();
    }
}
