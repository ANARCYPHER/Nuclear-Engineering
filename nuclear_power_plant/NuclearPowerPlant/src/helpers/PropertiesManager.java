/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package helpers;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.util.*;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Breaze
 */
public class PropertiesManager {
    private Properties props = new Properties();
    private InputStream input = null;	
    private final String PROPERTIES_ROUTE;
    public PropertiesManager(){
        this.props = new Properties();
        this.PROPERTIES_ROUTE = "./src/config.properties";
        this.readProperties();
    }
    
    private void readProperties(){
        try {
            this.input = new FileInputStream(this.PROPERTIES_ROUTE);
            this.props.load(input);
        } catch(IOException e) {
            System.out.println(e.toString());
        }
    }
    public String[] getOnNetwork(){
        String onNetwork[] = this.props.getProperty("server.on_network").split(",");
        return onNetwork;
    }
    
    public String[] getPortRange(){
        String portRange[] = this.props.getProperty("server.port_range").split(",");
        return portRange;
    }
    
    public String[] getNeighbourPorts(){
        String neighbourPorts[] = this.props.getProperty("server.ports").split(",");
        for(String n : neighbourPorts)
            System.out.println(n);
        return neighbourPorts;
    }
    
    public String[] getNeighbours(){
        String neighbours[] = this.props.getProperty("server.neighbours").split(",");
        return neighbours;
    }
    
    public String[] getNeighbourNames(){
        String neighbour_names[] = this.props.getProperty("server.neighbour_names").split(",");
        return neighbour_names;
    }
    
    public String getBase(){
        String base = this.props.getProperty("server.base");
        return base;
    
    }
    
    public void saveValue(String key, String value){
        try {
            FileOutputStream out = new FileOutputStream(this.PROPERTIES_ROUTE);
            this.props.setProperty("server."+key, value);
            props.store(out, null);
        } catch (IOException ex) {
            Logger.getLogger(PropertiesManager.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
