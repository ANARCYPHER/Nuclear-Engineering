/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package network_layers;

import controllers.NuclearPowerPlantController;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.net.ssl.SSLSocket;

/**
 *
 * @author Breaze
 */
public class ServerThread extends Thread {

    private Socket client;
    private DataInputStream input;
    private DataOutputStream output;
    private NuclearPowerPlantController controller;
    private TCPServer parent;

    //TODO: ADD PARAM OF TCP SERVER
    public ServerThread(Socket client, NuclearPowerPlantController controller, TCPServer parent) {
        try {
            this.client = client;
            this.controller = controller;
            this.input = new DataInputStream(this.client.getInputStream());
            this.output = new DataOutputStream(this.client.getOutputStream());
            this.parent = parent;
        } catch (IOException ex) {
            Logger.getLogger(ServerThread.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public Socket getClient() {
        return this.client;
    }


    @Override
    public void run() {
        try {
            String message = this.input.readUTF();
            System.out.println("server >> " + message);
            String order[] = message.split(":");
            String res = this.trigger(order);
            int reactor = Integer.parseInt(order[1]);
            String info = this.controller.getReactorInfo(reactor);
            this.output.writeUTF(res+"\n "+info);
            //this.parent.updateClients();
        } catch (IOException ex) {
            Logger.getLogger(ServerThread.class.getName()).log(Level.SEVERE, null, ex);
        }
        //this.disconnect();
    }
    public String trigger(String[] order){
        String response = null;
        String function = order[0];
        int reactor = Integer.parseInt(order[1]);
        switch(function){
            case "turn_on":
                response = this.controller.turnOn(reactor);
                break;
            case "turn_off":
                response = this.controller.turnOff(reactor);
                break;
            case "charge":
                response = this.controller.chargeReactor(reactor, Integer.parseInt(order[2]));
                break;
            case "discharge":
                response = this.controller.dischargeReactor(reactor, Integer.parseInt(order[2]));
                break;
            case "repair":
                response = this.controller.repairReactor(reactor);
                break;
        }
        return response;
    }
    
    public final void disconnect() {
        try {
            this.client.close();
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }

    public DataOutputStream getOutput() {
        return output;
    }

    /*public String getMessage() {
        return message;
    }

    public String getRes() {
        return res;
    }*/
    
    
}
