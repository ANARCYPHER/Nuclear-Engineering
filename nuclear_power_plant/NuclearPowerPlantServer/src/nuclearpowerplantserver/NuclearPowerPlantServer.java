/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package nuclearpowerplantserver;

import java.io.IOException;
import java.net.SocketException;
import java.util.logging.Level;
import java.util.logging.Logger;
import network_layers.PortEntrance;
import network_layers.TCPServer;
import network_layers.TCPThread;
import network_layers.UDPThread;

/**
 *
 * @author Breaze
 */
public class NuclearPowerPlantServer {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        System.setProperty("javax.net.ssl.keyStore","mykeystore.jks");
        System.setProperty("javax.net.ssl.keyStorePassword","123456789");

        UDPThread udp = new UDPThread();
        udp.start();
        TCPThread tcp = new TCPThread();
        tcp.start();
    }
    
}
