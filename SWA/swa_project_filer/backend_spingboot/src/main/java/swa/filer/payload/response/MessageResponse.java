package swa.filer.payload.response;

public class MessageResponse {
    private String message;

    public MessageResponse(String _message){
        this.message = _message;
    }

    public String getMessage(){
        return this.message;
    }
    
}
