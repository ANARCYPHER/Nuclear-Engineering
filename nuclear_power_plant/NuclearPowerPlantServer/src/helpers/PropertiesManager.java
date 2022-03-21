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
   
    
    public String getServerName(){
        String name = this.props.getProperty("server.name");
        return name;
    
    }
    
    public int getServerPort(){
        int port = Integer.parseInt(this.props.getProperty("server.port"));
        return port;
    
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
