/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package helpers;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.Properties;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Breaze
 */
public class PortScanner {
    private final DatagramSocket socket;
    public PortScanner() throws SocketException
    {
        this.socket = new DatagramSocket();
    }
    
    public void send(String msg, String server, int port) throws UnknownHostException, IOException
    {
        InetAddress host = InetAddress.getByName(server);        
        
        byte[] buffer = msg.getBytes();

        DatagramPacket request = 
                new DatagramPacket(buffer, buffer.length, host, port);
        
        this.socket.send(request);
        
    }
    
    public ArrayList<ArrayList> scanPort(){
        PropertiesManager pm = new PropertiesManager();
        String portRange[] = pm.getPortRange();
        String onNetwork[] = pm.getOnNetwork();
        ArrayList<String> neighbours = new ArrayList();
        ArrayList<String> names = new ArrayList();
        ArrayList<Integer> ports = new ArrayList();
        int startPort = Integer.parseInt(portRange[0]);
        int finalPort = Integer.parseInt(portRange[1]);
        System.out.println("Scanning ports...");
        for(String server : onNetwork)
        {
            for(int i = startPort; i <= finalPort; i++){
                try {
                    this.socket.setSoTimeout(1000);
                    this.send("running", server, i);
                    String response = this.getResponse();
                    response = response.replace("\u0000", ""); // removes NUL chars
                    response = response.replace("\\u0000", ""); // removes backslash+u0000
                    String data[] = response.split(":");
                    System.out.println(response);
                    String name = data[0];
                    String port = data[1];
                    names.add(name);
                    neighbours.add(server);
                    ports.add(Integer.parseInt(port));
                    System.out.println(server+" is reachable in port: "+i);
                    
                } catch (IOException ex) {
                    System.out.println(server+" is not reachable in port: "+i);
                    //System.out.println("Error: "+ ex.getMessage());
                }
            }
        }
        ArrayList<ArrayList> neighboursInfo = new ArrayList<ArrayList>();
        neighboursInfo.add(neighbours);
        neighboursInfo.add(ports);
        neighboursInfo.add(names);
        return neighboursInfo;
        
    }
    public String getResponse() throws IOException
    {
        byte[] buffer = new byte[30];

        DatagramPacket request = 
                new DatagramPacket(buffer, buffer.length);
        this.socket.receive(request);
        //System.out.println(new String(request.getData()));
        return new String(request.getData());
    }
}
