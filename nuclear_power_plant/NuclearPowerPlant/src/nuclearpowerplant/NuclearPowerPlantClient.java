/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package nuclearpowerplant;

import gui.Home;
import helpers.NetworkScanner;
import helpers.PortScanner;
import helpers.NeighboursScanner;
import java.net.SocketException;
import java.util.logging.Level;
import java.util.logging.Logger;
import network_layer.TCPClient;

/**
 *
 * @author Breaze
 */
public class NuclearPowerPlantClient {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        /*try {
            NeighboursScanner ns = new NeighboursScanner();
            ns.searchNuclearPowerPlants();
                    
        } catch (SocketException ex) {
            Logger.getLogger(NuclearPowerPlantClient.class.getName()).log(Level.SEVERE, null, ex);
        }*/
        /*TCPClient client = new TCPClient("127.0.0.1", 9050);
        client.connect();*/
        System.setProperty("javax.net.ssl.trustStore", "myKeystore.jks");
        System.setProperty("javax.net.ssl.trustStorePassword", "123456789");

        Home home = new Home();
        home.setVisible(true);
        NetworkScanner net = new NetworkScanner();
        //net.
    }
    
}
