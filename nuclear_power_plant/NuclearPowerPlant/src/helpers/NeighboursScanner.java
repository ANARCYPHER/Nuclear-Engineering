/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package helpers;

import java.net.SocketException;
import java.util.ArrayList;

/**
 *
 * @author Breaze
 */
public class NeighboursScanner {
    private final NetworkScanner networkScanner;
    private final PortScanner portScanner;
    
    public NeighboursScanner() throws SocketException{
        this.networkScanner = new NetworkScanner();
        this.portScanner = new PortScanner();
    }
    
    public void searchNuclearPowerPlants(){
        this.networkScanner.checkHosts();
        ArrayList<ArrayList> neighboursInfo = this.portScanner.scanPort();
        ArrayList<String> servers = neighboursInfo.get(0);
        ArrayList<Integer> ports = neighboursInfo.get(1);
        ArrayList<String> names = neighboursInfo.get(2);
        this.saveNeighbours(servers, ports, names);
    }
    
    private void saveNeighbours(ArrayList<String> serverList, ArrayList<Integer> serverPorts, ArrayList<String> names){
        PropertiesManager pm = new PropertiesManager();
        String servers = "";
        String ports = "";
        String neighbourNames = "";
        for(int i = 0; i < serverList.size(); i++){
            
            servers += (i<serverList.size()-1)?serverList.get(i)+",":serverList.get(i);
            ports += (i<serverPorts.size()-1)?serverPorts.get(i)+",":serverPorts.get(i);
            neighbourNames += (i<names.size()-1)?names.get(i)+",":names.get(i);
        }
        System.out.println(servers);
        System.out.println(ports);
        System.out.println(neighbourNames);
        pm.saveValue("neighbours", servers);
        pm.saveValue("ports", ports);
        pm.saveValue("neighbour_names", neighbourNames);
    }
}