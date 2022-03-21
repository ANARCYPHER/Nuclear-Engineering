/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package helpers;

import java.io.IOException;
import java.net.Inet4Address;
import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Breaze
 */
public class NetworkScanner {
    public void checkHosts(){
        PropertiesManager pm = new PropertiesManager();
        String base = pm.getBase();
        ArrayList<String> neighbours = new ArrayList<>();
        int timeout = 100;
        System.out.println("Scanning devices on network...");
        //TODO: Assign value 1 to i and j variables and change the exit condition of the loops to
        // < 255
        for (int i = 110; i <= 111; i++)
        {       
            for(int j = 19; j <= 24; j++){
                for(int k = 44; k <=75; k++)
                {
                    try {
                        String host = base + "." + i+"."+j+"."+k;  
                        if (InetAddress.getByName(host).isReachable(timeout))
                        {
                            System.out.println(host + " is reachable");
                            neighbours.add(host);
                        }
                    } catch (IOException ex) {
                        Logger.getLogger(NetworkScanner.class.getName()).log(Level.SEVERE, null, ex);
                    }
                }
            }
        }
        this.saveOnNetwork(neighbours);
    }
    
    private void saveOnNetwork(ArrayList<String> on_network){
        String value = "";
        for(int i = 0; i < on_network.size(); i++){
            if(i<(on_network.size()-1))
                value += on_network.get(i)+",";
            else
                value +=on_network.get(i);
        }
        PropertiesManager pm = new PropertiesManager();
        pm.saveValue("on_network", value);
    }
}
