/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package models;

import exceptions.DamagedReactorException;
import exceptions.ReactorOffException;
import exceptions.ReactorAlreadyOnException;

/**
 *
 * @author Breaze
 */
public class NuclearPowerPlant {
    private final NuclearReactor reactors[];
    
    public NuclearPowerPlant(){
        this.reactors = new NuclearReactor[3];
        for(int i = 0; i < this.reactors.length; i++){
            this.reactors[i] = new NuclearReactor();
        }
    }

    public NuclearReactor[] getReactors() {
        return reactors;
    }
    
    public NuclearReactor getReactor(int reactor){
        return this.reactors[reactor];
    }
    
    public boolean turnOn(int reactor){
        boolean res = false;
        if(this.reactors!=null)
            res = this.reactors[reactor].turnOn();
        return res;
        
    }
    
    public boolean turnOff(int reactor){
        boolean res = false;
        if(this.reactors!=null)
            res = this.reactors[reactor].turnOff();
        return res;
        
    }
    
    public boolean chargeReactor(int reactor, int value){
        boolean res = false;
        if (this.reactors != null) {
            this.reactors[reactor].chargeReactor(value);
            res = true;
        }
        
        return res;
    }
    
    public boolean dischargeReactor(int reactor, int value){
        boolean res = false;
        
        if (this.reactors != null) {
            this.reactors[reactor].dischargeReactor(value);
            res = true;
        }
        return res;
    }
    
    public boolean repairReactor(int reactor){
        boolean res = false;
        if(this.reactors!=null){
            res = this.reactors[reactor].repairReactor();
        }
        return res;
    }
    
}
