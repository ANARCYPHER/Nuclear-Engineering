/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package network_layers;

import java.io.IOException;
import java.net.SocketException;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Breaze
 */
public class UDPThread extends Thread{
    @Override
    public void run(){
        try {
            PortEntrance pe = new PortEntrance();
            pe.runServer();
        } catch (SocketException ex) {
            Logger.getLogger(UDPThread.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(UDPThread.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
