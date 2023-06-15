package swa.filer.payload.response;

public class JwtResponse {
    
    private String token;
    private String type = "Bearer";
    private Long id;
    private String email;
    private String firstName;
    private String lastName;

    public JwtResponse(String accessToken, Long id, String email, String firstName, String lastName) {
        this.token = accessToken;
        this.id = id;
        this.email = email;
        this.firstName = firstName;
        this.lastName = lastName;
    }

    public String getAccessToken() {
        return this.token;
    }

    public void setAccessToken(String accessToken) {
        this.token = accessToken;
    }

    public String getTokenType() {
        return this.type;
    }

    public void setTokenType(String tokenType) {
        this.type = tokenType;
    }

    public Long getId(){
        return this.id;
    }

    public void setId(Long _id){
        this.id = _id;
    }

    public String getEmail(){
        return this.email;
    }

    public void setEmail(String _email){
        this.email = _email;
    }

    public String getFirstName(){
        return this.firstName;
    }

    public void setFirstName(String _firstName){
        this.firstName = _firstName;
    }

    public String getLastName(){
        return this.lastName;
    }

    public void setLastName(String _lastName){
        this.lastName = _lastName;
    }
}
