/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package exceptions;

/**
 *
 * @author Breaze
 */
public class DamagedReactorException extends RuntimeException{
    public DamagedReactorException(String message){
        super(message);
    }
    /*
    @Override
    public String getMessage(){
        return super.getMessage() + "The reactor cannot be turned off while is already off";
    }*/
}
